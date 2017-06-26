#ifdef WIN32
#define _WIN32_WINNT 0x0501
#include <stdio.h>
#endif

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "SQL.h"

//=================================
boost::asio::io_service service;
using namespace boost::asio;
using namespace boost::posix_time;
using boost::system::error_code;
void send_to_all (std::string &str);

//===================================
// Класс клиента
//===================================
struct talk_to_client : boost::enable_shared_from_this<talk_to_client> {
    // Конструктор.
    talk_to_client(): sock_(service) {}
    // Методы.
    void process_request();
    void on_login(const std::string & msg);
    void on_clients();
    void write(const std::string & msg);
    std::string username() const { return username_; }
    void answer_to_client();
    void set_clients_changed() { clients_changed_ = true; }
    ip::tcp::socket & sock() { return sock_; }
    void stop() { boost::system::error_code err; sock_.close(err); }
    void read_request();
    std::string username_;
    std::string password_;
private:
    ip::tcp::socket sock_;  // Сокет клиента.
    enum { max_msg = 1024 };
    int already_read_;  // Размер прочитанного сообщения.
    char buff_[max_msg];
    // bool started_;
    bool clients_changed_;
    ptime last_ping;
};

// Принимаем сообщение от клиета.
void talk_to_client :: answer_to_client() {
    // Обработка ошибки чтения из сокета.
    try {
        std::cout<<"answer to client"<<std::endl;  // Лишнее
        read_request();
        process_request();
    }
    catch (boost::system::system_error&) {
        std::cout<<"stop   ";
        stop();
    }
}

// Читаем из сокета сообщение от клиента.
void talk_to_client :: read_request() {
    if ( sock_.available())
        already_read_ += sock_.read_some(
                buffer(buff_ + already_read_, max_msg - already_read_));
}

// Массив клиентов.
typedef boost::shared_ptr<talk_to_client> client_ptr;
typedef std::vector<client_ptr> array;
array clients;
boost::recursive_mutex cs; // Thread-safe access to clients array.

// Поток, принимающий клиентов.
void accept_thread() {
    ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8004));
    while (true) {
        client_ptr new_(new talk_to_client);
        acceptor.accept(new_->sock());
        boost::recursive_mutex::scoped_lock lk(cs);
        clients.push_back(new_);
    }
}

// Поток, обрабатывающий существующих клиентов.
void handle_clients_thread() {
    while (true) {
        boost::this_thread::sleep( millisec(5000));
        // boost::recursive_mutex::scoped_lock lk(cs);
        for(array::iterator b = clients.begin(),e = clients.end(); b != e; ++b){
            std::cout<<(*b)->username()<<" ";
            (*b)->answer_to_client();
        }
    }
}

// Два потока - принимающий и обрабатывающий.
int main(int argc, char* argv[]) {
    boost::thread_group threads;
    threads.create_thread(accept_thread);
    threads.create_thread(handle_clients_thread);
    threads.join_all();
}

// Обработка запроса.
void talk_to_client:: process_request() {
    bool found_enter = std::find(buff_, buff_ + already_read_, '\n') < buff_ + already_read_;
    if (!found_enter) // Если сообщение не полное.
        return;
    size_t pos = std::find(buff_, buff_ + already_read_, '\n') - buff_;
    std::string msg(buff_, pos);
    std::cout<<msg;  // Лишнее
    std::copy(buff_ + already_read_, buff_ + max_msg, buff_);
    already_read_ -= pos + 1;
    if (msg.find("login ") == 0) on_login(msg);
    else if ( msg.find("ask_clients") == 0) on_clients();
    else send_to_all(msg); // !!!!!!!!!!!!!!!!!!!!!!!!!
}

// Запонминаем клиента (логин).
void talk_to_client::on_login(const std::string & msg) {
    std::istringstream in(msg);
    in >> username_ >> password_; //in >> username_ >> username_;
    // Работа с БД.
    GetAllUsers();
    int UserID = GetUserID(username_);
    if (UserID == -1) {
        std::cout << "Пользователя с логином " << username_ << " найти не удалось " << std::endl;
        InsertUser(username_, password_);
        write("Создана учетная запись\n");
        set_clients_changed(); // update_clients_changed();
    } else {
        std::string ReturnPassword = GetUserPassword(username_);
        // Проверка, есть ли логин в базе.
        if (ReturnPassword == ""){
            std::cout << "Логин " << " Login " << " не найден в базе";
            write("Неверный логин или пароль\n");
            return;
        }
        ReturnPassword = GetUserPassword(username_);
        if (ReturnPassword == password_){
            std::cout << "Пароль введенный пользователем совпадает с паролем в базе и равен "
                      << ReturnPassword;
            write("Успешная авторизация\n");
            set_clients_changed(); // update_clients_changed();
        } else {
            std::cout << "Пароль введенный пользователем = "
                      << ReturnPassword << " и не совпадает с паролем в базе";
            write("Неверный логин или пароль\n");
        }

    }
}

// Рассылка юзеров.
void talk_to_client::on_clients() {
    std::string msg, resultMsg;
    {
        // boost::recursive_mutex::scoped_lock lk(cs);
        for( array::const_iterator b = clients.begin(), e = clients.end() ;b != e; ++b)
            msg += (*b)->username() + " ";
    }
    resultMsg = "clients " + msg;
    send_to_all(resultMsg);
    // write("clients " + msg + "\n");
}

// Запись в сокет.
void talk_to_client::write(const std::string & msg) {
    sock_.write_some(buffer(msg));
}

// Групповая рассылка.
void send_to_all (std::string &str){
    str += "\n";
    std::cout << "Групповая рассылка: " << str << std::endl;
    for(array::iterator b = clients.begin(),e = clients.end(); b != e; ++b){
        if (str.find((*b)->username_) != 0)
        (*b)->write(str);
    }
}
