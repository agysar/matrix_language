#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

#include "exceptions.h"
//#include "lexeme_declaration.h"


enum statesLex {S, A, B, C, D, END};
/*
	S - start
	A - digits before dot
	B - digits after dot
	C - digits, letter and _ (variable)
	D - digits, letter and _ (variable)
	END - end of the lexeme
*/

class Lexeme : public ExceptionsLanguage {
	size_t type; // type of lexeme
	std :: string lex; // string
	size_t row; // row 
	size_t col; // col
	size_t op; // is it operation or not?
	size_t function; // is it function or not?

public:
	static size_t current_row;
	static size_t current_col;

	std :: string getLexemeType() const;

	size_t getLexemeRow() const { return row; }

	size_t getLexemeCol() const { return col; }

	std :: string &getLexemeString() { return lex; }

	bool isop() const { return (op) ? true : false; }

	bool isfunc() const { return (function) ? true : false; }

	void setLexemeType(size_t typee) { type = typee; }

	void setLexemeRow(size_t rowee) { row = rowee; }

	void setLexemeCol(size_t colee) { col = colee; }

	void setLexemeOp(size_t opee) { op = opee; }

	void setLexemeFunc(size_t opee) { function = opee; }

};

char gc(std :: ifstream&); // get char from ifstream file 

bool isDelimeter(char);

bool isSign(char); // operations and some special symbols 

Lexeme getLexeme(std :: ifstream&); // get lexeme from ifstream file

