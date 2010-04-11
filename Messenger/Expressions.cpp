// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Built-in expressions
//////////////////////////////////////////////////////////////////////////////////

// Return the Default Value.  This is the value to be returned if your object name
// is used without an expression name, eg. in "Counter + 1".
// Parameters can be passed, eg. MyObject(3,7).  You can check ExpReturn::Type() or GetNumParams() to check for overloads.
long ExtObject::ReturnDefaultValue(LPVAL theParams, ExpReturn& ret)
{
	return ret = 0;
}

// Called for undefined expression names, if your extension allows it.
// Eg: MyObject.UndefinedExpression(3,4,5) calls this routine with
// "UndefinedExpression" as the expression name.  OF_UNDEFINEDEXPRESSIONS must be specified in Main.h.
long ExtObject::ReturnUndefinedExpression(CString& expName, LPVAL theParams, ExpReturn& ret)
{
	return ret = 0;
}

//////////////////////////////////////////////////////////////////////////////////
// Expressions
//////////////////////////////////////////////////////////////////////////////////
static int clamp(int x, int min, int max)
{
	if(x > max)
		x = max;
	else if(x < min)
		x = min;
	return x;
}

long ExtObject::eGetMessages(LPVAL params, ExpReturn& ret)
{
	if(messages.IsEmpty())
		return ret.ReturnString(pRuntime, "");

	int start = clamp(params[0].GetInt() - 1, 0, messages.GetUpperBound());
	int end = clamp(params[1].GetInt() - 1, 0, messages.GetUpperBound());

	CString result;
	if(start < end) {
		for(int i = start; i <= end; ++i) {
			result = result + messages[i] + "\n";
		}
	} else {
		for(int i = start; i >= end; --i) {
			result = + result + messages[i] + "\n";
		}
	}
	return ret.ReturnString(pRuntime, result);
}

long ExtObject::eCount(LPVAL params, ExpReturn &ret)
{
	return ret = messages.GetCount();
}