// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Conditions
//////////////////////////////////////////////////////////////////////////////////

/*long ExtObject::cMyCondition(LPVAL params)
{
	// Always run
	return true;
}*/


long ExtObject::cErrorOccurred( LPVAL params )
{
	if(unprocessedErrors) {
		unprocessedErrors = false;
		return true;
	}

	return false;
}
