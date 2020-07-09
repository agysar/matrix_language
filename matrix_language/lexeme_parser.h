//#include "lexeme_analyzer.h"
#include "./sparse_matrix/rational_number.h"
#include "./sparse_matrix/rational_map.h"
#include "./sparse_matrix/rational_vector.h"
#include "./sparse_matrix/rational_matrix.h"
#include "./sparse_matrix/random_access_iterator.h"
#include "lexeme_analyzer.h"
#include "lexeme_declaration.h"


#include <vector>
#include <stack>
#include <string>


void S_Process(std :: vector<Lexeme> &a);
void A_Process(std :: vector<Lexeme> &a);
void B_Process(std :: vector<Lexeme> &a);
void F_Process(std :: vector<Lexeme> &a);
void F1_Process(std :: vector<Lexeme> &a);
void F2_Process(std :: vector<Lexeme> &a);
void D_Process(std :: vector<Lexeme> &a);
void H_Process(std :: vector<Lexeme> &a);
void M_Process(std :: vector<Lexeme> &a);
void N_Process(std :: vector<Lexeme> &a);
void Q_Process(std :: vector<Lexeme> &a);

class PolizElem { // the base class for all of the POLIZ items
public:
	virtual ~PolizElem() { }

	//virtual void evaluate(std :: stack<PolizElem> *stack,
	//	PolizElem *cur_cmd) const = 0;

protected:
	//static void push(std :: stack<PolizElem> *stack, PolizElem *elem);
	//static PolizElem* pop(std :: stack<PolizElem> *stack);
};

/*class PolizItem { // element of the POLIZ list
	PolizElem *ptr;
	PolizItem *next;
};*/

//std :: vector<PolizElem*> poliz_vec; 
//std :: stack<std :: string> sup_stack;

//[CONSTANTS]
class PolizConst : public PolizElem {
public:
	bool flg_int = false;
	bool flg_float = false;
	float value_float;
	int value_int;
};


// [VARIABLES]
class PolizVar : public PolizElem {
public: 
	//virtual PolizElem *clone() const = 0;
	virtual ~PolizVar() { };

	virtual std :: string getLabel() const = 0;
};

class PolizRational : public PolizVar {
	RationalNumber value;
public:
	std :: string label;

	PolizRational(RationalNumber a, std :: string labelee) { value = a; label = labelee; }
	virtual ~PolizRational() { }
	//virtual PolizElem *clone() const;
	RationalNumber get() const { return value; }
	std :: string getLabel() const { return label; }
};

class PolizInt : public PolizVar {
	int value;
public:
	std :: string label;

	PolizInt(int a, std :: string labelee) { value = a; label = labelee; }
	virtual ~PolizInt() { }
	//virtual PolizElem* clone() const;
	int get() const { return value; };
	std :: string getLabel() const { return label; }
};

class PolizFloat : public PolizVar {
	float value;
public:
	std :: string label;

	PolizFloat(float a, std :: string labelee) { value = a; label = labelee; }
	virtual ~PolizFloat() {}
	//virtual PolizElem* clone() const;
	float get() const { return value; };
	std :: string getLabel() const { return label; }
};

class PolizVector : public PolizVar {
	RationalVector value;
public:	
	std :: string label;

	PolizVector(RationalVector a, std :: string labelee) { value = a; label = labelee; }
	virtual ~PolizVector() {}
	//virtual PolizElem* clone() const;
	RationalVector get() const { return value; }
	std :: string getLabel() const { return label; }
};

class PolizMatrix : public PolizVar {
	RationalMatrix value;
public:
	std :: string label;

	PolizMatrix(RationalMatrix a, std :: string labelee) { value = a; label = labelee; }
	virtual ~PolizMatrix() {}
	//virtual PolizElem* clone() const;
	RationalMatrix get() const { return value; }
	std :: string getLabel() const { return label; }
};

// [OPERATIONS]
// main class for all of operations with expressions
class PolizFunction : public PolizElem {
public:
	virtual ~PolizFunction() { }
	//virtual PolizElem *evaluateFun() const = 0;
	virtual int getFunType() const { return 0; }
	//virtual void setFunType(int) { }
};

class PolizFunSemicolon : public PolizFunction {
	int type;
public:
	PolizFunSemicolon() : type(SEMICOLON) { }
	~PolizFunSemicolon() { }
	int getFunType() const { return type; }
	//void setFunType(int a ) { type = a; }
};

class PolizFunOpenBracket : public PolizFunction {
	int type;
public:
	PolizFunOpenBracket() : type(OPEN_BRACKET) { }
	~PolizFunOpenBracket() { }
	int getFunType() const { return type; }
	//void setFunType(int a ) { type = a; }
};

class PolizFunCloseBracket : public PolizFunction {
	int type;
public:
	PolizFunCloseBracket() : type(CLOSE_BRACKET) { }
	~PolizFunCloseBracket() { }
	int getFunType() const { return type; }
	//void setFunType(int a ) { type = a; }
};

/*class PolizFunPlus : public PolizFunction {

};

class PolizFunMinus : public PolizFunction {

};

class PolizFunMultiplication : public PolizFunction {

};

class PolizFunDivision : public PolizFunction {

};

class PolizFunRead : public PolizFunction { // read from "filename"

};

class PolizFunWrite : public PolizFunction { // write to "filename"

};

class PolizFunPrint : public PolizFunction { // print to stdout

};

class PolizFunInfo : public PolizFunction { // print every string in quotes

};

class PolizFunRow : public PolizFunction { // get row for matrix

};

class PolizFunColumn : public PolizFunction { // get column for matrix

};

// have highest priority in operations
class PolizFunMakeCanonical : public PolizFunction { 

};*/


Lexeme *glfa(std :: vector<Lexeme> &a);

void syntaxAnalyzer(std :: vector<Lexeme> &a);