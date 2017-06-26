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
}
python_connect::~python_connect(){
    Py_Finalize();
}
char *python_connect::getRezult(const char *dostring){
    char *s = NULL;
    if((s = strstr(dostring, GET_LIKE))!=NULL){
        PyTuple_SetItem(pArgs, 0, PyBytes_FromString(GET_LIKE));
        s +=sizeof(GET_LIKE);
        PyObject *pFunc = PyDict_GetItemString(pDict, s);
        PyObject *pValue = NULL;
        if (PyCallable_Check(pFunc)){
            pValue = PyObject_CallObject(pFunc, pArgs);
        } else {
            return ERROR_STR;
        }
        return  PyBytes_AsString(pValue);
    }else if((s = strstr(dostring, GET_NOT_MACH))!=NULL){
        PyTuple_SetItem(pArgs, 0, PyBytes_FromString(GET_NOT_MACH));
        s +=sizeof(GET_NOT_MACH);
        PyObject *pFunc = PyDict_GetItemString(pDict, s);
        PyObject *pValue = NULL;
        if (PyCallable_Check(pFunc)){
            pValue = PyObject_CallObject(pFunc, pArgs);
        } else {
            return ERROR_STR;
        }
        return  PyBytes_AsString(pValue);
    }else if((s = strstr(dostring, GET_RAZ))!=NULL){
        PyTuple_SetItem(pArgs, 0, PyBytes_FromString(GET_RAZ));
        s +=sizeof(GET_RAZ);
        PyObject *pFunc = PyDict_GetItemString(pDict, s);
        PyObject *pValue = NULL;
        if (PyCallable_Check(pFunc)){
            pValue = PyObject_CallObject(pFunc, pArgs);
        } else {
            return ERROR_STR;
        }
        return  PyBytes_AsString(pValue);
    }else if((s = strstr(dostring, GET_SUMM))!=NULL){
        PyTuple_SetItem(pArgs, 0, PyBytes_FromString(GET_SUMM));
        s +=sizeof(GET_SUMM);
        PyObject *pFunc = PyDict_GetItemString(pDict, s);
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

