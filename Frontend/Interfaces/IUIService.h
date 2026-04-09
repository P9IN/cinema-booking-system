#pragma once
#include <vector>
#include <string>
#include "../Domain/Session.h"

namespace Interfaces {
    class IUIService {
    public:
        virtual ~IUIService() = default;

        // UI update operations
        virtual void updateMovieList(const std::vector<Domain::Session>& sessions) = 0;
        virtual void updateUserBookings(const std::vector<Domain::Session>& bookings) = 0;
        virtual void showError(const std::string& message) = 0;
        virtual void showSuccess(const std::string& message) = 0;

        // UI state
        virtual std::string getCurrentDate() const = 0;
        virtual std::string getSelectedMovie() const = 0;
        virtual std::string getSelectedTime() const = 0;
    };
} 