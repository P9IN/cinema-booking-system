#pragma once
#include <QtWidgets/QMainWindow>
#include <QComboBox>
#include <QTableWidget>
#include <memory>
#include "../Interfaces/IUIService.h"
#include "../Interfaces/ISessionService.h"
#include "../Interfaces/IUserProfile.h"
#include "../Interfaces/IPaymentService.h"
#include "ui_examTrue.h"

namespace UI {
    class MainWindow : public QMainWindow, public Interfaces::IUIService {
        Q_OBJECT

    public:
        MainWindow(
            std::shared_ptr<Interfaces::ISessionService> sessionService,
            std::shared_ptr<Interfaces::IUserProfile> userProfile,
            std::shared_ptr<Interfaces::IPaymentService> paymentService,
            QWidget* parent = nullptr
        );
        ~MainWindow();

        // IUIService implementation
        void updateMovieList(const std::vector<Domain::Session>& sessions) override;
        void updateUserBookings(const std::vector<Domain::Session>& bookings) override;
        void showError(const std::string& message) override;
        void showSuccess(const std::string& message) override;
        std::string getCurrentDate() const override;
        std::string getSelectedMovie() const override;
        std::string getSelectedTime() const override;

    private slots:
        void onDateChanged(int index);
        void onBookButtonClicked();
        void onMovieSelectionChanged();

    private:
        void setupUI();
        void loadMovies();
        void updateSessionTable(const std::vector<Domain::Session>& sessions);
        void handleBookingResult(bool success, const std::string& movieName);

        Ui::examTrueClass* ui;
        std::shared_ptr<Interfaces::ISessionService> sessionService_;
        std::shared_ptr<Interfaces::IUserProfile> userProfile_;
        std::shared_ptr<Interfaces::IPaymentService> paymentService_;
        
        std::vector<std::string> dates_ = {"Today", "Tomorrow", "Day after tomorrow"};
        std::string selectedMovie_;
        std::string selectedTime_;
    };
} 