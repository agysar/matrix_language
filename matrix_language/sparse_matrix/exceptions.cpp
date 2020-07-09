#include "exceptions.h"


const char *exception_str[14] =
{
	"EX_UNKNOWN",
	"EX_OVERFLOW",
	"EX_BAD_ALLOC",
	"EX_DIVIDE_BY_ZERO",
	"EX_OUT_OF_RANGE",
	"EX_SIZE_OF_VECTORS_ARE_DIFFERENT",
	"EX_WRONG_FILE_NAME",
	"EX_CANNOT_OPEN_FILE",
	"EX_FILE_HAVE_NO_VECTOR",
	"EX_END_OF_FILE",
	"EX_FILE_HAVE_NO_MATRIX",
	"EX_SIZE_OF_MATRIX_ARE_DIFFERENT",
	"EX_PTR_IS_NULL",
	"EX_ITERATOR_SIZE_IS_NOT_EQUAL"
};


Exceptions :: Exceptions(int error, const Exceptions* p, int obj) 
	: error_type(error), ptr(p), object_type(obj) { }

Exceptions :: ~Exceptions() { }

int Exceptions :: get_error() const{
	return error_type;
}

const char *Exceptions :: get_error_str() const {
	return exception_str[error_type];
}

const Exceptions * Exceptions :: get_ptr() const { return ptr; }

int Exceptions :: get_object_type() const { return object_type; }