#include "Scanner.h"

Lex Scanner::getLex() {
	int intBuf = 0;
	float floatBuf = 0;
	float floatTmp = 0.1f;
	mState = BEGIN;
	for (;;)
		switch (mState) {
		case BEGIN:
			if (mInput.eof())
				return Lex::genNullLex();
			else if (isalpha(mSymbol)) {
				clearBuf();
				pushToBuf();
				getNextChar();
				mState = WORD;
			}
			else if (isdigit(mSymbol)) {
				intBuf = mSymbol - '0';
				getNextChar();
				mState = NUMBER;
			}
			else if (string("=<>!").find(mSymbol) != string::npos) {
				clearBuf();
				pushToBuf();
				getNextChar();
				mState = COMPARE;
			}
			else if (string(" \r\t").find(mSymbol) != string::npos)
				getNextChar();
			else if (mSymbol == '\n') {
				getNextChar();
				mCurrentString++;
			}
			else if (mSymbol == '\"') {
				clearBuf();
				getNextChar();
				mState = STRING;
			}
			else if (mSymbol == '/') {
				getNextChar();
				mState = SLASH;
			}
			else
				mState = DELIM; 
			break;
		case STRING:
			if (mInput.eof())
				throw new StringWithoutEndException(mCurrentString);
			else if (mSymbol == '\\') {
				getNextChar();
				switch (mSymbol) {
					case 'n':
						mBuf.push_back('\n');
						break;
					case 't':
						mBuf.push_back('\t');
						break;
					case 'r':
						mBuf.push_back('\r');
						break;
					case '\"':
						mBuf.push_back('\"');
						break;
					case '\'':
						mBuf.push_back('\'');
						break;
					case '\\':
						mBuf.push_back('\\');
						break;
					default:
						mBuf.push_back('\\');
						mBuf.push_back(mSymbol);
						break;
				}
			}
			else if (mSymbol == '\"') {
				getNextChar();
				return Lex::genStringLex(mBuf, &mTS);
			}
			else {
				pushToBuf();
				getNextChar();
			}
			break;
		case WORD:
			if (isalpha(mSymbol) || isdigit(mSymbol)) {
				pushToBuf();
				getNextChar();
			}
			else {
				Table::const_iterator t = mKeywords.find(mBuf);
				if (t != mKeywords.end())
					return Lex::genSimpleLex(t->second);
				else 
					return Lex::genIdentLex(mBuf, &mTID);
			}
			break;
		case NUMBER:
			if (isdigit(mSymbol)) {
				(intBuf *= 10) += (mSymbol - '0');
				getNextChar();
			}
			else if (mSymbol == '.') {
				floatBuf = intBuf;
				mState = REAL;
				getNextChar();
			}
			else
				return Lex::genIntLex(intBuf);
			break;
		case REAL:
			if(isdigit(mSymbol)) {
				floatBuf += floatTmp * (mSymbol - '0');
				floatTmp /= 10;
				getNextChar();
			}
			else
				return Lex::genFloatLex(floatBuf);
			break;
		case SLASH:
			if (mSymbol == '*') {
				getNextChar();
				mState = COMMENT;
			}
			else
				return Lex::genSimpleLex(LEX_DIV);
			break;
		case COMMENT:
			if (mSymbol != '*')
				getNextChar();
			else {
				getNextChar();
				if (mSymbol == '/') {
					getNextChar();
					mState = BEGIN;
				}
			}
			if (mInput.eof())
				throw new CommentWithoutEndException(mCurrentString);
			break;
		case COMPARE:
			if (mSymbol == '=') {
				pushToBuf();
				getNextChar();
				return Lex::genSimpleLex(mDelimiters.find(mBuf)->second);
			}
			else {
				Table::const_iterator t = mDelimiters.find(mBuf);
				if (t != mDelimiters.end())
					return Lex::genSimpleLex(t->second);
				else
					throw new WrongDelimiterException(mCurrentString, mBuf);
			}
			break;
		case DELIM: {
			clearBuf();
			pushToBuf();
			Table::const_iterator t = mDelimiters.find(mBuf);
			if (t != mDelimiters.end()) {
				getNextChar();
				return Lex::genSimpleLex(t->second);
			}
			else
				throw new WrongDelimiterException(mCurrentString, mBuf);
			break;
		}
		default:
			throw new O_o();
		}
	return Lex::genNullLex();
}

const map<string, TYPE_OF_LEX> Scanner::mKeywords = { 
	std::make_pair(""       , LEX_NULL),
	std::make_pair("and"    , LEX_AND),
	std::make_pair("boolean", LEX_BOOL),
	std::make_pair("break"  , LEX_BREAK),
	std::make_pair("case"   , LEX_CASE),
	std::make_pair("default", LEX_DEFAULT),
	std::make_pair("else"   , LEX_ELSE),
	std::make_pair("false"  , LEX_FALSE),
	std::make_pair("for"    , LEX_FOR),
	std::make_pair("goto"   , LEX_GOTO),
	std::make_pair("if"     , LEX_IF),
	std::make_pair("int"    , LEX_INT),
	std::make_pair("not"    , LEX_NOT),
	std::make_pair("or"     , LEX_OR),
	std::make_pair("program", LEX_PROGRAM),
	std::make_pair("read"   , LEX_READ),
	std::make_pair("string" , LEX_STRING),
	std::make_pair("real"   , LEX_REAL),
	std::make_pair("struct" , LEX_STRUCT),
	std::make_pair("switch" , LEX_SWITCH),
	std::make_pair("true"   , LEX_TRUE),
	std::make_pair("while"  , LEX_WHILE),
	std::make_pair("write"  , LEX_WRITE)
};

const map<string, TYPE_OF_LEX> Scanner::mDelimiters {
	std::make_pair(""  , LEX_NULL),
	std::make_pair("=" , LEX_ASSIGN),
	std::make_pair(":" , LEX_COLON),
	std::make_pair("," , LEX_COMMA),
	std::make_pair("==", LEX_EQ),
	std::make_pair(">=", LEX_GE),
	std::make_pair("(" , LEX_ORBRACE),
	std::make_pair("<=", LEX_LE),
	std::make_pair("<" , LEX_LESS),
	std::make_pair("-" , LEX_SUB),
	std::make_pair(">" , LEX_GREATER),
	std::make_pair("*" , LEX_MUL),
	std::make_pair("!=", LEX_NE),
	std::make_pair(";" , LEX_SEMICOLON),
	std::make_pair("%" , LEX_MOD),
	std::make_pair("+" , LEX_PLUS),
	std::make_pair("." , LEX_DOT),
	std::make_pair(")" , LEX_CRBRACE),
	std::make_pair("/" , LEX_DIV),
	std::make_pair("{" , LEX_OCBRACE),
	std::make_pair("}" , LEX_CCBRACE)
};

Scanner::Scanner(const string& fileName) :
	mState(BEGIN),
	mCurrentString(1),
	mInput(fileName.c_str()) 
{
	getNextChar();	
}

Scanner::LexerException::LexerException() {

}

Scanner::LexerException::LexerException(int strId) {
	sprintf(mMessage, "Error at line %d\n", strId);
}

const char* Scanner::LexerException::what() const noexcept {
	return mMessage;
}

Scanner::O_o::O_o() {
	strcpy(mMessage, "O_o");
}

Scanner::WrongDelimiterException::WrongDelimiterException(int strId, const string& delim) {
	sprintf(mMessage, "Unexpected delimiter %c with code %d at line %d", delim.c_str(), delim.c_str()[0], strId);
}

Scanner::CommentWithoutEndException::CommentWithoutEndException(int strId) {
	sprintf(mMessage, "Unexpected EOF at line %d: comment without end\n", strId);
}

Scanner::StringWithoutEndException::StringWithoutEndException(int strId) {
	sprintf(mMessage, "Unexpected EOF at line %d: string without end\n", strId);
}


Scanner::LexerException::
