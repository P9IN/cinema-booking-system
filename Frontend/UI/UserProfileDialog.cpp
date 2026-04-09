#include "UserProfileDialog.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

namespace UI {
    UserProfileDialog::UserProfileDialog(
        std::shared_ptr<Interfaces::IUserProfile> userProfile,
        QWidget* parent
    )
        : QDialog(parent)
        , ui(new Ui::Dialog)
        , userProfile_(std::move(userProfile))
    {
        ui->setupUi(this);
        setupUI();
        loadUserData();
    }

    UserProfileDialog::~UserProfileDialog() {
        delete ui;
    }

    void UserProfileDialog::setupUI() {
        // Connect signals
        connect(ui->pushButton, &QPushButton::clicked,
                this, &UserProfileDialog::onSaveClicked);
        connect(ui->pushButton_2, &QPushButton::clicked,
                this, &UserProfileDialog::onCancelClicked);
        
        // Connect validation signals
        connect(ui->lineEdit, &QLineEdit::textChanged,
                this, &UserProfileDialog::validateInput);
        connect(ui->lineEdit_2, &QLineEdit::textChanged,
                this, &UserProfileDialog::validateInput);

        // Set validators
        QRegularExpression ageRegex("^\\d{1,3}$");
        ui->lineEdit->setValidator(new QRegularExpressionValidator(ageRegex, this));

        QRegularExpression phoneRegex("^\\d{10,12}$");
        ui->lineEdit_2->setValidator(new QRegularExpressionValidator(phoneRegex, this));
    }

    void UserProfileDialog::loadUserData() {
        // Load existing user data if available
        if (!userProfile_->getAge().empty()) {
            ui->lineEdit->setText(QString::fromStdString(userProfile_->getAge()));
        }
        
        if (userProfile_->getPhoneNumber() != 0) {
            ui->lineEdit_2->setText(QString::number(userProfile_->getPhoneNumber()));
        }

        validateInput();
    }

    void UserProfileDialog::validateInput() {
        QString age = ui->lineEdit->text();
        QString phone = ui->lineEdit_2->text();

        bool isAgeValid = validateAge(age.toStdString());
        bool isPhoneValid = validatePhoneNumber(phone.toStdString());

        isValid_ = isAgeValid && isPhoneValid;

        // Update UI based on validation
        QPalette agePalette = ui->lineEdit->palette();
        agePalette.setColor(QPalette::Text, isAgeValid ? Qt::black : Qt::red);
        ui->lineEdit->setPalette(agePalette);

        QPalette phonePalette = ui->lineEdit_2->palette();
        phonePalette.setColor(QPalette::Text, isPhoneValid ? Qt::black : Qt::red);
        ui->lineEdit_2->setPalette(phonePalette);

        ui->pushButton->setEnabled(isValid_);
    }

    bool UserProfileDialog::validateAge(const std::string& age) const {
        if (age.empty()) return false;
        
        try {
            int ageNum = std::stoi(age);
            return ageNum >= 0 && ageNum <= 150;
        }
        catch (...) {
            return false;
        }
    }

    bool UserProfileDialog::validatePhoneNumber(const std::string& phone) const {
        if (phone.empty()) return false;
        
        try {
            long long phoneNum = std::stoll(phone);
            return phone.length() >= 10 && phone.length() <= 12;
        }
        catch (...) {
            return false;
        }
    }

    void UserProfileDialog::onSaveClicked() {
        if (!isValid_) {
            QMessageBox::warning(this, "Validation Error",
                               "Please correct the input fields before saving.");
            return;
        }

        // Save user data
        userProfile_->setAge(ui->lineEdit->text().toStdString());
        userProfile_->setPhoneNumber(ui->lineEdit_2->text().toLongLong());

        accept();
    }

    void UserProfileDialog::onCancelClicked() {
        reject();
    }
} 