// Declaration of Lexeme types
#pragma once

#define UNKNOWN 100500
#define END_OF_FILE 100501
#define SIGN 890
#define ID 891
#define NUMBER_TYPE 892
#define COMMENT 893
#define DELIMETER 894
#define QUOTE_STRING 895 // maybe name of the file 
#define PLUS 896
#define MINUS 897
#define OPEN_BRACKET 898
#define CLOSE_BRACKET 899
#define DEFAULT_WORD 900
#define DIVISION 901
#define MULTIPLICATION 902
#define SEMICOLON 903
#define DECLARE 904
#define PROCESS 905
#define MATRIX_TYPE 906
#define FLOAT_KAPPA 907 // состояние автомата
#define INTEGER 908
#define VECTOR_TYPE 909
#define RATIONAL 910
#define READ 911
#define WRITE 912
#define PRINT 913
#define INFO 914
#define ROTATE 915
#define ROW 916
#define COLUMN 917
#define MAKE_CANONICAL 918
#define COLON 919
#define BACKSLASH 920
#define COMMA 921
#define FLOAT_NUMBER 922 // тип числа
#define SLASH 923
#define SQ_OPEN_BRACKET 924
#define SQ_CLOSE_BRACKET 925
#define POWER 926

#include <set>
#include <string>

//using namespace std;

extern std :: set<std :: string> SetOfWords;
/*	"declare",
	"integer",
	"float",
	"vector",
	"matrix",
	"rational",
	"read",
	"write",
	"print",
	"info",
	"rotate",
	"row",
	"column",
	"make_canonical"
};*/




bool isDefaultWord(std :: string str);