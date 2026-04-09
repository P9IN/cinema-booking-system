#include "MainWindow.h"
#include <QMessageBox>
#include <QDateTime>

namespace UI {
    MainWindow::MainWindow(
        std::shared_ptr<Interfaces::ISessionService> sessionService,
        std::shared_ptr<Interfaces::IUserProfile> userProfile,
        std::shared_ptr<Interfaces::IPaymentService> paymentService,
        QWidget* parent
    )
        : QMainWindow(parent)
        , ui(new Ui::examTrueClass)
        , sessionService_(std::move(sessionService))
        , userProfile_(std::move(userProfile))
        , paymentService_(std::move(paymentService))
    {
        ui->setupUi(this);
        setupUI();
        loadMovies();
    }

    MainWindow::~MainWindow() {
        delete ui;
    }

    void MainWindow::setupUI() {
        // Setup date combo box
        ui->comboBox->clear();
        for (const auto& date : dates_) {
            ui->comboBox->addItem(QString::fromStdString(date));
        }

        // Setup table widget
        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setHorizontalHeaderLabels({
            "Movie Name", "Rating", "Start Time", "Genre",
            "Price", "End Time", "Age Limit"
        });

        // Connect signals
        connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &MainWindow::onDateChanged);
        connect(ui->pushButton, &QPushButton::clicked,
                this, &MainWindow::onBookButtonClicked);
        connect(ui->tableWidget, &QTableWidget::itemSelectionChanged,
                this, &MainWindow::onMovieSelectionChanged);
    }

    void MainWindow::loadMovies() {
        auto currentDate = getCurrentDate();
        auto sessions = sessionService_->getSessionsByDate(currentDate);
        updateMovieList(sessions);
    }

    void MainWindow::updateMovieList(const std::vector<Domain::Session>& sessions) {
        updateSessionTable(sessions);
    }

    void MainWindow::updateSessionTable(const std::vector<Domain::Session>& sessions) {
        ui->tableWidget->setRowCount(static_cast<int>(sessions.size()));
        
        int row = 0;
        for (const auto& session : sessions) {
            const auto& movie = session.getMovie();
            
            ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(movie.getName())));
            ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(movie.getRating())));
            ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(session.getDate())));
            ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(movie.getGenre())));
            ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(session.getPrice())));
            ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(session.getDate())));
            ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(movie.getAge())));

            ++row;
        }

        ui->tableWidget->resizeColumnsToContents();
    }

    void MainWindow::updateUserBookings(const std::vector<Domain::Session>& bookings) {
        // This could be implemented to show user's bookings in a separate view
    }

    void MainWindow::showError(const std::string& message) {
        QMessageBox::critical(this, "Error", QString::fromStdString(message));
    }

    void MainWindow::showSuccess(const std::string& message) {
        QMessageBox::information(this, "Success", QString::fromStdString(message));
    }

    std::string MainWindow::getCurrentDate() const {
        int index = ui->comboBox->currentIndex();
        if (index >= 0 && index < dates_.size()) {
            QDate date = QDate::currentDate().addDays(index);
            return date.toString("yyyy-MM-dd").toStdString();
        }
        return QDate::currentDate().toString("yyyy-MM-dd").toStdString();
    }

    std::string MainWindow::getSelectedMovie() const {
        return selectedMovie_;
    }

    std::string MainWindow::getSelectedTime() const {
        return selectedTime_;
    }

    void MainWindow::onDateChanged(int index) {
        loadMovies();
    }

    void MainWindow::onBookButtonClicked() {
        if (!userProfile_->isProfileComplete()) {
            showError("Please complete your profile first");
            return;
        }

        if (selectedMovie_.empty() || selectedTime_.empty()) {
            showError("Please select a movie and time first");
            return;
        }

        // Get the selected session
        auto sessions = sessionService_->getSessionsByDate(getCurrentDate());
        auto it = std::find_if(sessions.begin(), sessions.end(),
            [this](const Domain::Session& session) {
                return session.getMovie().getName() == selectedMovie_ &&
                    session.getDate() == selectedTime_;
            });

        if (it == sessions.end()) {
            showError("Selected session not found");
            return;
        }

        // Process payment
        Interfaces::IPaymentService::PaymentDetails payment{
            it->getPrice(),
            "USD",
            "Movie ticket: " + selectedMovie_,
            Interfaces::IPaymentService::PaymentMethod::Card
        };

        if (paymentService_->processPayment(payment)) {
            // Book the session
            bool success = sessionService_->bookSession(
                selectedMovie_,
                selectedTime_,
                userProfile_->getUserId()
            );
            handleBookingResult(success, selectedMovie_);
        } else {
            showError("Payment failed");
        }
    }

    void MainWindow::onMovieSelectionChanged() {
        auto selectedItems = ui->tableWidget->selectedItems();
        if (!selectedItems.empty()) {
            int row = selectedItems[0]->row();
            selectedMovie_ = ui->tableWidget->item(row, 0)->text().toStdString();
            selectedTime_ = ui->tableWidget->item(row, 2)->text().toStdString();
        }
    }

    void MainWindow::handleBookingResult(bool success, const std::string& movieName) {
        if (success) {
            showSuccess("Successfully booked ticket for " + movieName);
            loadMovies(); // Refresh the movie list
        } else {
            showError("Failed to book ticket for " + movieName);
        }
    }
} 