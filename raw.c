// input and output binary numbers
// h2kyeong, 2013. 8. 13

#include <Python.h>
#define PyDEF  static PyObject*
#define PyARGS  PyObject *self, PyObject *args

PyDEF fopen_ (PyARGS){
	int ok;
	const char* v1=0, *v2=0;
	ok = PyArg_ParseTuple(args, "s|s", &v1, &v2);
	if (!ok) return 0;
	if (!v2) v2 = "w+";
	FILE* fout = fopen(v1, v2);
	if (!fout){
		PyErr_SetString(PyExc_IOError, "failed to open file for writing");
		fout = stdout;
		return 0;
	}
	return PyInt_FromLong((long) fout);
}

PyDEF fclose_ (PyARGS){
	int ok;
	FILE* fout = 0;
	ok = PyArg_ParseTuple(args, "k", &fout);
	if (!ok) return 0;
	ok = fclose(fout);
	if (ok){
		PyErr_SetString(PyExc_IOError, "failed to close");
		return 0;
	}
	Py_RETURN_NONE;
}

PyDEF fseek_ (PyARGS){
	int ok;
	long p;
	int m = 0;
	FILE* fout = 0;
	ok = PyArg_ParseTuple(args, "ll|i", &fout, &p, &m);
	if (!ok) return 0;
	if (m < 0 || m > 2){
		PyErr_SetString(PyExc_IOError, "give 0,1,2 for SEEK_SET, SEEK_CUR, SEEK_END, respectively");
		return 0;
	}
	int const modes[] = {SEEK_SET, SEEK_CUR, SEEK_END};
	m = modes[m];
	ok = fseek(fout, p, m);
	if (ok<0){
		PyErr_SetString(PyExc_IOError, "failed to fseek");
		return 0;
	}
	Py_RETURN_NONE;
}

PyDEF ftell_ (PyARGS){
	int ok;
	FILE* fout = 0;
	ok = PyArg_ParseTuple(args, "l", &fout);
	if (!ok) return 0;
	long p = ftell(fout);
	if (p<0){
		PyErr_SetString(PyExc_IOError, "failed to ftell");
		return 0;
	}
	return PyInt_FromLong(p);
}

PyDEF fwrite_ (PyARGS){
	int ok;
	const char* val;
	unsigned int len;
	FILE* fout = stdout;
	ok = PyArg_ParseTuple(args, "s#|l", &val, &len, &fout);
	if (!ok) return 0;
	fwrite(val, sizeof(char), len, fout);
	Py_RETURN_NONE;
}

PyDEF write_long (PyARGS){
	int ok;
	long val;
	FILE* fout = stdout;
	ok = PyArg_ParseTuple(args, "l|l", &val, &fout);
	if (!ok) return 0;
	fwrite(&val, sizeof(long), 1, fout);
	Py_RETURN_NONE;
}

PyDEF write_int (PyARGS){
	int ok;
	int val;
	FILE* fout = stdout;
	ok = PyArg_ParseTuple(args, "i|l", &val, &fout);
	if (!ok) return 0;
	fwrite(&val, sizeof(int), 1, fout);
	Py_RETURN_NONE;
}

PyDEF write_short (PyARGS){
	int ok;
	short val;
	FILE* fout = stdout;
	ok = PyArg_ParseTuple(args, "h|l", &val, &fout);
	if (!ok) return 0;
	fwrite(&val, sizeof(short), 1, fout);
	Py_RETURN_NONE;
}

PyDEF write_ulong (PyARGS){
	int ok;
	unsigned long val;
	FILE* fout = stdout;
	ok = PyArg_ParseTuple(args, "k|l", &val, &fout);
	if (!ok) return 0;
	fwrite(&val, sizeof(unsigned long), 1, fout);
	Py_RETURN_NONE;
}

PyDEF write_uint (PyARGS){
	int ok;
	unsigned int val;
	FILE* fout = stdout;
	ok = PyArg_ParseTuple(args, "I|l", &val, &fout);
	if (!ok) return 0;
	fwrite(&val, sizeof(unsigned int), 1, fout);
	Py_RETURN_NONE;
}

PyDEF write_ushort (PyARGS){
	int ok;
	unsigned short val;
	FILE* fout = stdout;
	ok = PyArg_ParseTuple(args, "H|l", &val, &fout);
	if (!ok) return 0;
	fwrite(&val, sizeof(unsigned short), 1, fout);
	Py_RETURN_NONE;
}

PyDEF write_float (PyARGS){
	int ok;
	float val;
	FILE* fout = stdout;
	ok = PyArg_ParseTuple(args, "f|l", &val, &fout);
	if (!ok) return 0;
	fwrite(&val, sizeof(float), 1, fout);
	Py_RETURN_NONE;
}

PyDEF write_double (PyARGS){
	int ok;
	double val;
	FILE* fout = stdout;
	ok = PyArg_ParseTuple(args, "d|l", &val, &fout);
	if (!ok) return 0;
	fwrite(&val, sizeof(double), 1, fout);
	Py_RETURN_NONE;
}



PyDEF str_long (PyARGS){
	int ok;
	long val;
	ok = PyArg_ParseTuple(args, "l", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(long));
}

PyDEF str_int (PyARGS){
	int ok;
	int val;
	ok = PyArg_ParseTuple(args, "i", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(int));
}

PyDEF str_short (PyARGS){
	int ok;
	short val;
	ok = PyArg_ParseTuple(args, "h", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(short));
}

PyDEF str_ulong (PyARGS){
	int ok;
	unsigned long val;
	ok = PyArg_ParseTuple(args, "k", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(unsigned long));
}

PyDEF str_uint (PyARGS){
	int ok;
	unsigned int val;
	ok = PyArg_ParseTuple(args, "I", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(unsigned int));
}

PyDEF str_ushort (PyARGS){
	int ok;
	unsigned short val;
	ok = PyArg_ParseTuple(args, "H", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(unsigned short));
}

PyDEF str_float (PyARGS){
	int ok;
	float val;
	ok = PyArg_ParseTuple(args, "f", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(float));
}

PyDEF str_double (PyARGS){
	int ok;
	double val;
	ok = PyArg_ParseTuple(args, "d", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(double));
}

static PyMethodDef methods[] = {
	{"open", fopen_, METH_VARARGS, "addr = open(name, mode='w+')\n" "open a file for writing"},
	{"close", fclose_, METH_VARARGS, "close(addr)\n" "close the file"},
	{"write", fwrite_, METH_VARARGS, "write(str, addr=stdout)\n" "write a string"},
	{"seek", fseek_, METH_VARARGS, "seek(addr, pos, mode=SEEK_SET)\n" "go to byte offset of current file"},
	{"tell", ftell_, METH_VARARGS, "tell(addr)\n" "get the byte offset of current file"},
	{"write_i8", write_long, METH_VARARGS, "write(val, addr=stdout)\n" "write a signed long in binary"},
	{"write_i4", write_int, METH_VARARGS, "write(val, addr=stdout)\n" "write a signed int in binary"},
	{"write_i2", write_short, METH_VARARGS, "write(val, addr=stdout)\n" "write a signed short in binary"},
	{"write_u8", write_ulong, METH_VARARGS, "write(val, addr=stdout)\n" "write an unsigned long in binary"},
	{"write_u4", write_uint, METH_VARARGS, "write(val, addr=stdout)\n" "write an unsigned int in binary"},
	{"write_u2", write_ushort, METH_VARARGS, "write(val, addr=stdout)\n" "write an unsigned short in binary"},
	{"write_f8", write_double, METH_VARARGS, "write(val, addr=stdout)\n" "write a signed double in binary"},
	{"write_f4", write_float, METH_VARARGS, "write(val, addr=stdout)\n" "write a signed float in binary"},
	{"str_i8", str_long, METH_VARARGS, "binary representation of a signed long"},
	{"str_i4", str_int, METH_VARARGS, "binary representation of a signed integer"},
	{"str_i2", str_short, METH_VARARGS, "binary representation of a signed short"},
	{"str_u8", str_ulong, METH_VARARGS, "binary representation of an unsigned long"},
	{"str_u4", str_uint, METH_VARARGS, "binary representation of an unsigned integer"},
	{"str_u2", str_ushort, METH_VARARGS, "binary representation of an unsigned short"},
	{"str_f8", str_double, METH_VARARGS, "binary representation of a double"},
	{"str_f4", str_float, METH_VARARGS, "binary representation of a float"},
	{0,0,0,0}
};

PyMODINIT_FUNC initraw (void){
	PyObject* module = Py_InitModule("raw", methods);
	PyObject* x;
	x = PyInt_FromLong(SEEK_SET); PyObject_SetAttrString(module, "SEEK_SET", x); Py_DECREF(x);
	x = PyInt_FromLong(SEEK_CUR); PyObject_SetAttrString(module, "SEEK_CUR", x); Py_DECREF(x);
	x = PyInt_FromLong(SEEK_END); PyObject_SetAttrString(module, "SEEK_END", x); Py_DECREF(x);
}
