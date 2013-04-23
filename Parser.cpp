#include "Parser.h"

Parser::Parser(const string& fileName) :
	mScanner(fileName) 
{
}

void Parser::getLex() {
	mCurrentLex = mScanner.getLex();

}

void Parser::Prog() {
	if (mCurrentLex.type() != LEX_PROGRAM)
		;//TODO: throw
	getLex();
	if (mCurrentLex.type() != LEX_OCBRACE)
		;//TODO: throw
	getLex();
	Decl();
	if (mCurrentLex.type() != LEX_CCBRACE)
		;//TODO: throw
	getLex();
	if (mCurrentLex.type() != LEX_NULL)
		;//TODO: throw
}

void Parser::Decl() {
	while (mCurrentLex.type() == LEX_REAL || mCurrentLex.type() == LEX_INT || mCurrentLex.type() == LEX_BOOL || mCurrentLex.type() == LEX_STRING) {
		
		getLex();
	}
}


