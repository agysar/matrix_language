#include "lexeme_declaration.h"

std :: set<std :: string> SetOfWords = {
	//"declare",
	//"process",
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
};

bool isDefaultWord(std :: string str) {
	if(SetOfWords.count(str)) {
		return true;
	} 
	return false;
};