//#include "lexeme_analyzer.h"
#include "lexeme_parser.h"

using namespace std;



int main() {
	vector<Lexeme> lexeme_vector;
	ifstream file;
	file.open("kappa");

	Lexeme tmp;
	try {
		while(true) {
			tmp = getLexeme(file);
			if (tmp.getLexemeType() == "END_OF_FILE") {
				lexeme_vector.push_back(tmp);
				break;
			}
			if (tmp.getLexemeType() != "DELIMETER" && 
				tmp.getLexemeType() != "COMMENT" && 
				tmp.getLexemeType() != "BACKSLASH") { 
				/*cout << "type: " << tmp.getLexemeType() << endl
			 	<< "lex: " << tmp.getLexemeString() << endl
			 	<< "row: " << tmp.getLexemeRow() << endl
			 	<< "col: " << tmp.getLexemeCol() << endl;*/
			 	lexeme_vector.push_back(tmp);
			}
		}
		cout << "LEX OK...\n"; 
		try {
			syntaxAnalyzer(lexeme_vector);
		}
		catch(Exceptions &ex) {
			cout << ex.get_error_str() << endl;
			return 0;
		}
		catch(ExceptionsLanguage &ex) {
			ex.printException();
			return 0;
		}
	}
	catch(ExceptionsLanguage &ex) {
		ex.printException();
		return 0;
	}

	
	/*for (size_t i = 0; i < poliz_vec.size(); ++i) {
		cout << poliz_vec[i]->get();
	}*/
	return 0;
}