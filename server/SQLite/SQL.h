//
// Created by olyasur on 26.06.17.
//

#ifndef SERVER_SQL_H
#define SERVER_SQL_H
#endif //SERVER_SQL_H

#include <iostream>
#include <string.h>
#include "sqlite3.h"

// Возвращает id первого пользователя, соответствующего логину.
// Можно использовать для определения уникальности пользователя.
int GetUserID (std::string _log) {
    char *db_name = "CppProgramTestDB.sl3";
    sqlite3 *db;
    // char *zErrMsg = 0;
    int error;
    // Создание или открытие БД.
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if (error) {
        std::cout << "Невозможно открыть базу данных: "
                  << sqlite3_errmsg(db)
                  << std::endl;
    }
    // Скрипт извлечения данных из таблицы.
    std::string SelectValuesSqlText = "SELECT id from Users where login = '" + _log + "'";
    int length = SelectValuesSqlText.length();
    char *CharValue = new char [length];
    strcpy (CharValue, SelectValuesSqlText.c_str());
    sqlite3_stmt *res;
    const char *tail;
    error = sqlite3_prepare_v2(db, CharValue , 1000, &res, &tail);
    if (error) {
        std::cout << "Неверная выборка данных: " << sqlite3_errmsg(db) << std::endl;
    }
    int id = -1;
    while (sqlite3_step(res) == SQLITE_ROW && id == -1) {
        int LengthResult = strlen((char*)sqlite3_column_text(res, 0));
        std::string sID = "";
        for (int i = 0; i < LengthResult; ++i) {
            sID += sqlite3_column_text(res, 0)[i];
        }
        id = std::atoi(sID.c_str());
    }
    sqlite3_close(db);
    return id;
}

// Функция чтобы избежать дублирования логинов.
void InsertUser (std::string _log, std::string _pass) {
    char *db_name = "CppProgramTestDB.sl3";
    sqlite3 *db;
    char *zErrMsg = 0;
    int error;
    // Создание или открытие БД.
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if (error) {
        std::cout << "Невозможно открыть базу данных: "
                  << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
    }
    // Скрипт добавления данных в таблицу.
    std::string InsertValueSqlText = "insert into Users(login, password) VALUES ('"
                                     + _log + "', '" + _pass + "');";
    //std::cout << InsertValueSqlText;
    int length = InsertValueSqlText.length();
    char * CharValue = new char [length];
    strcpy( CharValue, InsertValueSqlText.c_str() );
    error = sqlite3_exec(db, CharValue, NULL, 0, &zErrMsg);
    // Добавление пароля и логина в таблицу пользователей.
    if (error) {
        std::cout << "Невозможно добавление данных значений в таблицу Users" << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
    }
    sqlite3_close(db);
}

// Создание таблицы.
void CreateTable () {
    char *db_name = "CppProgramTestDB.sl3";
    sqlite3 *db;
    char *zErrMsg = 0;
    int error;
    // Создание или открытие БД.
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if (error) {
        std::cout << "Невозможно открыть базу данных: "
                  << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
    }
    // создаем таблицу пользователей
    char *CreateTableSqlText =  "CREATE TABLE Users "
            "(id integer PRIMARY KEY, login TEXT,"
            "password TEXT);";
    error = sqlite3_exec(db, CreateTableSqlText, NULL, 0, &zErrMsg);
    if (error) {
        std::cout << "Была создана таблица User"
                  << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
    }
    sqlite3_close(db);
}

// Получить всех пользователей.
void GetAllUsers () {
    char *db_name = "CppProgramTestDB.sl3";
    sqlite3 *db;
    // char *zErrMsg = 0;
    int error;
    // Создание или открытие БД.
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if (error) {
        std::cout << "Невозможно открыть базу данных: "
                  << sqlite3_errmsg(db)
                  << std::endl;
        sqlite3_close(db);
    }
    char * CharValue = "select * from Users";
    sqlite3_stmt *res;
    const char *tail;
    error = sqlite3_prepare_v2(db, CharValue , 1000, &res, &tail);
    if (error) {
        std::cout << "Неверная выборка данных: "
                  << sqlite3_errmsg(db)
                  << std::endl;
    }
    std::cout << "Результат запроса к таблице Users" << std::endl;
    int rec_count = 0;
    while (sqlite3_step(res) == SQLITE_ROW) {
        std::cout << "Row (" << rec_count << "):" << sqlite3_column_text(res, 0) << " ";
        std::cout << sqlite3_column_text(res, 1) << " ";
        std::cout << sqlite3_column_text(res, 2) << std::endl;
        rec_count++;
    }
}

// Возвращает пароль пользователя по переданному логину.
// Можно использовать для определения, правильный ли логин и пароль ввел пользователь.
std::string GetUserPassword(std::string _log){
    char *db_name = "CppProgramTestDB.sl3";
    sqlite3 *db;
    // char *zErrMsg = 0;
    int error;
    // Создание или открытие БД.
    error = sqlite3_open(db_name, &db);
    // Обработка возможных ошибок.
    // Если sqlite3_open вернет ошибки, то коннект закрываем.
    if (error) {
        std::cout << "Невозможно открыть базу данных: " << sqlite3_errmsg(db) << std::endl;
    }
    // Скрипт извлечения данных из таблицы.
    std::string SelectValuesSqlText = "SELECT password from Users where login = '" + _log + "'";
    int length = SelectValuesSqlText.length();
    char * CharValue = new char [length];
    strcpy( CharValue, SelectValuesSqlText.c_str() );
    sqlite3_stmt *res;
    const char *tail;
    error = sqlite3_prepare_v2(db, CharValue , 1000, &res, &tail);
    if (error) {
        std::cout << "Неверная выборка данных: " << sqlite3_errmsg(db) << std::endl;
    }
    // Можно задать любое значение для проверки верный ли логин ввел пользователь.
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
