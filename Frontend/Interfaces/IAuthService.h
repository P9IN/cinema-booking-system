#pragma once
#include <string>

namespace Interfaces {
    class IAuthService {
    public:
        virtual ~IAuthService() = default;

        struct Credentials {
            std::string username;
            std::string password;
            bool isValid() const { return !username.empty() && !password.empty(); }
        };

        // Получение сохраненных учетных данных
        virtual Credentials getCredentials() = 0;
        
        // Сохранение учетных данных
        virtual void saveCredentials(const Credentials& credentials) = 0;
        
        // Получение токена авторизации
        virtual std::string getAuthToken() = 0;
        
        // Проверка наличия сохраненных учетных данных
        virtual bool hasStoredCredentials() = 0;
    };
} 