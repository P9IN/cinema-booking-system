#pragma once
#include <QDialog>
#include <memory>
#include "../Interfaces/IUserProfile.h"
#include "ui_userForm.h"

namespace UI {
    class UserProfileDialog : public QDialog {
        Q_OBJECT

    public:
        UserProfileDialog(std::shared_ptr<Interfaces::IUserProfile> userProfile,
                         QWidget* parent = nullptr);
        ~UserProfileDialog();

    private slots:
        void onSaveClicked();
        void onCancelClicked();
        void validateInput();

    private:
        void setupUI();
        void loadUserData();
        void updateUI();
        bool validateAge(const std::string& age) const;
        bool validatePhoneNumber(const std::string& phone) const;

        Ui::Dialog* ui;
        std::shared_ptr<Interfaces::IUserProfile> userProfile_;
        bool isValid_ = false;
    };
} 