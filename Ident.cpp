#include "Ident.h"
#include "Constants.h"

Ident::Ident(const string& name) :
	mName(name),
	mIsDeclared(false),
	mType(LEX_NULL),
	mIsAssigned(false)
{
}
