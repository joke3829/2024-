#include <string>
#include<fstream>
#include "python.h" 

static PyObject *

spam_createFile(PyObject *self, PyObject *args)
{
	PyObject* listObj;

	if (!PyArg_ParseTuple(args, "O", &listObj))
		return NULL;

	if (!PyList_Check(listObj)) {
		PyErr_SetString(PyExc_TypeError, "Parameter must be a list");
		return NULL;
	}

	int listSize = PyList_Size(listObj);
	std::ofstream out{ "ĳ���� ����.txt" };
	for (int i = 0; i < listSize; ++i) {
		PyObject* item = PyList_GetItem(listObj, i);
		if (!PyUnicode_Check(item)) {
			PyErr_SetString(PyExc_TypeError, "List must contain only strings");
			return NULL;
		}
		const char* str = PyUnicode_AsUTF8(item);
		out << str << std::endl;
	}

	return Py_BuildValue("i", 0);
}

static PyMethodDef SpamMethods[] = {
	{ "createFile", spam_createFile, METH_VARARGS,
	"createFile for character" },
	{ NULL, NULL, 0, NULL } // �迭�� ���� ��Ÿ���ϴ�.
};

static struct PyModuleDef spammodule = {
	PyModuleDef_HEAD_INIT,
	"spam",            // ��� �̸�
	"It is test module.", // ��� ������ ���� �κ�, ����� __doc__�� ����˴ϴ�.
	-1,SpamMethods
};

PyMODINIT_FUNC
PyInit_spam(void)
{
	return PyModule_Create(&spammodule);
}
