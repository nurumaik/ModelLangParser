#include "Lex.h"
#include "Scanner.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {
	Scanner s("testprogram.model");
	try {
	while (s.getLex().type() != LEX_NULL) {
		cout << "Lex" << endl;
	}
	}
	catch (Scanner::WrongDelimiterException *e) {
		std::cerr << e->what() << endl;
	}

	return 0;
}
