#pragma once
#include <fstream>
#include <QFile>
#include <QTextStream>
#include "../Interfaces/IAuthService.h"
#include "../Interfaces/IApiService.h"

namespace Services {
    class AuthService : public Interfaces::IAuthService {
    public:
        AuthService(std::shared_ptr<Interfaces::IApiService> apiService,
                   const std::string& credentialsFile = "logindata.txt")
            : apiService_(std::move(apiService))
            , credentialsFile_(credentialsFile)
        {}

        Credentials getCredentials() override {
            if (!hasStoredCredentials()) {
                auto [username, password] = apiService_->getAnonymousAuth();
                Credentials creds{username, password};
                if (creds.isValid()) {
                    saveCredentials(creds);
                }
                return creds;
            }

            QFile file(QString::fromStdString(credentialsFile_));
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                return Credentials{};
            }

            QTextStream in(&file);
            QString line = in.readLine();
            file.close();

            int pos = line.indexOf(' ');
            if (pos == -1) {
                return Credentials{};
            }

            return Credentials{
                line.left(pos).toStdString(),
                line.mid(pos + 1).toStdString()
            };
        }

        void saveCredentials(const Credentials& credentials) override {
            std::ofstream file(credentialsFile_);
            if (file.is_open()) {
                file << credentials.username << " " << credentials.password << std::endl;
            }
        }

        std::string getAuthToken() override {
            auto creds = getCredentials();
            if (!creds.isValid()) {
                return "";
            }

            QString credentials = QString::fromStdString(creds.username + ":" + creds.password);
            return "Basic " + credentials.toUtf8().toBase64().toStdString();
        }

        bool hasStoredCredentials() override {
            std::ifstream file(credentialsFile_);
            return file.good();
        }

    private:
        std::shared_ptr<Interfaces::IApiService> apiService_;
        std::string credentialsFile_;
    };
} 