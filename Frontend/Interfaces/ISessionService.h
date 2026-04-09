#pragma once
#include <vector>
#include <string>
#include "../Domain/Session.h"

namespace Interfaces {
    class ISessionService {
    public:
        virtual ~ISessionService() = default;

        // Session management
        virtual std::vector<Domain::Session> getSessionsByDate(const std::string& date) const = 0;
        virtual std::vector<Domain::Session> getAvailableSessions() const = 0;

        // Booking operations
        virtual bool bookSession(const std::string& movieName,
            const std::string& startTime,
            const std::string& userId) = 0;
        virtual bool cancelBooking(const std::string& movieName,
            const std::string& startTime,
            const std::string& userId) = 0;
    };
}