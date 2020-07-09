#pragma once

#define LEXEME 106

#define EX_UNKNOWN 0
#define EX_BAD_LEXEME 1
#define EX_ERR_OUT_OF_RANGE 2
#define EX_ERR0 3
#define EX_ERR1 4
#define EX_ERR2 5
#define EX_ERR3 6
#define EX_ERR4 7
#define EX_ERR5 8
#define EX_ERR6 9
#define EX_ERR7 10
#define EX_ERR8 11
#define EX_ERR9 12
#define EX_ERR10 13
#define EX_ERR11 14
#define EX_ERR12 15
#define EX_ERR13 16
#define EX_ERR14 17
#define EX_ERR15 18
#define EX_ERR16 19
#define EX_ERR17 20
#define EX_ERR18 21
#define EX_ERR19 22
#define EX_ERR20 23
#define EX_ERR21 24



class ExceptionsLanguage {
public:
	int error_type;
	ExceptionsLanguage *ptr;
	int object_type;

//	public:
		ExceptionsLanguage(int = 0, ExceptionsLanguage * = nullptr, int = 0);
		virtual ~ExceptionsLanguage();

		ExceptionsLanguage *getPtr() const { return ptr; }
		void printException() const;
};