/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *mainFrame;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *chatPage;
    QGridLayout *gridLayout;
    QTextEdit *roomTextEdit;
    QLineEdit *sayLineEdit;
    QListWidget *userListWidget;
    QPushButton *sayButton;
    QPushButton *logoutButton;
    QLabel *titleLabel;
    QLabel *loginLabel;
    QWidget *loginPage;
    QGridLayout *gridLayout_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    QFrame *loginFrame;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *loginButton;
    QLabel *warning_label;
    QLineEdit *userLineEdit;
    QLineEdit *passwordLineEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        // Выровнить код
        MainWindow->setStyleSheet(QLatin1String("\n"
"#titleLabel {\n"
"background: white;\n"
"color: blue;\n"
"font-size: 20px;\n"
"border: none;\n"
"border-bottom:  1px solid black;\n"
"padding: 5px;\n"
"}\n"
"\n"
"#mainFrame {\n"
"border: none;\n"
"background: white;\n"
"}\n"
"\n"
"#loginFrame {\n"
"background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ddf, stop: 1 #aaf);\n"
"border: 1px solid gray;\n"
"padding: 10px;\n"
"border-radius: 25px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        mainFrame = new QFrame(centralwidget);
        mainFrame->setObjectName(QStringLiteral("mainFrame"));
        mainFrame->setFrameShape(QFrame::StyledPanel);
        verticalLayout_2 = new QVBoxLayout(mainFrame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        stackedWidget = new QStackedWidget(mainFrame);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        chatPage = new QWidget();
        chatPage->setObjectName(QStringLiteral("chatPage"));
        gridLayout = new QGridLayout(chatPage);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        roomTextEdit = new QTextEdit(chatPage);
        roomTextEdit->setObjectName(QStringLiteral("roomTextEdit"));
        roomTextEdit->setReadOnly(true);

        gridLayout->addWidget(roomTextEdit, 1, 0, 1, 1);

        sayLineEdit = new QLineEdit(chatPage);
        sayLineEdit->setObjectName(QStringLiteral("sayLineEdit"));

        gridLayout->addWidget(sayLineEdit, 2, 0, 1, 2);

        userListWidget = new QListWidget(chatPage);
        userListWidget->setObjectName(QStringLiteral("userListWidget"));

        gridLayout->addWidget(userListWidget, 1, 1, 1, 2);

        sayButton = new QPushButton(chatPage);
        sayButton->setObjectName(QStringLiteral("sayButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sayButton->sizePolicy().hasHeightForWidth());
        sayButton->setSizePolicy(sizePolicy);
        sayButton->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(sayButton, 2, 2, 1, 1);

        logoutButton = new QPushButton(chatPage);
        logoutButton->setObjectName(QStringLiteral("logoutButton"));

        gridLayout->addWidget(logoutButton, 0, 2, 1, 1);

        titleLabel = new QLabel(chatPage);
        titleLabel->setObjectName(QStringLiteral("titleLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(titleLabel, 0, 0, 1, 1);

        loginLabel = new QLabel(chatPage);
        loginLabel->setObjectName(QStringLiteral("loginLabel"));

        gridLayout->addWidget(loginLabel, 0, 1, 1, 1);

        stackedWidget->addWidget(chatPage);
        loginPage = new QWidget();
        loginPage->setObjectName(QStringLiteral("loginPage"));
        gridLayout_3 = new QGridLayout(loginPage);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalSpacer = new QSpacerItem(223, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(223, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 1, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_3->addItem(verticalSpacer, 0, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 267, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_2, 3, 1, 1, 1);

        loginFrame = new QFrame(loginPage);
        loginFrame->setObjectName(QStringLiteral("loginFrame"));
        sizePolicy.setHeightForWidth(loginFrame->sizePolicy().hasHeightForWidth());
        loginFrame->setSizePolicy(sizePolicy);
        loginFrame->setMinimumSize(QSize(300, 0));
        gridLayout_2 = new QGridLayout(loginFrame);
        gridLayout_2->setSpacing(20);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label = new QLabel(loginFrame);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(loginFrame);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        sizePolicy.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
        loginButton->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(loginButton, 2, 3, 1, 1);

        warning_label = new QLabel(loginFrame);
        warning_label->setObjectName(QStringLiteral("warning_label"));

        gridLayout_2->addWidget(warning_label, 2, 0, 1, 3);

        userLineEdit = new QLineEdit(loginFrame);
        userLineEdit->setObjectName(QStringLiteral("userLineEdit"));

        gridLayout_2->addWidget(userLineEdit, 0, 1, 1, 3);

        passwordLineEdit = new QLineEdit(loginFrame);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));

        gridLayout_2->addWidget(passwordLineEdit, 1, 1, 1, 3);


        gridLayout_3->addWidget(loginFrame, 1, 1, 1, 1);

        stackedWidget->addWidget(loginPage);

        verticalLayout_2->addWidget(stackedWidget);


        verticalLayout->addWidget(mainFrame);

        MainWindow->setCentralWidget(centralwidget);
        QWidget::setTabOrder(userLineEdit, roomTextEdit);
        QWidget::setTabOrder(roomTextEdit, userListWidget);
        QWidget::setTabOrder(userListWidget, sayLineEdit);
        QWidget::setTabOrder(sayLineEdit, sayButton);

        retranslateUi(MainWindow);
        QObject::connect(sayLineEdit, SIGNAL(returnPressed()), sayButton, SLOT(animateClick()));
        QObject::connect(userLineEdit, SIGNAL(returnPressed()), loginButton, SLOT(animateClick()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        sayButton->setText(QApplication::translate("MainWindow", "Say", 0));
        logoutButton->setText(QApplication::translate("MainWindow", "logout", 0));
        titleLabel->setText(QApplication::translate("MainWindow", "BytePlusOne", 0));
        loginLabel->setText(QString());
        label->setText(QApplication::translate("MainWindow", "User name:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Password:", 0));
        loginButton->setText(QApplication::translate("MainWindow", "Login", 0));
        warning_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
