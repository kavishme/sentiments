%module sentiment

%typemap(in) (int argc, char **argv) {
	/* Check if is a list */
	if (PyList_Check($input)) {
	    int i;
	    $1 = PyList_Size($input);
	    $2 = (char **) malloc(($1+1)*sizeof(char *));
	    for (i = 0; i < $1; i++) {
		    PyObject *o = PyList_GetItem($input,i);
		    if (PyString_Check(o))
				$2[i] = PyString_AsString(PyList_GetItem($input,i));
		    else {
				PyErr_SetString(PyExc_TypeError,"list must contain strings");
				free($2);
				return NULL;
		    }
	    }
	    $2[i] = 0;
  	} else {
	    PyErr_SetString(PyExc_TypeError,"not a list");
	    return NULL;
  }
}

%typemap(freearg) (int argc, char **argv) {
 	free((char *) $2);
}


%{
#include "sentiment.h"
%}

%include "std_string.i"

%include "std_vector.i"
namespace std {
%template(vectorStr) vector<string>;
%template(vectorTsv) vector<vector<string> >;
}

%include "std_map.i"
namespace std {
%template(sentiMap) map<string, float>;
}

%include "sentiment.h"