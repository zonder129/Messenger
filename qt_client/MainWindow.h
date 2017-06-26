#include <QMainWindow>
#include <QTcpSocket>
#include "ui_MainWindow.h"

//класс главного окна нашего приложения, наследуемый от класса главного окна в Qt
class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

    public:

        MainWindow(QWidget *parent=0);

    private slots:

        void on_loginButton_clicked();
        void on_sayButton_clicked();
        void on_logoutButton_clicked();
        void readyRead();
        void connected();

    private:

        QTcpSocket *socket;
        const int HostNumber = 4200;
};
