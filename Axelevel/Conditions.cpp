// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Conditions
//////////////////////////////////////////////////////////////////////////////////

long ExtObject::cErrorOccurred( LPVAL params )
{
	if(unprocessedErrors) {
		unprocessedErrors = false;
		return true;
	}

	return false;
}
