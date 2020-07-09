#pragma once

#define NUMBER 100
#define MAP 101
#define VECTOR 102
#define MATRIX 103
#define ITERATOR 104


#define EX_UNKNOWN 0
#define EX_OVERFLOW 1
#define EX_BAD_ALLOC 2
#define EX_DIVIDE_BY_ZERO 3
#define EX_OUT_OF_RANGE 4
#define EX_SIZE_OF_VECTORS_ARE_DIFFERENT 5
#define EX_WRONG_FILE_NAME 6
#define EX_CANNOT_OPEN_FILE 7
#define EX_FILE_HAVE_NO_VECTOR 8
#define EX_END_OF_FILE 9
#define EX_FILE_HAVE_NO_MATRIX 10
#define EX_SIZE_OF_MATRIX_ARE_DIFFERENT 11
#define EX_PTR_IS_NULL 12
#define EX_ITERATOR_SIZE_IS_NOT_EQUAL 13



class Exceptions {
	int error_type;
	const Exceptions *ptr;
	int object_type;

	public:
		Exceptions(int, const Exceptions *, int);
		int get_error() const;
		const Exceptions *get_ptr() const;
		const char *get_error_str() const;
		int get_object_type() const;
		~Exceptions();
};