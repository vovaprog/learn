#include <iostream>

#include <Python.h>

#include <boost/python.hpp>

using namespace std;

using namespace boost::python;


bool runPython(const string &expression,double &result) 
{
    Py_Initialize();
    
    if(PyRun_SimpleString((string("result = ")+expression).c_str())!=0)
    {
      Py_Finalize();
      return false;      
    }
    
    PyObject * module = PyImport_AddModule("__main__"); // borrowed reference
    
    assert(module);                                     // __main__ should always exist
    PyObject * dictionary = PyModule_GetDict(module);   // borrowed reference
    assert(dictionary);                                 // __main__ should have a dictionary
    PyObject * pyresult
    = PyDict_GetItemString(dictionary, "result");     // borrowed reference
    
    assert(pyresult);                                     // just added result
    
    result = PyFloat_AsDouble(pyresult);
    std::cout << result << std::endl;
    
    Py_Finalize();
    return true;
}

bool runPythonBoost(const string &expression,double &result) 
{
    Py_Initialize();
    
    try {
        if(PyRun_SimpleString((string("result = ")+expression).c_str())!=0)
        {
          Py_Finalize();
          return false;      
        }    
        
        object module(handle<>(borrowed(PyImport_AddModule("__main__"))));
        object dictionary = module.attr("__dict__");
        object pyResult = dictionary["result"];
        result = extract<double>(pyResult);
        
    } catch (error_already_set) {
        PyErr_Print();
    }
    
    Py_Finalize();
    
    return true;
}

bool runPythonBoost2(const string &expression,double &result) 
{
    Py_Initialize();

    try {
        
        object main_module = import("__main__");
        object main_namespace = main_module.attr("__dict__");    
        
        object pyResult = eval(expression.c_str(), main_namespace);
        result = extract<double>(pyResult);
        
    } catch (error_already_set) {
        PyErr_Print();
        Py_Finalize();
        return false;
    }
    
    Py_Finalize();
    
    return true;
}

