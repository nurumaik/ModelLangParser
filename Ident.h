#ifndef _IDENT_H_
#define _IDENT_H_

#include <string>

using std::string;

class Ident {
public:
	Ident(const string& name);

	/*char *name() {
		return mName;
	}


	void setName (const char *newName) {
		if (mName)
			delete[] mName;
		mName = new char[strlen(newName) + 1];
		strcpy(mName, newName);
	}

	bool isDeclared() const {
		return mIsDeclared;
	}

	bool declare() {
		mIsDeclared = true;
	}

	TYPE_OF_LEX type() const {
		return mType;
	}

	void setType(Lex::TYPE_OF_LEX newType) {
		mType = newType;
	}

	bool isAssigned() const {
		return mIsAssigned;
	}

	void assign() {
		mIsAssigned = true;
	}

	int value() const {
		return mLexValue;
	}

	void setValue(int newValue) {
		mLexValue = newValue;
	}*/

	inline bool operator<(const Ident& i) const  {
		return mName < i.mName;
	}

private:
	string mName;
	bool mIsDeclared;
	int mType;
	bool mIsAssigned;
};

#endif