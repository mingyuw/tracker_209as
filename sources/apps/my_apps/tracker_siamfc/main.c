#include <Python.h>
#include "caller_tracker.h"

int main() {
  PyImport_AppendInittab("call_tracker", PyInit_caller_tracker);
  Py_Initialize();
  PyImport_ImportModule("call_tracker");
  call_tracker();
  Py_Finalize();
  return 0;
}