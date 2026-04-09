#pragma once
#include <vector>
#include <string>
#include "../Domain/Session.h"

namespace Interfaces {
    class IApiService {
    public:
        virtual ~IApiService() = default;
        
        // Получение сессий с сервера
        virtual std::vector<Domain::Session> getSessions(const std::string& authToken) = 0;
        
        // Получение анонимных данных для авторизации
        virtual std::pair<std::string, std::string> getAnonymousAuth() = 0;
    };
} 