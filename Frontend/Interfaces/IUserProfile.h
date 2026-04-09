#pragma once
#include <string>

namespace Interfaces {
    class IUserProfile {
    public:
        virtual ~IUserProfile() = default;

        // Profile information
        virtual std::string getAge() const = 0;
        virtual void setAge(const std::string& age) = 0;
        virtual long long getPhoneNumber() const = 0;
        virtual void setPhoneNumber(long long number) = 0;
        virtual std::string getUserId() const = 0;
        
        // Profile validation
        virtual bool isProfileComplete() const = 0;
        virtual bool isAgeValid() const = 0;
        virtual bool isPhoneNumberValid() const = 0;
    };
} 