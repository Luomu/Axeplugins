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

long ExtObject::eObjectCount( LPVAL params, ExpReturn& ret )
{
	return ret = roomObjects.size();
}

long ExtObject::eObject( LPVAL params, ExpReturn& ret )
{
	int idx = params[0].GetInt() - 1;
	//CString str(roomObjects.at(idx).c_str());
	CString str("undefined");
	return ret.ReturnString(pRuntime, str);
}


long ExtObject::eObjectValue( LPVAL params, ExpReturn& ret )
{
	int idx = params[0].GetInt() - 1;
	RoomObject& ro = roomObjects.at(idx);
	switch(params[1].GetInt()) {
	case 1:
		return ret = ro.type;
	case 2:
		return ret = ro.xpos + offsetX;
	case 3:
		return ret = ro.ypos + offsetY;
	case 4:
		return ret = ro.angle;
	case 5:
		return ret = ro.width;
	case 6:
		return ret = ro.height;
	default:
		return ret = 0;
	}
}

long ExtObject::eObjectName( LPVAL params, ExpReturn& ret )
{
	RoomObject& ro = roomObjects.at(params[0].GetInt() - 1);
	return ret.ReturnString(pRuntime, ro.name.c_str());
}

long ExtObject::eObjectXData( LPVAL params, ExpReturn& ret )
{
	RoomObject& ro = roomObjects.at(params[0].GetInt() - 1);
	return ret.ReturnString(pRuntime, ro.xdata.c_str());
}

long ExtObject::eErrorString( LPVAL params, ExpReturn& ret )
{
	return ret.ReturnString(pRuntime, errorString);
}