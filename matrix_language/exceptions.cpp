//#include "exceptions.h"
#include "lexeme_analyzer.h"

#include <iostream>
#include <typeinfo>

const char *exception_str_lang[25] =
{
	"EX_UNKNOWN",
	"EX_BAD_LEXEME",
	"EX_ERR_OUT_OF_RANGE",
	"EX_ERR0",
	"EX_ERR1",
	"EX_ERR2",
	"EX_ERR3",
	"EX_ERR4",
	"EX_ERR5",
	"EX_ERR6",
	"EX_ERR7",
	"EX_ERR8",
	"EX_ERR9",
	"EX_ERR10",
	"EX_ERR11",
	"EX_ERR12",
	"EX_ERR13",
	"EX_ERR14",
	"EX_ERR15",
	"EX_ERR16",
	"EX_ERR17",
	"EX_ERR18",
	"EX_ERR19",
	"EX_ERR20",
	"EX_ERR21"
};


ExceptionsLanguage :: ExceptionsLanguage(int error, ExceptionsLanguage *p, int obj) 
	: error_type(error), ptr(p), object_type(obj) { }

ExceptionsLanguage :: ~ExceptionsLanguage() { }

void ExceptionsLanguage :: printException() const {
	//Exceptions *tmp_ex = const_cast<Exceptions*>(this->getPtr());
	Lexeme *tmp;
	tmp = dynamic_cast<Lexeme*>(this->getPtr());
	if (error_type == EX_BAD_LEXEME) {
		std :: cout << "BAD_LEXEME";
	}
	if (error_type == EX_ERR_OUT_OF_RANGE) {
		std :: cout << "OUT_OF_RANGE";
	}
	if (error_type == EX_UNKNOWN) {
		std :: cout << "UNKNOWN";
	}
	std :: cout << exception_str_lang[error_type];
	std :: cout << "[" << tmp->getLexemeRow() 
	<< ":" << tmp->getLexemeCol() << "]: "
	<< tmp->getLexemeString() << "\n";
	//delete tmp;
} 

