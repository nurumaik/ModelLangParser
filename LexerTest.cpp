#include "Lex.h"
#include "Scanner.h"
#include <iostream>
using std::cout;
using std::endl;

int main() {
	Scanner s("testprogram.model");
	while (s.getLex().type() != LEX_NULL) {
		cout << "Lex" << endl;
	}

	return 0;
}