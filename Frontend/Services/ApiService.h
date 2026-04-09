#pragma once
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include "../Interfaces/IApiService.h"

namespace Services {
    class ApiService : public Interfaces::IApiService {
    public:
        ApiService(const std::string& baseUrl = "http://localhost:8000")
            : baseUrl_(QString::fromStdString(baseUrl))
        {
        }

        std::vector<Domain::Session> getSessions(const std::string& authToken) override {
            QNetworkAccessManager manager;
            QNetworkRequest request(QUrl(baseUrl_ + "/sessions"));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
            request.setRawHeader("Authorization", QByteArray::fromStdString(authToken));

            QNetworkReply* reply = manager.get(request);

            QEventLoop loop;
            QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            loop.exec();

            std::vector<Domain::Session> sessions;

            if (reply->error() == QNetworkReply::NoError) {
                QByteArray response = reply->readAll();
                QJsonDocument doc = QJsonDocument::fromJson(response);

                if (doc.isArray()) {
                    QJsonArray array = doc.array();
                    for (const QJsonValue& value : array) {
                        QJsonObject obj = value.toObject();

                        // Получаем объект movie из JSON
                        QJsonObject movieObj = obj["movie"].toObject();

                        // Создаем объект Movie
                        Domain::Movie movie(
                            movieObj["name"].toString().toStdString(),
                            movieObj["age"].toInt(),
                            movieObj["genre"].toString().toStdString(),
                            movieObj["rating"].toDouble()
                        );

                        // Создаем объект Session
                        Domain::Session session(
                            obj["id"].toInt(),
                            movie,
                            obj["sessionDate"].toString().toStdString(),
                            obj["price"].toDouble()
                        );

                        sessions.push_back(session);
                    }
                }
            }

            reply->deleteLater();
            return sessions;
        }

        std::pair<std::string, std::string> getAnonymousAuth() override {
            QNetworkAccessManager manager;
            QNetworkRequest request(QUrl(baseUrl_ + "/anon_auth"));
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

            QNetworkReply* reply = manager.get(request);

            QEventLoop loop;
            QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
            loop.exec();

            std::pair<std::string, std::string> result;

            if (reply->error() == QNetworkReply::NoError) {
                QByteArray response = reply->readAll();
                QJsonDocument doc = QJsonDocument::fromJson(response);

                if (doc.isObject()) {
                    QJsonObject obj = doc.object();
                    result.first = obj["username"].toString().toStdString();
                    result.second = obj["password"].toString().toStdString();
                }
            }

            reply->deleteLater();
            return result;
        }

    private:
        QString baseUrl_;
    };
}