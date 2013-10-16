// input and output binary numbers
// h2kyeong, 2013. 8. 13

#define PY_SSIZE_T_CLEAN  // must preceed Python.h
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
	Py_ssize_t len;
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



PyDEF bin_long (PyARGS){
	int ok;
	long val;
	ok = PyArg_ParseTuple(args, "l", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(long));
}

PyDEF bin_int (PyARGS){
	int ok;
	int val;
	ok = PyArg_ParseTuple(args, "i", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(int));
}

PyDEF bin_short (PyARGS){
	int ok;
	short val;
	ok = PyArg_ParseTuple(args, "h", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(short));
}

PyDEF bin_ulong (PyARGS){
	int ok;
	unsigned long val;
	ok = PyArg_ParseTuple(args, "k", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(unsigned long));
}

PyDEF bin_uint (PyARGS){
	int ok;
	unsigned int val;
	ok = PyArg_ParseTuple(args, "I", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(unsigned int));
}

PyDEF bin_ushort (PyARGS){
	int ok;
	unsigned short val;
	ok = PyArg_ParseTuple(args, "H", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(unsigned short));
}

PyDEF bin_float (PyARGS){
	int ok;
	float val;
	ok = PyArg_ParseTuple(args, "f", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(float));
}

PyDEF bin_double (PyARGS){
	int ok;
	double val;
	ok = PyArg_ParseTuple(args, "d", &val);
	if (!ok) return 0;
	return Py_BuildValue("s#", &val, sizeof(double));
}

char const CHARSET[] = "0123456789abcdef";

PyDEF bin2hex (PyARGS){
	int ok;
	const unsigned char* val;
	Py_ssize_t len;
	ok = PyArg_ParseTuple(args, "s#", &val, &len);
	if (!ok) return 0;
	
	char* out = (char*) calloc(sizeof(char), len*2);
	if (!out){
		PyErr_SetString(PyExc_MemoryError, "failed to allocate memory for output");
		return 0;
	}
	// WARNING FREE MEMORY BEFORE RETURN
	
	const unsigned char* ival = val;
	unsigned char* iout = out;
	for (Py_ssize_t i=0; i<len; ++i){
		int c = *ival;
		*iout = CHARSET[c >> 4]; ++iout;
		*iout = CHARSET[c & 15]; ++iout;
		++ival;
	}
	
	PyObject* ret = Py_BuildValue("s#", out, sizeof(char) * len*2);
	free(out);
	return ret;
}

// returns 0 to 15
static int __hex2bin_char (char c){
	if ('0' <= c && c <= '9') return (c - '0');
	if ('a' <= c && c <= 'f') return (c - 'a' + 10);
	if ('A' <= c && c <= 'F') return (c - 'A' + 10);
	return -1;
}

PyDEF hex2bin (PyARGS){
	int ok;
	const char* val;
	Py_ssize_t len;
	ok = PyArg_ParseTuple(args, "s#", &val, &len);
	if (!ok) return 0;
	if (len & 1){
		PyErr_SetString(PyExc_Exception, "length is not even");
		return 0;
	}
	
	unsigned char* out = (unsigned char*) calloc(sizeof(char), len/2);
	if (!out){
		PyErr_SetString(PyExc_MemoryError, "failed to allocate memory for output");
		return 0;
	}
	// WARNING FREE MEMORY BEFORE RETURN
	
	unsigned char* iout = out;
	for (Py_ssize_t i=0; i<len; i+=2){
		int v;
		const char* c = val + i;
		ok = __hex2bin_char(c[1]);
		if (ok < 0){
			PyErr_SetString(PyExc_Exception, "illegal character");
			free(out);
			return 0;
		}
		v = ok;
		ok = __hex2bin_char(c[0]);
		if (ok < 0){
			PyErr_SetString(PyExc_Exception, "illegal character");
			free(out);
			return 0;
		}
		v += ok << 4;
		*iout = v;
		++iout;
	}
	
	PyObject* ret = Py_BuildValue("s#", out, sizeof(char) * len/2);
	free(out);
	return ret;
}

static PyMethodDef methods[] = {
	{"open", fopen_, METH_VARARGS, "addr = open(name, mode='w+')\n" "open a file for writing"},
	{"close", fclose_, METH_VARARGS, "close(addr)\n" "close the file"},
	{"write", fwrite_, METH_VARARGS, "write(str, addr=stdout)\n" "write a string"},
	{"seek", fseek_, METH_VARARGS, "seek(addr, pos, mode=SEEK_SET)\n" "go to byte offset of current file"},
	{"tell", ftell_, METH_VARARGS, "tell(addr)\n" "get the byte offset of current file"},
	{"write_f8", write_double, METH_VARARGS, "write(float, addr=stdout)\n" "write a signed double in binary"},
	{"write_f4", write_float, METH_VARARGS, "write(float, addr=stdout)\n" "write a signed float in binary"},
	{"write_i8", write_long, METH_VARARGS, "write(int, addr=stdout)\n" "write a signed long in binary"},
	{"write_i4", write_int, METH_VARARGS, "write(int, addr=stdout)\n" "write a signed int in binary"},
	{"write_i2", write_short, METH_VARARGS, "write(int, addr=stdout)\n" "write a signed short in binary"},
	{"write_u8", write_ulong, METH_VARARGS, "write(int, addr=stdout)\n" "write an unsigned long in binary"},
	{"write_u4", write_uint, METH_VARARGS, "write(int, addr=stdout)\n" "write an unsigned int in binary"},
	{"write_u2", write_ushort, METH_VARARGS, "write(int, addr=stdout)\n" "write an unsigned short in binary"},
	{"bin_i8", bin_long, METH_VARARGS, "binary representation of a signed long"},
	{"bin_i4", bin_int, METH_VARARGS, "binary representation of a signed integer"},
	{"bin_i2", bin_short, METH_VARARGS, "binary representation of a signed short"},
	{"bin_u8", bin_ulong, METH_VARARGS, "binary representation of an unsigned long"},
	{"bin_u4", bin_uint, METH_VARARGS, "binary representation of an unsigned integer"},
	{"bin_u2", bin_ushort, METH_VARARGS, "binary representation of an unsigned short"},
	{"bin_f8", bin_double, METH_VARARGS, "binary representation of a double"},
	{"bin_f4", bin_float, METH_VARARGS, "binary representation of a float"},
	{"hex2bin", hex2bin, METH_VARARGS, "hex dump into a binary string"},
	{"bin2hex", bin2hex, METH_VARARGS, "convert a hex dump to a binary string"},
	{0,0,0,0}
};

PyMODINIT_FUNC initraw (void){
	PyObject* module = Py_InitModule("raw", methods);
	PyObject* x;
	x = PyInt_FromLong(SEEK_SET); PyObject_SetAttrString(module, "SEEK_SET", x); Py_DECREF(x);
	x = PyInt_FromLong(SEEK_CUR); PyObject_SetAttrString(module, "SEEK_CUR", x); Py_DECREF(x);
	x = PyInt_FromLong(SEEK_END); PyObject_SetAttrString(module, "SEEK_END", x); Py_DECREF(x);
}
