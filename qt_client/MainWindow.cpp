#include "MainWindow.h"

#include <QRegExp>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // создает все виджеты из ui
    setupUi(this);

    // Показываем login page при запуске
    stackedWidget->setCurrentWidget(loginPage);

    // инициализируем сокет но не конектимся до нажатия на кнопку
    socket = new QTcpSocket(this);

    //таким образом мы говорим qt как читать и конектится
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
}

// Вызывается при нажатии на кнопку Login
void MainWindow::on_loginButton_clicked()
{
    warning_label->clear();
    // Коннектится к серверу на порту 4200
    // если поле логина остается пустым, то показывает сообщение пользователю
    if(!userLineEdit->text().isEmpty()) {
        warning_label->setText("CONNECTION SET");
        socket->connectToHost("localhost", 4200);
    } else {
        warning_label->setText(QString("YOU NOT ENTERED LOGIN"));
    }
}
//Вызывается при нажатии на кнопку Logout
void MainWindow::on_logoutButton_clicked()
{
    stackedWidget->setCurrentWidget(loginPage);
    socket->write(QString("/"+userLineEdit->text()+":logout").toUtf8());
    socket->disconnectFromHost();
    qDebug << "DISCONNECTED";
}

// Вызывается при нажатии кнопки Say
void MainWindow::on_sayButton_clicked()
{
    QString message = sayLineEdit->text().trimmed();

    // ПОсылаем сообщение на сервер только если не пусто
    if(!message.isEmpty()) {
        socket->write(QString(userLineEdit->text()+":" + message + "\n").toUtf8());
        qDebug() << "MESSAGE SEND";
    }

    sayLineEdit->clear();
    sayLineEdit->setFocus();
}

//Функция вызывается, когда сервер присылает нам сообщение
void MainWindow::readyRead()
{
    qDebug() << "GET MESSAGE";
    while(socket->canReadLine()) {
        QString line = QString::fromUtf8(socket->readLine()).trimmed();

        //регулярки для распознавания сообещний с сервера

        //"username:The message"
        QRegExp messageRegex("^([^:]+):(.*)$");

        //список пользователей
        QRegExp usersRegex("^/users:(.*)$");

        if(usersRegex.indexIn(line) != -1) {
            // Обновляем юзер лист справа
            QStringList users = usersRegex.cap(1).split(",");
            userListWidget->clear();
            foreach(QString user, users)
                new QListWidgetItem(QPixmap(":/user.png"), user, userListWidget);
        } else if(messageRegex.indexIn(line) != -1) {
            qDebug() << "I NEED TO SHOW YOU SOMETHING";
            QString user = messageRegex.cap(1);
            QString message = messageRegex.cap(2);

            roomTextEdit->append("<b>" + user + "</b>: " + message + "\n");
        }
    }
}

// вызывается при удачном присоединении к чату
void MainWindow::connected()
{
    qDebug() << "CONNECTED";
    // Переключение на страницу чата:
    warning_label->clear();
    stackedWidget->setCurrentWidget(chatPage);
    loginLabel->setText(QString(userLineEdit->text()));
    // Посылаем наш логин серверу
    socket->write(QString("/me:" + userLineEdit->text() + "\n").toUtf8());
}
