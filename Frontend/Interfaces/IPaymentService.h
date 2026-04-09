#pragma once
#include <string>

namespace Interfaces {
    class IPaymentService {
    public:
        virtual ~IPaymentService() = default;

        enum class PaymentMethod {
            Card,
            Cash
        };

        struct PaymentDetails {
            double amount;
            std::string currency;
            std::string description;
            PaymentMethod method;
        };

        // Payment operations
        virtual bool processPayment(const PaymentDetails& details) = 0;
        virtual bool refundPayment(const std::string& paymentId) = 0;
        virtual bool validatePaymentMethod(PaymentMethod method) = 0;
        
        // Payment status
        virtual std::string getPaymentStatus(const std::string& paymentId) const = 0;
    };
} 