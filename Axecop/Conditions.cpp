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

long ExtObject::cForEachItem(LPVAL params)
{
	if(playerInventory.empty())
		return false;

	EventParametersInfo2 epi;
	pRuntime->GetCurrentEventPtrs(epi);


	currentItem = playerInventory.begin();
	while(currentItem != playerInventory.end()) {
		pRuntime->NewSOLCopy();

		if(epi.pCnds && !pRuntime->RunConditions(epi.pCnds)) {
			pRuntime->RestoreSOL();
			break;
		}

		if(epi.pActs)
			pRuntime->RunActions(epi.pActs);

		if(epi.pSubEvents)
			pRuntime->RunSubEvents(epi.pSubEvents);

		pRuntime->RestoreSOL();
		currentItem++;
	}

	return false;
}