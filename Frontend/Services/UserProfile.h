#pragma once
#include <string>
#include <regex>
#include "../Interfaces/IUserProfile.h"

namespace Services {
    class UserProfile : public Interfaces::IUserProfile {
    public:
        explicit UserProfile(std::string userId)
            : userId_(std::move(userId)) {}

        std::string getAge() const override {
            return age_;
        }

        void setAge(const std::string& age) override {
            age_ = age;
        }

        long long getPhoneNumber() const override {
            return phoneNumber_;
        }

        void setPhoneNumber(long long number) override {
            phoneNumber_ = number;
        }

        std::string getUserId() const override {
            return userId_;
        }

        bool isProfileComplete() const override {
            return !age_.empty() && phoneNumber_ != 0;
        }

        bool isAgeValid() const override {
            try {
                int age = std::stoi(age_);
                return age >= 0 && age <= 150; // Reasonable age range
            }
            catch (...) {
                return false;
            }
        }

        bool isPhoneNumberValid() const override {
            // Simple validation: check if number has 10-12 digits
            std::string phoneStr = std::to_string(phoneNumber_);
            return phoneStr.length() >= 10 && phoneStr.length() <= 12;
        }

    private:
        std::string userId_;
        std::string age_;
        long long phoneNumber_ = 0;
    };
} 