#include <QtWidgets/QApplication>
#include <memory>
#include "UI/MainWindow.h"
#include "Services/SessionService.h"
#include "Services/PaymentService.h"
#include "Services/UserProfile.h"
#include "Services/ApiService.h"
#include "Services/AuthService.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto apiService = std::make_shared<Services::ApiService>();
    auto authService = std::make_shared<Services::AuthService>(apiService);
    auto sessionService = std::make_shared<Services::SessionService>(apiService, authService);
    auto paymentService = std::make_shared<Services::PaymentService>();
    auto userProfile = std::make_shared<Services::UserProfile>("user1");

    UI::MainWindow w(sessionService, userProfile, paymentService);
    w.show();

    return a.exec();
}