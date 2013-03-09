#include "Lex.h"
#include "Constants.h"

Lex::Lex() {
}

TYPE_OF_LEX Lex::type() const {
	return mLexType;
}

int Lex::intValue() const {
	if (mLexType == LEX_CONST_INTEGER)
		return mIntVal;
	else 
		throw new WrongTypeException(LEX_CONST_INTEGER, mLexType);
}

float Lex::floatVal() const {
	if (mLexType == LEX_CONST_FLOAT)
		return mFloatVal;
	else 
		throw new WrongTypeException(LEX_CONST_FLOAT, mLexType);
}
/*
bool Lex::booleanVal() const {
	if (mLexType == LEX_CONST_BOOLEAN)
		return mBooleanVal;
	else 
		throw WrongTypeException(LEX_CONST_INTEGER, mLexType);
}*/

const string& Lex::stringVal() const {
	if (mLexType == LEX_CONST_STRING)
		return *mCStringId;
	else
		throw new WrongTypeException(LEX_CONST_STRING, mLexType);
}

const Ident& Lex::identVal() const {
	if (mLexType == LEX_ID)
		return *mIdentID;
	else
		throw new WrongTypeException(LEX_ID, mLexType);
}

Lex Lex::genSimpleLex(TYPE_OF_LEX type) {
	Lex l;
	l.mLexType = type;
	return l;
}

Lex Lex::genIntLex(int value) {
	Lex l;
	l.mLexType = LEX_CONST_INTEGER;
	l.mIntVal = value;
	return l;
}

Lex Lex::genFloatLex(float value) {
	Lex l;
	l.mLexType = LEX_CONST_FLOAT;
	l.mFloatVal = value;
	return l;
}

Lex Lex::genStringLex(const string& value, StringTable *t) {
	Lex l;
	l.mLexType = LEX_CONST_STRING;
	l.mCStringId = t->insert(value).first;
	return l;
}

Lex Lex::genIdentLex(const string& value, IdentTable *t) {
	Lex l;
	l.mLexType = LEX_ID;
	l.mIdentID = t->insert(Ident(value)).first;
	return l;
}

/*Lex Lex::genBooleanLex(bool value) {
	Lex l;
	l.mLexType = LEX_CONST_BOOLEAN;
	l.mFloatVal = value;
	return l;
}*/

Lex Lex::genNullLex() {
	Lex l;
	l.mLexType = LEX_NULL;
	return l;
}

Lex::WrongTypeException::WrongTypeException(TYPE_OF_LEX expectation, TYPE_OF_LEX reality) { //Ожидание - реальность
	sprintf(mMessage, "Wrong lex type! Expected %d type, got %d type.", expectation, reality);
}

const char* Lex::WrongTypeException::what() const noexcept {
	return mMessage;
}