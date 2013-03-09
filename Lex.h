#ifndef _LEX_H_
#define _LEX_H_ 

#include "Constants.h"
#include <exception>
#include <cstdio>
#include "Ident.h"

using std::exception;

class Lex {
public:
	class WrongTypeException : public exception {
	public:
		WrongTypeException(TYPE_OF_LEX expectation, TYPE_OF_LEX reality);

		virtual const char* what() const noexcept;
	private:
		char mMessage[255];
	};

	TYPE_OF_LEX type() const;

	int 		  intValue()   const;
	float 		  floatVal()   const;
	// bool 		  booleanVal() const;
	const string& stringVal()  const;
	const Ident&  identVal()   const;

	static Lex genSimpleLex(TYPE_OF_LEX type);
	static Lex genIntLex(int value);
	static Lex genFloatLex(float value);
	static Lex genStringLex(const string& value, StringTable *t);
	static Lex genIdentLex(const string& value, IdentTable *t);
	// static Lex genBooleanLex(bool value);
	static Lex genNullLex();

private:
	Lex();
	TYPE_OF_LEX mLexType;
	union {
		StringTable::iterator mCStringId;
		float mFloatVal;
		bool mBooleanVal;
		int mIntVal;
		IdentTable::iterator mIdentID;
	};
};

#endif