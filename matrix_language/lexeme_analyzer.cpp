#include "lexeme_analyzer.h"
#include "lexeme_declaration.h"

size_t Lexeme :: current_row = 1;
size_t Lexeme :: current_col = 1;

char gc(std :: ifstream &file) {
	char c = file.get();
	if (c == '\n') {
		++Lexeme :: current_row;
		Lexeme :: current_col = 1;
	} else {
		++Lexeme :: current_col;
	}
	return c;
}

bool isDelimeter(char c) {
	if (c == ' ' || 
		c == '\t' ||
		c == '(' ||
		c == ')' ||
		c == ':' ||
		c == ';' ||
		c == ',' ||
		c == '+' ||
		c == '-' ||
		c == '*' ||
		c == '\\' || 
		c == '/' || 
		c == '[' ||
		c == ']' ||
		//c == '"' ||
		c == '\'' ||
		c == '\n') 
	{
		return true;
	} else {
		return false;
	}

}

bool isSign(char c) {
	if (c == '+' || 
		c == '-' ||
		c == '*' || 
		c == '/' || 
		c == '(' ||
		c == ')' || 
		c == '[' ||
		c == ']' ||
		c == ':' ||
		c == ';' ||
		c == ',' ||
		c == '=' ||
		c == '^') {
		return true;
	} else {
		return false;
	}
}

std :: string Lexeme :: getLexemeType() const {
	std :: string res = "";
	switch(type) {
		case UNKNOWN:
			res += "UNKNOWN";
		break;

		case SIGN:
			res += "SIGN";
		break;

		case ID:
			res += "ID";
		break;

		case NUMBER_TYPE:
			res += "NUMBER_TYPE";
		break;

		case COMMENT:
			res += "COMMENT";
		break;

		case DELIMETER:
			res += "DELIMETER";
		break;

		case END_OF_FILE:
			res += "END_OF_FILE";
		break;

		case PLUS:
			res += "PLUS";
		break;

		case MINUS:
			res += "MINUS";
		break;

		case OPEN_BRACKET:
			res += "OPEN_BRACKET";
		break;

		case CLOSE_BRACKET:
			res += "CLOSE_BRACKET";
		break;

		case DEFAULT_WORD:
			res += "DEFAULT_WORD";
		break;

		case DIVISION:
			res += "DIVISION";
		break;

		case MULTIPLICATION:
			res += "MULTIPLICATION";
		break;

		case SEMICOLON:
			res += "SEMICOLON";
		break;

		case DECLARE:
			res += "DECLARE";
		break;

		case PROCESS:
			res += "PROCESS";
		break;

		case QUOTE_STRING:
			res += "QUOTE_STRING";
		break;

		case BACKSLASH:
			res += "BACKSLASH";
		break;

		case COLON:
			res += "COLON";
		break;

		case COMMA:
			res += "COMMA";
		break;

		case FLOAT_KAPPA:
			res += "FLOAT_KAPPA";
		break;

		case INTEGER:
			res += "INTEGER";
		break;

		case VECTOR_TYPE:
			res += "VECTOR_TYPE";
		break;

		case MATRIX_TYPE:
			res += "MATRIX_TYPE";
		break;

		case RATIONAL:
			res += "RATIONAL";
		break;

		case READ:
			res += "READ";
		break;

		case WRITE:
			res += "WRITE";
		break;

		case PRINT:
			res += "PRINT";
		break;

		case INFO:
			res += "INFO";
		break;

		case ROTATE:
			res += "ROTATE";
		break;

		case ROW:
			res += "ROW";
		break;

		case COLUMN:
			res += "COLUMN";
		break;

		case MAKE_CANONICAL:
			res += "MAKE_CANONICAL";
		break;

		case FLOAT_NUMBER:
			res += "FLOAT_NUMBER";
		break;

		case SQ_OPEN_BRACKET:
			res += "SQ_OPEN_BRACKET";
		break;

		case SQ_CLOSE_BRACKET:
			res += "SQ_CLOSE_BRACKET";
		break;
	}
    return res;
}

Lexeme getLexeme(std :: ifstream &file) {
	Lexeme res;
	res.getLexemeString() = "";
	res.setLexemeType(UNKNOWN);
	res.setLexemeRow(Lexeme :: current_row);
	res.setLexemeCol(Lexeme :: current_col);
	res.setLexemeOp(0);
	res.setLexemeFunc(0);
	char c = gc(file);
	statesLex state = S;
	//std :: string tmp_str; 

	while (c != EOF) {

		if (c == '#') {
			res.getLexemeString() += c;
			//std :: getline(file, tmp_str);
			while((c = gc(file)) != '\n') { }
			//c = gc(file);
			state = END;
			continue;
		}

		if (c == '/') {
			if ((c = gc(file)) == '*') {
				while (c != EOF) {
					if (c != '*') {
						c = gc(file);
						continue;
					} 
					if ((c = gc(file)) == '/') {
						//c = gc(file);
						state = END;
                        res.setLexemeType(COMMENT);
						break;
					} else {
						if (c == '\n') {
							--Lexeme :: current_row;
						}
						--Lexeme :: current_col;
						file.unget();
					}
				}
				if (c == EOF) {
					Lexeme *tmp = new Lexeme(res);
					throw (ExceptionsLanguage(EX_BAD_LEXEME, tmp, LEXEME));
				}
			} else {
				if (c == '\n') {
					--Lexeme :: current_row;
				}
				--Lexeme :: current_col;
				file.unget();
				c = '/';
			}
		}

		switch(state) {
			case S: {
				if (isdigit(c)) {
					state = A;
					res.getLexemeString() += c;
					c = gc(file);
					continue;
				}
				if (isalpha(c) || c == '_') {
					state = C;
					res.getLexemeString() += c;
					c = gc(file);
					continue;
				}
				if (isSign(c)) {
					state = END;
					res.getLexemeString() += c;
					continue;
				} else if (isDelimeter(c)) {
					res.getLexemeString() += c;
					state = END;
					continue;
				}
				if (c == '"') {
					res.getLexemeString() += c;
					while(((c = gc(file)) != '"') && (c != EOF)) {
						if (c == '\\') {
							c = gc(file);
							if (c == 'n') {
								res.getLexemeString() += '\\';
							}
						} 
						res.getLexemeString() += c;
					}
					if (c != EOF) {
						res.getLexemeString() += c;
						state = END;
					} else {
						Lexeme *tmp = new Lexeme(res);
						throw (ExceptionsLanguage(EX_BAD_LEXEME, tmp, LEXEME));
					}
					continue;
				}
				if (c != EOF) {
					Lexeme *tmp = new Lexeme(res);
					throw (ExceptionsLanguage(EX_BAD_LEXEME, tmp, LEXEME));
				} /*else {
					state = END;
					continue;
				}*/
				break;
			}

			case A: {
				if (isdigit(c)) {
					state = A;
					res.getLexemeString() += c;
					c = gc(file);
					continue;
				}
				if (c == '.') {
					state = B;
					res.getLexemeString() += c;
					c = gc(file);
					continue;
				}
				if (isSign(c)) {
					state = END;
					if (c == '\n') {
						--Lexeme :: current_row;
					}
					--Lexeme :: current_col;
					file.unget();
					continue;
				} else if (isDelimeter(c)) {
					state = END;
					if (c == '\n') {
						--Lexeme :: current_row;
					}
					--Lexeme :: current_col;
					file.unget();
					continue;
				}
				Lexeme *tmp = new Lexeme(res);
				throw (ExceptionsLanguage(EX_BAD_LEXEME, tmp, LEXEME));
				break;
			}

			case B: {
				if (isdigit(c)) {
					state = B;
					res.getLexemeString() += c;
					c = gc(file);
					continue;
				}
				if (isSign(c)) {
					state = END;
					if (c == '\n') {
						--Lexeme :: current_row;
					}
					--Lexeme :: current_col;
					file.unget();
					continue;
				} else if (isDelimeter(c)) {
					state = END;
					if (c == '\n') {
						--Lexeme :: current_row;
					}
					--Lexeme :: current_col;
					file.unget();
					continue;
				}
				Lexeme *tmp = new Lexeme(res);
				try {
					throw (ExceptionsLanguage(EX_BAD_LEXEME, tmp, LEXEME));
				}
				catch (ExceptionsLanguage &ex) {
					//delete tmp;
					throw(ex);
				}
				break;
			}

			case C: {
				if (c == '_' || isalpha(c)) {
					state = C;
					res.getLexemeString() += c;
					c = gc(file);
					continue;
				}
				if (isdigit(c)) {
					state = D;
					res.getLexemeString() += c;
					c = gc(file);
					continue;
				}
				if (isSign(c)) {
					state = END;
					if (c == '\n') {
						--Lexeme :: current_row;
					}
					--Lexeme :: current_col;
					file.unget();
					continue;
				} else if (isDelimeter(c)) {
					state = END;
					if (c == '\n') {
						--Lexeme :: current_row;
					}
					--Lexeme :: current_col;
					file.unget();
					continue;
				}
				Lexeme *tmp = new Lexeme(res);
				throw (ExceptionsLanguage(EX_BAD_LEXEME, tmp, LEXEME));
				break;
			}

			case D: {
				if (c == '_' || isalpha(c)) {
					state = C;
					res.getLexemeString() += c;
					c = gc(file);
					continue;
				}
				if (isdigit(c)) {
					state = D;
					res.getLexemeString() += c;
					c = gc(file);
					continue;
				}
				if (isSign(c)) {
					state = END;
					if (c == '\n') {
						--Lexeme :: current_row;
					}
					--Lexeme :: current_col;
					file.unget();
					continue;
				} else if (isDelimeter(c)) {
					state = END;
					if (c == '\n') {
						--Lexeme :: current_row;
					}
					--Lexeme :: current_col;
					file.unget();
					continue;
				}
				Lexeme *tmp = new Lexeme(res);
				throw (ExceptionsLanguage(EX_BAD_LEXEME, tmp, LEXEME));
				break;
			}

			case END: {
				/*if (c == EOF) {  
					res.setLexemeType(END_OF_FILE);
					return res; 
				}*/	 
                if (res.getLexemeType() == "COMMENT") {
                    return res;
                } else if (res.getLexemeString()[0] == '#') {
					res.setLexemeType(COMMENT);
                } else if (isdigit(res.getLexemeString()[0])) {
					res.setLexemeType(NUMBER_TYPE);
					if (res.getLexemeString().find(".") != std :: string :: npos) {
						res.setLexemeType(FLOAT_NUMBER);
					}
				} else if (res.getLexemeString() == "declare") {
					res.setLexemeType(DECLARE);
				} else if (res.getLexemeString() == "process") {
					res.setLexemeType(PROCESS);
				} else if (res.getLexemeString() == "matrix") {
					res.setLexemeType(MATRIX_TYPE);
				} else if (res.getLexemeString() == "float") {
					res.setLexemeType(FLOAT_KAPPA);
				} else if (res.getLexemeString() == "integer") {
					res.setLexemeType(INTEGER);
				} else if (res.getLexemeString() == "vector") {
					res.setLexemeType(VECTOR_TYPE);
				} else if (res.getLexemeString() == "rational") {
					res.setLexemeType(RATIONAL);
				} else if (res.getLexemeString() == "read") {
					res.setLexemeType(READ);
					res.setLexemeFunc(1);
				} else if (res.getLexemeString() == "write") {
					res.setLexemeType(WRITE);
					res.setLexemeFunc(1);
				} else if (res.getLexemeString() == "print") {
					res.setLexemeType(PRINT);
					res.setLexemeFunc(1);
				} else if (res.getLexemeString() == "info") {
					res.setLexemeType(INFO);
					res.setLexemeFunc(1);
				} else if (res.getLexemeString() == "rotate") {
					res.setLexemeType(ROTATE);
					res.setLexemeFunc(1);
				} else if (res.getLexemeString() == "row") {
					res.setLexemeType(ROW);
					res.setLexemeFunc(1);
				} else if (res.getLexemeString() == "column") {
					res.setLexemeType(COLUMN);
					res.setLexemeFunc(1);
				} else if (res.getLexemeString() == "make_canonical") {
					res.setLexemeType(MAKE_CANONICAL);
					res.setLexemeFunc(1);
				} else if (res.getLexemeString()[0] == '+') {
					res.setLexemeType(PLUS);
					res.setLexemeOp(1);
				} else if (res.getLexemeString()[0] == '-') {
					res.setLexemeType(MINUS);
					res.setLexemeOp(1);
				} else if (res.getLexemeString()[0] == '*') {
					res.setLexemeType(MULTIPLICATION);
					res.setLexemeOp(1);
				} else if (res.getLexemeString()[0] == '^') {
					res.setLexemeType(POWER);
					res.setLexemeOp(1);
				} else if (res.getLexemeString()[0] == '/') {
					res.setLexemeType(DIVISION);
					res.setLexemeOp(1);
				} else if (res.getLexemeString()[0] == '(') {
					res.setLexemeType(OPEN_BRACKET);
				} else if (res.getLexemeString()[0] == ')') {
					res.setLexemeType(CLOSE_BRACKET);
				} else if (res.getLexemeString()[0] == '"') {
					res.setLexemeType(QUOTE_STRING);
				} else if (res.getLexemeString()[0] == ':') {
					res.setLexemeType(COLON);
				} else if (res.getLexemeString()[0] == '[') {
					res.setLexemeType(SQ_OPEN_BRACKET);
				} else if (res.getLexemeString()[0] == ']') {
					res.setLexemeType(SQ_CLOSE_BRACKET);
				}
				/*else if (isDefaultWord(res.getLexemeString())) {
					res.setLexemeType(DEFAULT_WORD);
				}*/else if (isalpha(res.getLexemeString()[0])) {
					res.setLexemeType(ID);
				} else if (res.getLexemeString()[0] == ';') {
					res.setLexemeType(SEMICOLON);
				} else if (res.getLexemeString()[0] == '\n') {
					res.setLexemeType(BACKSLASH);
				} else if (res.getLexemeString()[0] == ',') {
					res.setLexemeType(COMMA);
				} else if (res.getLexemeString()[0] == '/') {
					res.setLexemeType(SLASH);
				} else if (isDelimeter(res.getLexemeString()[0])) {
					res.setLexemeType(DELIMETER);
				}
                /*
				if (isSign(res.getLexemeString()[0])) {
					res.setLexemeType(SIGN);
				} else if (isdigit(res.getLexemeString()[0])) {
					res.setLexemeType(NUMBER);
				} else if (isalpha(res.getLexemeString()[0])) {
					res.setLexemeType(ID);
				} else if (res.getLexemeString()[0] == '#') {
					res.setLexemeType(COMMENT);
				} else if (isDelimeter(res.getLexemeString()[0])) {
					res.setLexemeType(DELIMETER);
				} else if (res.getLexemeString()[0] == '"') {
					res.setLexemeType(QUOTE_STRING);
				}*/

				return res;
				break;
			}
		}
	}
	res.setLexemeType(END_OF_FILE);
	return res; 
	//Lexeme *tmp = new Lexeme(res);
	//throw (ExceptionsLanguage(EX_BAD_LEXEME, tmp, LEXEME));
}

