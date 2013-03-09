#ifndef _SCANNER_H_
#define _SCANNER_H_

#include <string>
#include <fstream>
#include <map>
#include <exception>
#include <cstdio>
#include <cstring>
#include "Lex.h"
#include "Constants.h"

using std::string;
using std::ifstream;
using std::map;
using std::exception;

class Scanner {	
public:
	class LexerException : public exception {
	public:
		LexerException() {

		}

		LexerException(int strId)/* : mStringNumber(strId)*/ {
			sprintf(mMessage, "Error at line %d\n", strId);
		}

		virtual const char* what() const noexcept {
			return mMessage;
		}
	protected:
		//unsigned int mStringNumber;
		char mMessage [255];
	};

	class StringWithoutEndException : public LexerException {
	public:
		StringWithoutEndException(int strId) {
			sprintf(mMessage, "Unexpected EOF at line %d: string without end\n", strId);
		}
	};

	class CommentWithoutEndException : public LexerException {
	public:
		CommentWithoutEndException(int strId) {
			sprintf(mMessage, "Unexpected EOF at line %d: comment without end\n", strId);
		}
	};

	class WrongDelimiterException : public LexerException {
	public:
		WrongDelimiterException(int strId, const string& delim) {
			sprintf(mMessage, "Unexpected delimiter %s at line %d", delim.c_str(), strId);
		}
	};

	class O_o : public LexerException {
	public:
		O_o() {
			strcpy(mMessage, "O_o");
		}
	};

	Lex getLex();
	//char showChar() const;
	Scanner(const string& fileName);
	~Scanner() = default;
private:
	inline void getNextChar() {
		mInput.get(mSymbol);
	}
	inline void pushToBuf() {
		mBuf.push_back(mSymbol);
	}
	inline void clearBuf() {
		mBuf.clear();
	} //...and this functions can be removed safely too

	enum State {BEGIN, NUMBER, WORD, SLASH, COMMENT, REAL, COMPARE, DELIM, STRING};

	typedef map<string, TYPE_OF_LEX> Table;

	static const Table mKeywords;
	static const Table mDelimiters;

	IdentTable mTID;
	StringTable mTS;
	State mState;
	string mBuf; //TODO: state and buf can be in-function variables
	char mSymbol;
	unsigned int mCurrentString;
	ifstream mInput;
};

#endif
