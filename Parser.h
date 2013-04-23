#ifndef _PARSER_H_
#define _PARSER_H_

#include "Constants.h"
#include <stack>
#include <string>
#include "Scanner.h"
#include "Lex.h"

using std::stack;
using std::string;

class Parser {
	public:
		Parser(const string& fileName);
	private:
	//Recursive descent procedures
		void Prog();
		void Decl();
		void Oper();
		void Expr();
	//Other procedures
		void getLex();	

		Lex mCurrentLex;
		stack<int> mIntStack;
		stack<TYPE_OF_LEX> mLexTypeStack;
		Scanner mScanner;
}

#endif
