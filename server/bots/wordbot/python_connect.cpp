#include "python_connect.h"

python_connect::python_connect()
{
    Py_Initialize();
    pName = PyUnicode_DecodeFSDefault(SCRIPT_NAME);
    pModule = PyImport_Import(pName);
    if(pModule==NULL){
        PyErr_Print();
        printf("Failed to load\n");
        Py_Finalize();
        exit(1);
    }
    pDict = PyModule_GetDict(pModule);
    pArgs = PyTuple_New(1);
}
python_connect::~python_connect(){
    Py_Finalize();
}
char *python_connect::getRezult(char *dostring){
    char *s = NULL;
    if((s = strstr(dostring, GET_LIKE))!=NULL){
        s +=sizeof(GET_LIKE);
        PyTuple_SetItem(pArgs, 0, PyBytes_FromString(s));
        PyObject *pFunc = PyDict_GetItemString(pDict, GET_LIKE);
        PyObject *pValue = NULL;
        if (PyCallable_Check(pFunc)){
            pValue = PyObject_CallObject(pFunc, pArgs);
        } else {
            return ERROR_STR;
        }
        return  PyBytes_AsString(pValue);
    }else if((s = strstr(dostring, GET_NOT_MACH))!=NULL){
        s +=sizeof(GET_NOT_MACH);
        PyTuple_SetItem(pArgs, 0, PyBytes_FromString(s));
        PyObject *pFunc = PyDict_GetItemString(pDict, GET_NOT_MACH);
        PyObject *pValue = NULL;
        if (PyCallable_Check(pFunc)){
            pValue = PyObject_CallObject(pFunc, pArgs);
        } else {
            return ERROR_STR;
        }
        return  PyBytes_AsString(pValue);
    }else if((s = strstr(dostring, GET_RAZ))!=NULL){
        s +=sizeof(GET_RAZ);
        PyTuple_SetItem(pArgs, 0, PyBytes_FromString(s));
        PyObject *pFunc = PyDict_GetItemString(pDict, GET_RAZ);
        PyObject *pValue = NULL;
        if (PyCallable_Check(pFunc)){
            pValue = PyObject_CallObject(pFunc, pArgs);
        } else {
            return ERROR_STR;
        }
        return  PyBytes_AsString(pValue);
    }else if((s = strstr(dostring, GET_SUMM))!=NULL){
        s +=sizeof(GET_SUMM);
        PyTuple_SetItem(pArgs, 0, PyBytes_FromString(s));
        PyObject *pFunc = PyDict_GetItemString(pDict, GET_SUMM);
        PyObject *pValue = NULL;
        if (PyCallable_Check(pFunc)){
            pValue = PyObject_CallObject(pFunc, pArgs);
        } else {
            return ERROR_STR;
        }
        return  PyBytes_AsString(pValue);
    }
    return ERROR_STR;
}

