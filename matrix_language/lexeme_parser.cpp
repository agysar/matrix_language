//#include "lexeme_declaration.h"
#include "lexeme_parser.h"
//#include "lexeme_analyzer.h"
#include <stack>

// declaration 
size_t current_position = 0;
std :: vector<PolizVar*> variable_vec;
std :: vector<PolizElem*> poliz_vec;
std :: stack<PolizFunction> support_stack; 

enum syntaxStates {
	Start,
	A_, // declare
//	Err0,
//	Err1,
	A1,
	M,
	V,
	R,
	F,
	I,
//	Err2,
	M1,
	V1,
	R1,
	F1,
	I1,
	M2,
//	Err3,
	M3,
//	Err4,
	M4,
//	Err5,
	M5,
//	Err6,
//	Err8,
	V2,
	V3,
	V4,
	V5,
	R2,
	R3,
	R4,
	R5,
//	Err7,
	R6, 
	R7,
	R8,
//	Err9,
	R9,
//	Err10,
	F2,
	F3,
	F4,
	F5,
	F6,
	I2,
	I3,
	I4,
	I5,
	I6,
//	S_Process,
/*	A_Process,
	B_Process,
	C_Process,
	F_Process,
	F1_Process,
	H_Process,
	M_Process,
	N_Process,
	A1_Process*/
};

int minus_flag = 1;
size_t numerator = 0;
size_t denominator = 1;
float flt = 0;
int intee = 0;
syntaxStates state = Start;
Lexeme *current_lexeme;
Lexeme previous_lexeme;
std :: string current_label;
std :: vector<Lexeme> *tmp_a;
PolizFunOpenBracket obracket;
PolizFunCloseBracket clbracket;
PolizFunSemicolon semicolon;
//support_stack.push(obracket);

void freeVariableVec() {
	for (auto x : variable_vec) {
		delete x;
	}
}

void freePolizVec() {
	for (auto x : poliz_vec) {
		delete x;
	}
}
// getLexemeFromArray
Lexeme *glfa(std :: vector<Lexeme> &a) {
	++current_position;
	if ((current_position - 1) >= a.size()) {
		freeVariableVec();
		throw(ExceptionsLanguage(EX_ERR_OUT_OF_RANGE, current_lexeme, LEXEME));
	}
	return (&a.front() + current_position - 1);
}

//check if the variable in the vector
PolizVar *isVar(Lexeme &a) {
	for(auto const& value: variable_vec) {
		if (value->getLabel() == a.getLexemeString()) {
			return value;
		} 
	}
	return nullptr;
}

//support_stack.push("(");


/*void Pop_Process() { // pop out of the stack push to the POLIZ if we see the ; or )
	while(support_stack.size()) {
		switch(support_stack.top()) {

		}
	}
}*/


void Info_Process(std :: vector<Lexeme> &a) {
	if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		if (current_lexeme->getLexemeType() == "QUOTE_STRING") {
			previous_lexeme = *current_lexeme;
			current_lexeme = glfa(a);
			if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
				previous_lexeme = *current_lexeme;
				current_lexeme = glfa(a);
				return;
			}
		}
	}
	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR21, current_lexeme, LEXEME));
}

void S_Process(std :: vector<Lexeme> &a) {
	if (isVar(*current_lexeme) != nullptr) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		A_Process(a);
		return;
	} else if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
		//support_stack.push("(");
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		S_Process(a);
		return;
	} else if (current_lexeme->getLexemeType() == "SEMICOLON") {
		//Pop_Process();
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		S_Process(a);
		return;
	} else if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		S_Process(a);
		return;
	} else if (current_lexeme->getLexemeType() == "NUMBER_TYPE" ||
				current_lexeme->getLexemeType() == "FLOAT_NUMBER") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		B_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "END_OF_FILE") {
		return;
	}
	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR11, current_lexeme, LEXEME));
}

void A_Process(std :: vector<Lexeme> &a) {
	//poliz_vec.push_back(isVar(current_lexeme));
	if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		A_Process(a);
		return;
	}

	if (current_lexeme->getLexemeString() == "=") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		M_Process(a);
		return;
	}

	if (current_lexeme->isop()) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		N_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		H_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "SEMICOLON") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		S_Process(a);
		return;
	}
	
	if (current_lexeme->getLexemeType() == "SQ_OPEN_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		D_Process(a);
		return;	
	}

	if (current_lexeme->getLexemeType() == "COLON") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		if (current_lexeme->isfunc()) {
			previous_lexeme = *current_lexeme;
			current_lexeme = glfa(a);
			if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
				F2_Process(a);
			} else {
				F_Process(a);
			}
			return;
		}
	}

	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR12, current_lexeme, LEXEME));	
}

void B_Process(std :: vector<Lexeme> &a) {
	if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		B_Process(a);
		return;
	}

	if (current_lexeme->isop()) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		N_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		H_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "SEMICOLON") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		S_Process(a);
		return;
	}

	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR13, current_lexeme, LEXEME));		
}

void F_Process(std :: vector<Lexeme> &a) {
	if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		F_Process(a);
		return;
	}

	if (current_lexeme->isop()) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		N_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		H_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "SEMICOLON") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		S_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "QUOTE_STRING") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		F1_Process(a);
		return;
	}

	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR14, current_lexeme, LEXEME));
}

void F1_Process(std :: vector<Lexeme> &a) {
	if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		F1_Process(a);
		return;
	}

	if (current_lexeme->isop()) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		N_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		H_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "SEMICOLON") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		S_Process(a);
		return;
	}

	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR15, current_lexeme, LEXEME));
}

void F2_Process(std :: vector<Lexeme> &a) {
	if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		F_Process(a);
		return;
	} 

	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR15, current_lexeme, LEXEME));
}

void H_Process(std :: vector<Lexeme> &a) {
	if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		H_Process(a);
		return;
	}

	if (current_lexeme->isop()) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		N_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		H_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "SEMICOLON") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		S_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "COLON") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		if (current_lexeme->isfunc()) {
			previous_lexeme = *current_lexeme;
			current_lexeme = glfa(a);
			F_Process(a);
			return;
		}
	}

	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR16, current_lexeme, LEXEME));
}

void D_Process(std :: vector<Lexeme> &a) {
	if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		D_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "NUMBER_TYPE" //||
				//current_lexeme->getLexemeType() == "FLOAT_NUMBER"
				) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		if (current_lexeme->getLexemeType() == "COMMA") {
			previous_lexeme = *current_lexeme;
			current_lexeme = glfa(a);
			if (current_lexeme->getLexemeType() == "NUMBER_TYPE" ||
				//current_lexeme->getLexemeType() == "FLOAT_NUMBER" ||
				isVar(*current_lexeme) != nullptr) {
				previous_lexeme = *current_lexeme;
				current_lexeme = glfa(a);
				if (current_lexeme->getLexemeType() == "SQ_CLOSE_BRACKET") {
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					H_Process(a);
					return;
				}
			}
		} else if (current_lexeme->getLexemeType() == "SQ_CLOSE_BRACKET") {
			previous_lexeme = *current_lexeme;
			current_lexeme = glfa(a);
			H_Process(a);
			return;
		}
	} else if (isVar(*current_lexeme) != nullptr) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		if (current_lexeme->getLexemeType() == "COMMA") {
			previous_lexeme = *current_lexeme;
			current_lexeme = glfa(a);
			if (current_lexeme->getLexemeType() == "NUMBER_TYPE" ||
				//current_lexeme->getLexemeType() == "FLOAT_NUMBER" ||
				isVar(*current_lexeme) != nullptr) {
				previous_lexeme = *current_lexeme;
				current_lexeme = glfa(a);
				if (current_lexeme->getLexemeType() == "SQ_CLOSE_BRACKET") {
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					H_Process(a);
					return;
				}
			}
		} else if (current_lexeme->getLexemeType() == "SQ_CLOSE_BRACKET") {
			previous_lexeme = *current_lexeme;
			current_lexeme = glfa(a);
			H_Process(a);
			return;
		}
	}

	
	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR17, current_lexeme, LEXEME));
}

void M_Process(std :: vector<Lexeme> &a) {
	if (isVar(*current_lexeme) != nullptr) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		A_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "NUMBER_TYPE" ||
				current_lexeme->getLexemeType() == "FLOAT_NUMBER") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		B_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		M_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		M_Process(a);
		return;
	}

	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR18, current_lexeme, LEXEME));
}

void N_Process(std :: vector<Lexeme> &a) {
	if (isVar(*current_lexeme) != nullptr) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Q_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "NUMBER_TYPE" ||
				current_lexeme->getLexemeType() == "FLOAT_NUMBER") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		B_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		M_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		N_Process(a);
		return;
	}	

	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR19, current_lexeme, LEXEME));		
}

void Q_Process(std :: vector<Lexeme> &a) {
	if (current_lexeme->getLexemeType() == "INFO") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		Info_Process(a);
		Q_Process(a);
		return;
	}

	if (current_lexeme->isop()) {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		N_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		H_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "SEMICOLON") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		S_Process(a);
		return;
	}

	if (current_lexeme->getLexemeType() == "COLON") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		if (current_lexeme->isfunc()) {
			previous_lexeme = *current_lexeme;
			current_lexeme = glfa(a);
			F_Process(a);
			return;
		}
	}

	if (current_lexeme->getLexemeType() == "SQ_OPEN_BRACKET") {
		previous_lexeme = *current_lexeme;
		current_lexeme = glfa(a);
		D_Process(a);
		return;	
	}

	freeVariableVec();
	throw(ExceptionsLanguage(EX_ERR20, current_lexeme, LEXEME));	
}

void syntaxAnalyzer(std :: vector<Lexeme> &a) {
	
	current_lexeme = glfa(a);
	while(current_lexeme->getLexemeType() != "END_OF_FILE") {
		switch(state) {
			case Start: {
				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = Start;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "DECLARE") {
					state = A_;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR0, current_lexeme, LEXEME));
				break;
			}

			case A_: {
				if (current_lexeme->getLexemeType() == "COLON") {
					state = A1;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR1, current_lexeme, LEXEME));
				break;
			}

			case A1: {
				if (current_lexeme->getLexemeType() == "MATRIX_TYPE") {
					state = M;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "VECTOR_TYPE") {
					state = V;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "RATIONAL") {
					state = R;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "FLOAT_KAPPA") {
					state = F;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "INTEGER") {
					state = I;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "PROCESS") {
					current_lexeme = glfa(a);
					if (current_lexeme->getLexemeType() == "COLON") {
						current_lexeme = glfa(a);
						tmp_a = &a;
						goto START_PROCESS;//S_Process();
					}
					freeVariableVec();
					throw(ExceptionsLanguage(EX_ERR1, current_lexeme, LEXEME));
					//continue;
				}
				throw(ExceptionsLanguage(EX_ERR2, current_lexeme, LEXEME));
				break;
			}

			case M: {
				if (current_lexeme->getLexemeType() == "COLON") {
					state = M1;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR1, current_lexeme, LEXEME));
				break;
			}

			case V: {
				if (current_lexeme->getLexemeType() == "COLON") {
					state = V1;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR1, current_lexeme, LEXEME));
				break;
			}

			case R: {
				if (current_lexeme->getLexemeType() == "COLON") {
					state = R1;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR1, current_lexeme, LEXEME));
				break;
			}

			case F: {
				if (current_lexeme->getLexemeType() == "COLON") {
					state = F1;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR1, current_lexeme, LEXEME));
				break;
			}

			case I: {
				if (current_lexeme->getLexemeType() == "COLON") {
					state = I1;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR1, current_lexeme, LEXEME));
				break;
			}

			case M1: {
				if (current_lexeme->getLexemeType() == "ID") {
					state = M2;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR3, current_lexeme, LEXEME));
				break;
			}

			case V1: {
				if (current_lexeme->getLexemeType() == "ID") {
					state = V2;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR3, current_lexeme, LEXEME));
				break;
			}

			case R1: {
				if (current_lexeme->getLexemeType() == "ID") {
					state = R2;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR3, current_lexeme, LEXEME));
				break;
			}

			case F1: {
				if (current_lexeme->getLexemeType() == "ID") {
					state = F2;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR3, current_lexeme, LEXEME));
				break;
			}

			case I1: {
				if (current_lexeme->getLexemeType() == "ID") {
					state = I2;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR3, current_lexeme, LEXEME));
				break;
			}

			case M2: {
				if (current_lexeme->getLexemeType() == "COMMA") {
					RationalMatrix tmp;
					PolizMatrix *mtrx = 
						new PolizMatrix(tmp, 
							previous_lexeme.getLexemeString());
					variable_vec.push_back(mtrx);
					state = M1;
					std :: cout << previous_lexeme.getLexemeString() << "\n";
					tmp.to_out();
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
					state = M3;
					current_label = previous_lexeme.getLexemeString();
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					if (previous_lexeme.getLexemeType() == "ID") {
						RationalMatrix tmp;
						PolizMatrix *mtrx = 
							new PolizMatrix(tmp, 
								previous_lexeme.getLexemeString());
						variable_vec.push_back(mtrx);
						std :: cout << previous_lexeme.getLexemeString() << "\n";
						tmp.to_out();
					}
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR4, current_lexeme, LEXEME));
				break;
			}

			case M3: {
				if (current_lexeme->getLexemeType() == "QUOTE_STRING") {
					const char *tmp_str = (current_lexeme->getLexemeString()).c_str();
					size_t len = strlen(tmp_str);
					char *tmp_s = new char[len - 1];
					for (size_t j = 1; j < len - 1; ++j) {
						tmp_s[j - 1] = tmp_str[j];
					}
					tmp_s[len - 2] = '\0';
					try {
						RationalMatrix tmp(tmp_s);
						delete[] tmp_s;
						PolizMatrix *mtrx = 
						new PolizMatrix(tmp, 
							current_label);
						variable_vec.push_back(mtrx);
						state = M4;
						std :: cout << current_label << "\n";
						tmp.to_out();
					} catch (Exceptions &ex) {
						delete[] tmp_s;
						freeVariableVec();
						freePolizVec();
						throw (ex);
					}
					
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR5, current_lexeme, LEXEME));
				break;
			}

			case M4: {
				if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
					state = M5;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR6, current_lexeme, LEXEME));
				break;
			}

			case M5: {
				if (current_lexeme->getLexemeType() == "COMMA") {
					state = M1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR8, current_lexeme, LEXEME));
				break;
			}

			case V2: {
				if (current_lexeme->getLexemeType() == "COMMA") {
					RationalVector tmp;
					PolizVector *vctr = 
						new PolizVector(tmp, 
							previous_lexeme.getLexemeString());
					variable_vec.push_back(vctr);
					state = V1;
					std :: cout << previous_lexeme.getLexemeString() << "\n";
					tmp.to_out();
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
					state = V3;
					current_label = previous_lexeme.getLexemeString();
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					if (previous_lexeme.getLexemeType() == "ID") {
						RationalVector tmp;
						PolizVector *vctr = 
							new PolizVector(tmp, 
								previous_lexeme.getLexemeString());
						variable_vec.push_back(vctr);
						std :: cout << previous_lexeme.getLexemeString() << "\n";
						tmp.to_out();
					}
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR4, current_lexeme, LEXEME));
				break;
			}

			case V3: {
				if (current_lexeme->getLexemeType() == "QUOTE_STRING") {
					const char *tmp_str = (current_lexeme->getLexemeString()).c_str();
					size_t len = strlen(tmp_str);
					char *tmp_s = new char[len - 1];
					for (size_t j = 1; j < len - 1; ++j) {
						tmp_s[j - 1] = tmp_str[j];
					}
					tmp_s[len - 2] = '\0';
					try {
						RationalVector tmp(tmp_s);
						delete[] tmp_s;
						PolizVector *vctr = 
							new PolizVector(tmp, 
								current_label);
						variable_vec.push_back(vctr);
						state = V4;
						std :: cout << current_label << "\n";
						tmp.to_out();
					}
					catch (Exceptions &ex) {
						delete[] tmp_s;
						freeVariableVec();
						freePolizVec();
						throw (ex);
					}
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR5, current_lexeme, LEXEME));
				break;
			}

			case V4: {
				if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
					state = V5;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR6, current_lexeme, LEXEME));
				break;
			}

			case V5: {
				if (current_lexeme->getLexemeType() == "COMMA") {
					state = V1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR8, current_lexeme, LEXEME));
				break;
			}

			case R2: {
				if (current_lexeme->getLexemeType() == "COMMA") {
					RationalNumber tmp;
					PolizRational *nmbr = 
						new PolizRational(tmp, 
							previous_lexeme.getLexemeString());
					variable_vec.push_back(nmbr);
					state = R1;
					std :: cout << previous_lexeme.getLexemeString() << "\n";
					std :: cout << tmp << "\n";
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
					state = R3;
					current_label = previous_lexeme.getLexemeString();
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					if (previous_lexeme.getLexemeType() == "ID") {
						RationalNumber tmp;
						PolizRational *nmbr = 
							new PolizRational(tmp, 
								previous_lexeme.getLexemeString());
						variable_vec.push_back(nmbr);
						std :: cout << previous_lexeme.getLexemeString() << "\n";
						std :: cout << tmp << "\n";
					}
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR4, current_lexeme, LEXEME));
				break;
			}

			case R3: {
				if (current_lexeme->getLexemeType() == "MINUS") {
					minus_flag = -1;
					state = R4;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "NUMBER_TYPE") {
					numerator = std :: stoi(current_lexeme->getLexemeString());
					state = R5;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR7, current_lexeme, LEXEME));
				break;				
			}

			case R4: {
				if (current_lexeme->getLexemeType() == "NUMBER_TYPE") {
					numerator = std :: stoi(current_lexeme->getLexemeString());
					state = R6;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR7, current_lexeme, LEXEME));
				break;
			}

			case R5: {
				if (current_lexeme->getLexemeType() == "DIVISION") {
					state = R8;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
					state = R7;
					RationalNumber tmp(numerator, denominator);
					tmp = tmp * RationalNumber(minus_flag);
					PolizRational *nmbr = 
						new PolizRational(tmp, 
							current_label);
					variable_vec.push_back(nmbr);
					std :: cout << current_label << "\n";
					std :: cout << tmp << "\n";
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR8, current_lexeme, LEXEME));
				break;
			}

			case R6: {
				if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
					state = R7;
					RationalNumber tmp(numerator, denominator);
					tmp = tmp * RationalNumber(minus_flag);
					PolizRational *nmbr = 
						new PolizRational(tmp, 
							current_label);
					variable_vec.push_back(nmbr);
					std :: cout << current_label << "\n";
					std :: cout << tmp << "\n";
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "DIVISION") {
					state = R8;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR9, current_lexeme, LEXEME));
				break;
			}

			case R7: {
				minus_flag = 1;
				numerator = 0;
				denominator = 1;

				if (current_lexeme->getLexemeType() == "COMMA") {
					state = R1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR8, current_lexeme, LEXEME));
				break;
			}

			case R8: {
				if (current_lexeme->getLexemeType() == "NUMBER_TYPE") {
					denominator = std :: stoi(current_lexeme->getLexemeString());
					state = R9;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR10, current_lexeme, LEXEME));
				break;
			}

			case R9: {
				if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
					state = R7;
					RationalNumber tmp(numerator, denominator);
					tmp = tmp * RationalNumber(minus_flag);
					PolizRational *nmbr = 
						new PolizRational(tmp, 
							current_label);
					variable_vec.push_back(nmbr);
					std :: cout << current_label << "\n";
					std :: cout << tmp << "\n";
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR6, current_lexeme, LEXEME));
				break;
			}

			case F2: {
				if (current_lexeme->getLexemeType() == "COMMA") {
					float tmp = 0;
					PolizFloat *nmbr = 
						new PolizFloat(tmp, 
							previous_lexeme.getLexemeString());
					variable_vec.push_back(nmbr);
					state = F1;
					std :: cout << previous_lexeme.getLexemeString() << "\n";
					std :: cout << tmp << "\n";
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
					state = F3;
					current_label = previous_lexeme.getLexemeString();
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					if (previous_lexeme.getLexemeType() == "ID") {
						float tmp = 0;
						PolizFloat *nmbr = 
							new PolizFloat(tmp, 
								previous_lexeme.getLexemeString());
						variable_vec.push_back(nmbr);
						std :: cout << previous_lexeme.getLexemeString() << "\n";
						std :: cout << tmp << "\n";
					}
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR4, current_lexeme, LEXEME));
				break;
			}

			case F3: {
				if (current_lexeme->getLexemeType() == "MINUS") {
					minus_flag = -1;
					state = F6;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "NUMBER_TYPE") {
					flt = std :: stoi(current_lexeme->getLexemeString());
					state = F4;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "FLOAT_NUMBER") {
					flt = std :: stof(current_lexeme->getLexemeString(), nullptr);
					state = F4;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR7, current_lexeme, LEXEME));
				break;
			}

			case F4: {
				if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
					state = F5;
					float tmp = flt;
					tmp = tmp * minus_flag;
					PolizFloat *nmbr = 
						new PolizFloat(tmp, 
							current_label);
					variable_vec.push_back(nmbr);
					std :: cout << current_label << "\n";
					std :: cout << tmp << "\n";
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR6, current_lexeme, LEXEME));
				break;
			}

			case F5: {
				minus_flag = 1;
				flt = 0;

				if (current_lexeme->getLexemeType() == "COMMA") {
					state = F1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR9, current_lexeme, LEXEME));
				break;
			}

			case F6: {
				if (current_lexeme->getLexemeType() == "NUMBER_TYPE") {
					flt = std :: stoi(current_lexeme->getLexemeString());
					state = F4;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "FLOAT_NUMBER") {
					flt = std :: stof(current_lexeme->getLexemeString(), nullptr);
					state = F4;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR7, current_lexeme, LEXEME));
				break;
			}

			case I2: {
				if (current_lexeme->getLexemeType() == "COMMA") {
					int tmp = 0;
					PolizInt *nmbr = 
						new PolizInt(tmp, 
							previous_lexeme.getLexemeString());
					variable_vec.push_back(nmbr);
					state = I1;
					std :: cout << previous_lexeme.getLexemeString() << "\n";
					std :: cout << tmp << "\n";
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "OPEN_BRACKET") {
					state = I3;
					current_label = previous_lexeme.getLexemeString();
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					if (previous_lexeme.getLexemeType() == "ID") {
						int tmp = 0;
						PolizInt *nmbr = 
							new PolizInt(tmp, 
								previous_lexeme.getLexemeString());
						variable_vec.push_back(nmbr);
						std :: cout << previous_lexeme.getLexemeString() << "\n";
						std :: cout << tmp << "\n";
					}
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR4, current_lexeme, LEXEME));
				break;
			}

			case I3: {
				if (current_lexeme->getLexemeType() == "MINUS") {
					minus_flag = -1;
					state = I6;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "NUMBER_TYPE") {
					intee = std :: stoi(current_lexeme->getLexemeString());
					state = I4;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR7, current_lexeme, LEXEME));
				break;
			}

			case I4: {
				if (current_lexeme->getLexemeType() == "CLOSE_BRACKET") {
					state = I5;
					int tmp = intee;
					tmp = tmp * minus_flag;
					PolizInt *nmbr = 
						new PolizInt(tmp, 
							current_label);
					variable_vec.push_back(nmbr);
					std :: cout << current_label << "\n";
					std :: cout << tmp << "\n";
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR6, current_lexeme, LEXEME));
				break;
			}

			case I5: {
				minus_flag = 1;
				intee = 0;

				if (current_lexeme->getLexemeType() == "COMMA") {
					state = I1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}

				if (current_lexeme->getLexemeType() == "SEMICOLON") {
					state = A1;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR9, current_lexeme, LEXEME));
				break;
			}

			case I6: {
				if (current_lexeme->getLexemeType() == "NUMBER_TYPE") {
					intee = std :: stoi(current_lexeme->getLexemeString());
					state = I4;
					previous_lexeme = *current_lexeme;
					current_lexeme = glfa(a);
					continue;
				}
				freeVariableVec();
				throw(ExceptionsLanguage(EX_ERR7, current_lexeme, LEXEME));
				break;
			}
			// declare ended here
			/*case S_Process: {
				
			}*/
		}
	}
	START_PROCESS:
		std :: cout << "DECLARE OK...\n"; 
		S_Process(a);
	for (size_t j = 0; j < variable_vec.size(); ++j) {
		delete variable_vec[j];
	}
	std :: cout << "PROCESS OK...\n";
}