#pragma once
#include <unordered_map>
#include <memory>
#include "../Interfaces/ISessionService.h"
#include "../Interfaces/IApiService.h"
#include "../Interfaces/IAuthService.h"

namespace Services {
    class SessionService : public Interfaces::ISessionService {
    public:
        SessionService(std::shared_ptr<Interfaces::IApiService> apiService,
            std::shared_ptr<Interfaces::IAuthService> authService)
            : apiService_(std::move(apiService))
            , authService_(std::move(authService))
        {
            refreshSessions();
        }

        std::vector<Domain::Session> getSessionsByDate(const std::string& date) const override {
            std::vector<Domain::Session> result;
            auto it = sessions_.find(date);
            if (it != sessions_.end()) {
                result = it->second;
            }
            return result;
        }

        std::vector<Domain::Session> getAvailableSessions() const override {
            std::vector<Domain::Session> result;
            for (const auto& [_, dateSessions] : sessions_) {
                for (const auto& session : dateSessions) {
                    if (session.hasAvailableSeats()) {
                        result.push_back(session);
                    }
                }
            }
            return result;
        }

        bool bookSession(const std::string& movieName,
            const std::string& date,
            const std::string& userId) override {
            auto dateKey = extractDateFromTime(date);
            auto it = sessions_.find(dateKey);
            if (it == sessions_.end()) {
                return false;
            }

            auto& dateSessions = it->second;
            for (auto& session : dateSessions) {
                if (session.getMovie().getName() == movieName &&
                    session.getDate().find(date) != std::string::npos &&
                    session.hasAvailableSeats()) {
                    session.decrementSeats();
                    bookings_[userId].push_back(session);
                    return true;
                }
            }
            return false;
        }

        bool cancelBooking(const std::string& movieName,
            const std::string& date,
            const std::string& userId) override {
            auto it = bookings_.find(userId);
            if (it == bookings_.end()) {
                return false;
            }

            auto& userBookings = it->second;
            auto bookingIt = std::find_if(userBookings.begin(), userBookings.end(),
                [&](const Domain::Session& s) {
                    return s.getMovie().getName() == movieName &&
                        s.getDate().find(date) != std::string::npos;
                });

            if (bookingIt == userBookings.end()) {
                return false;
            }

            auto dateKey = extractDateFromTime(date);
            auto sessionIt = sessions_.find(dateKey);
            if (sessionIt != sessions_.end()) {
                for (auto& session : sessionIt->second) {
                    if (session.getMovie().getName() == movieName &&
                        session.getDate().find(date) != std::string::npos) {
                        session.setAvailableSeats(session.getAvailableSeats() + 1);
                        break;
                    }
                }
            }

            userBookings.erase(bookingIt);
            return true;
        }

    private:
        void refreshSessions() {
            auto authToken = authService_->getAuthToken();
            if (!authToken.empty()) {
                auto serverSessions = apiService_->getSessions(authToken);
                for (const auto& session : serverSessions) {
                    auto dateKey = extractDateFromTime(session.getDate());
                    sessions_[dateKey].push_back(session);
                }
            }
        }

        std::string extractDateFromTime(const std::string& time) const {
            if (time.empty() || time.length() < 10) {
                return "";
            }
            return time.substr(0, 10);
        }

        std::shared_ptr<Interfaces::IApiService> apiService_;
        std::shared_ptr<Interfaces::IAuthService> authService_;
        std::unordered_map<std::string, std::vector<Domain::Session>> sessions_;
        std::unordered_map<std::string, std::vector<Domain::Session>> bookings_;
    };
}