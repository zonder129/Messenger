#ifndef PYTHON_CONNECT_H
#define PYTHON_CONNECT_H

#include <cmath>
#include <Python.h>
#include <cstring>

#define SCRIPT_NAME "w2v"

#define GET_LIKE "get_like"
#define GET_SUMM "get_summ"
#define GET_RAZ "get_raz"
#define GET_NOT_MACH "get_not_mach"
#define ERROR_STR "Comand error"

class python_connect
{
public:
    python_connect();
    ~python_connect();
    char *getRezult(const char*);

private:
    PyObject *pModule, *pName, *pDict, *pArgs;

};

#endif // PYTHON_CONNECT_H
