#ifndef UI_USERFORM_H
#define UI_USERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtGui/QIntValidator>

namespace Ui {
    class Dialog {
    public:
        QVBoxLayout* mainLayout;
        QFormLayout* formLayout;
        QLabel* ageLabel;
        QLineEdit* lineEdit;  // Keep as QLineEdit for compatibility
        QLabel* phoneLabel;
        QLineEdit* lineEdit_2;  // Keep original name
        QHBoxLayout* buttonLayout;
        QPushButton* pushButton;  // Keep original name
        QPushButton* pushButton_2;  // Keep original name
        QLabel* movieInfoLabel;  // Added to show movie info

        void setupUi(QDialog* dialog) {
            if (dialog->objectName().isEmpty())
                dialog->setObjectName(QString::fromUtf8("UserProfileDialog"));
            dialog->resize(400, 250);

            mainLayout = new QVBoxLayout(dialog);
            mainLayout->setObjectName(QString::fromUtf8("mainLayout"));

            // Add movie info label
            movieInfoLabel = new QLabel(dialog);
            movieInfoLabel->setObjectName(QString::fromUtf8("movieInfoLabel"));
            movieInfoLabel->setText(QString::fromUtf8("Movie Information:"));
            movieInfoLabel->setStyleSheet("font-weight: bold;");
            mainLayout->addWidget(movieInfoLabel);

            formLayout = new QFormLayout();
            formLayout->setObjectName(QString::fromUtf8("formLayout"));

            ageLabel = new QLabel(dialog);
            ageLabel->setObjectName(QString::fromUtf8("ageLabel"));
            ageLabel->setText(QString::fromUtf8("Your Age:"));
            formLayout->setWidget(0, QFormLayout::LabelRole, ageLabel);

            lineEdit = new QLineEdit(dialog);
            lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
            // Set validator to only accept numbers
            lineEdit->setValidator(new QIntValidator(1, 120, dialog));
            lineEdit->setText("18");
            formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

            phoneLabel = new QLabel(dialog);
            phoneLabel->setObjectName(QString::fromUtf8("phoneLabel"));
            phoneLabel->setText(QString::fromUtf8("Phone Number:"));
            formLayout->setWidget(1, QFormLayout::LabelRole, phoneLabel);

            lineEdit_2 = new QLineEdit(dialog);
            lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
            formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_2);

            mainLayout->addLayout(formLayout);

            QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
            mainLayout->addItem(verticalSpacer);

            buttonLayout = new QHBoxLayout();
            buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));

            QSpacerItem* horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            buttonLayout->addItem(horizontalSpacer);

            pushButton = new QPushButton(dialog);
            pushButton->setObjectName(QString::fromUtf8("pushButton"));
            pushButton->setText(QString::fromUtf8("Confirm Booking"));
            buttonLayout->addWidget(pushButton);

            pushButton_2 = new QPushButton(dialog);
            pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
            pushButton_2->setText(QString::fromUtf8("Cancel"));
            buttonLayout->addWidget(pushButton_2);

            mainLayout->addLayout(buttonLayout);

            QMetaObject::connectSlotsByName(dialog);
        }

        void retranslateUi(QDialog* dialog) {
            dialog->setWindowTitle(QApplication::translate("UserProfileDialog", "Confirm Booking", nullptr));
            movieInfoLabel->setText(QApplication::translate("UserProfileDialog", "Movie Information:", nullptr));
            ageLabel->setText(QApplication::translate("UserProfileDialog", "Your Age:", nullptr));
            phoneLabel->setText(QApplication::translate("UserProfileDialog", "Phone Number:", nullptr));
            pushButton->setText(QApplication::translate("UserProfileDialog", "Confirm Booking", nullptr));
            pushButton_2->setText(QApplication::translate("UserProfileDialog", "Cancel", nullptr));
        }
    };
}

#endif // UI_USERFORM_H 