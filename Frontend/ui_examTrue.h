#ifndef UI_EXAMTRUE_H
#define UI_EXAMTRUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHeaderView>

namespace Ui {
    class examTrueClass {
    public:
        QWidget* centralWidget;
        QVBoxLayout* mainLayout;
        QHBoxLayout* topLayout;
        QLabel* dateLabel;
        QComboBox* comboBox;
        QTableWidget* tableWidget;
        QPushButton* pushButton;

        void setupUi(QMainWindow* MainWindow) {
            if (MainWindow->objectName().isEmpty())
                MainWindow->setObjectName(QString::fromUtf8("examTrue"));
            MainWindow->resize(900, 600);

            centralWidget = new QWidget(MainWindow);
            centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

            mainLayout = new QVBoxLayout(centralWidget);
            mainLayout->setObjectName(QString::fromUtf8("mainLayout"));

            topLayout = new QHBoxLayout();
            topLayout->setObjectName(QString::fromUtf8("topLayout"));

            dateLabel = new QLabel(centralWidget);
            dateLabel->setObjectName(QString::fromUtf8("dateLabel"));
            dateLabel->setText(QString::fromUtf8("Select Date:"));
            topLayout->addWidget(dateLabel);

            comboBox = new QComboBox(centralWidget);
            comboBox->setObjectName(QString::fromUtf8("comboBox"));
            topLayout->addWidget(comboBox);

            topLayout->addStretch();

            mainLayout->addLayout(topLayout);

            tableWidget = new QTableWidget(centralWidget);
            tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
            tableWidget->setColumnCount(6);

            QStringList headers;
            headers << "Movie" << "Genre" << "Age" << "Rating" << "Date & Time" << "Price";
            tableWidget->setHorizontalHeaderLabels(headers);

            tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
            tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
            tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            mainLayout->addWidget(tableWidget);

            pushButton = new QPushButton(centralWidget);
            pushButton->setObjectName(QString::fromUtf8("pushButton"));
            pushButton->setText(QString::fromUtf8("Book Ticket"));
            mainLayout->addWidget(pushButton);

            MainWindow->setCentralWidget(centralWidget);

            QMetaObject::connectSlotsByName(MainWindow);
        }

        void retranslateUi(QMainWindow* MainWindow) {
            MainWindow->setWindowTitle(QApplication::translate("examTrue", "Movie Booking System", nullptr));
            dateLabel->setText(QApplication::translate("examTrue", "Select Date:", nullptr));
            pushButton->setText(QApplication::translate("examTrue", "Book Ticket", nullptr));
        }
    };
}

namespace Ui {
    class MainWindow : public examTrueClass {};
} // namespace Ui

#endif // UI_EXAMTRUE_H 