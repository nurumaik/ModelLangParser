#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_


#include <string>
#include "Ident.h"

using std::string;

#include <set>
using std::set;
typedef set<Ident> IdentTable;
typedef set<string> StringTable;



enum TYPE_OF_LEX {
	LEX_NULL,
	//--------------Keyword lexes------------------

	LEX_PROGRAM, 
	LEX_INT, 
	LEX_REAL,
	LEX_BOOL, 
	LEX_STRING, 
	LEX_IF, 
	LEX_ELSE, 
	LEX_WHILE, 
	LEX_WRITE, 
	LEX_READ, 
	LEX_NOT, 
	LEX_AND, 
	LEX_OR, 
	LEX_FOR, 
	LEX_GOTO, 
	LEX_BREAK,
	LEX_TRUE, 
	LEX_FALSE,
	LEX_SWITCH, 
	LEX_CASE, 
	LEX_DEFAULT, 
	LEX_STRUCT,
	//---------------------------------------------

	LEX_FIN,
	//-----------Delimiter lexes-------------------

	LEX_SEMICOLON, 
	LEX_COMMA, 
	LEX_COLON, 
	LEX_OCBRACE, 
	LEX_CCBRACE, 
	LEX_ORBRACE, 
	LEX_CRBRACE, 
	LEX_DOT,
	LEX_EQ, 
	LEX_GREATER, 
	LEX_LESS, 
	LEX_GE, 
	LEX_LE, 
	LEX_NE,
	LEX_PLUS, 
	LEX_DIV, 
	LEX_MUL, 
	LEX_SUB, 
	LEX_ASSIGN, 
	LEX_MOD,

	//-------------Const lexes---------------------
	LEX_CONST_INTEGER, 
	LEX_CONST_STRING,
	LEX_CONST_BOOLEAN,
	LEX_CONST_FLOAT,

	//--------------Identifyers--------------------
	LEX_ID
};

#endif
