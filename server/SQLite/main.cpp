#include <iostream>
#include <string.h>
#include "sqlite3.h"

// возвращает id первого пользователя соответствующего логину
// можно использовать для определения уникальности пользователя
int GetUserID(std::string _log){
    char *db_name="CppProgramTestDB.sl3";
    sqlite3 *db;
    char *zErrMsg = 0;
    int error;

    // Создание или открытие БД
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if ( error )
    {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }

    // скрипт извлечения данных из таблицы
    std::string SelectValuesSqlText = "SELECT id from Users where login = '" + _log + "'";

    int length = SelectValuesSqlText.length();
    char * CharValue = new char [length];
    strcpy( CharValue, SelectValuesSqlText.c_str() );

    sqlite3_stmt    *res;
    const char      *tail;

    error = sqlite3_prepare_v2(db, CharValue , 1000, &res, &tail);
    if ( error )
    {
        std::cout << "Can't select data: " << sqlite3_errmsg(db) << std::endl;
    }

    int id = -1;
    while (sqlite3_step(res) == SQLITE_ROW && id == -1){
        int LengthResult = strlen((char*)sqlite3_column_text(res, 0));
        std::string sID = "";
        for (int i = 0; i < LengthResult; ++i){
            sID += sqlite3_column_text(res, 0)[i];
        }
        id = std::atoi(sID.c_str());
    }

    sqlite3_close(db);
    return id;
}

// данную функцию надо оборачивать как показано в main чтобы избежать дублирования логинов
void InsertUser(std::string _log, std::string _pass){

    char *db_name="CppProgramTestDB.sl3";
    sqlite3 *db;
    char *zErrMsg = 0;
    int error;

    // Создание или открытие БД
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if ( error )
    {
        std::cout << "Can't open database: "
                  << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
    }

    // скрипт добавления данных в таблицу
    std::string InsertValueSqlText = "insert into Users(login, password) VALUES ('"
                                     + _log + "', '" + _pass + "');";
    //std::cout << InsertValueSqlText;

    int length = InsertValueSqlText.length();
    char * CharValue = new char [length];
    strcpy( CharValue, InsertValueSqlText.c_str() );

    error = sqlite3_exec(db, CharValue, NULL, 0, &zErrMsg);
    // добавление пароля и логина в таблицу пользователей
    if ( error )
    {
        std::cout << "Values wasn't inserted in table Users" << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }
    sqlite3_close(db);
}


void CreateTable (){
    char *db_name="CppProgramTestDB.sl3";
    sqlite3 *db;
    char *zErrMsg = 0;
    int error;

    // Создание или открытие БД
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if ( error )
    {
        std::cout << "Can't open database: "
                  << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
    }

    // создаем таблицу пользователей
    char * CreateTableSqlText =  "CREATE TABLE Users "
            "(id integer PRIMARY KEY, login TEXT,"
                    "password TEXT);";

    error = sqlite3_exec(db, CreateTableSqlText, NULL, 0, &zErrMsg);
    if ( error )
    {
        std::cout << "Table Users was created "
                  << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
    }
    sqlite3_close(db);
}


void GetAllUsers (){
    char *db_name="CppProgramTestDB.sl3";
    sqlite3 *db;
    char *zErrMsg = 0;
    int error;

    // Создание или открытие БД
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if ( error )
    {
        std::cout << "Can't open database: "
                  << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
    }

    char * CharValue = "select * from Users";

    sqlite3_stmt    *res;
    const char      *tail;

    error = sqlite3_prepare_v2(db, CharValue , 1000, &res, &tail);
    if ( error )
    {
        std::cout << "Can't select data: " << sqlite3_errmsg(db) << std::endl;
    }

    // отображение строк на экране
    std::cout << "Display result from Users" << std::endl;
    int     rec_count = 0;
    while (sqlite3_step(res) == SQLITE_ROW)
    {
        std::cout << "Row (" << rec_count << "):" << sqlite3_column_text(res, 0) << " ";
        std::cout << sqlite3_column_text(res, 1) << " ";
        std::cout << sqlite3_column_text(res, 2) << std::endl;

        rec_count++;
    }
}


// возвращает пароль пользователя по переданному логину
// можно использовать для определения, правильный ли логин и пароль ввел пользователь.
std::string GetUserPassword(std::string _log){
    char *db_name="CppProgramTestDB.sl3";
    sqlite3 *db;
    char *zErrMsg = 0;
    int error;

    // Создание или открытие БД
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if ( error )
    {
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    }

    // скрипт извлечения данных из таблицы
    std::string SelectValuesSqlText = "SELECT password from Users where login = '" + _log + "'";

    int length = SelectValuesSqlText.length();
    char * CharValue = new char [length];
    strcpy( CharValue, SelectValuesSqlText.c_str() );

    sqlite3_stmt    *res;
    const char      *tail;

    error = sqlite3_prepare_v2(db, CharValue , 1000, &res, &tail);
    if ( error )
    {
        std::cout << "Can't select data: " << sqlite3_errmsg(db) << std::endl;
    }

    // можно задать любое значение для проверки верный ли логин ввел пользователь
    std::string password = "";
    while (sqlite3_step(res) == SQLITE_ROW && password == ""){
        int LengthResult = strlen((char*)sqlite3_column_text(res, 0));
        std::string sPass = "";
        for (int i = 0; i < LengthResult; ++i) {
            sPass += sqlite3_column_text(res, 0)[i];
        }
        password = sPass;
    }

    sqlite3_close(db);
    return password;
}

int main() {
    // вызывается один раз

    // CreateTable();

    GetAllUsers();

    std::string Login = "Log";
    std::string Password = "Pass";

    int UserID = GetUserID(Login);
    if (UserID == -1){
        std::cout << "Пользователя с логином " << Login << " найти не удалось " << std::endl;
        //InsertUser(Login, Password);
    }

    std::string ReturnPassword = GetUserPassword("Login");
    // проверка, есть ли логин в базе
    if (ReturnPassword == ""){
        std::cout << "Логин " << " Login " << " не найден в базе";
    }

    ReturnPassword = GetUserPassword(Login);
    if (ReturnPassword == Password){
        std::cout << "Пароль введенный пользователем совпадает с паролем в базе и равен "
                  << ReturnPassword;
    }else{
        std::cout << "Пароль введенный пользователем = "
                  << ReturnPassword << " и не совпадает с паролем в базе";
    }


    std::cout << "\n current user ID = " << UserID << std::endl;

    return 0;
}