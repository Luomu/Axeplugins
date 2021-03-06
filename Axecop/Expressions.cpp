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

/*long ExtObject::eMyExpression(LPVAL params, ExpReturn& ret)
{
	// Return 0 using ExpReturn's operator=
	// Use ret.ReturnString() for strings.
	return ret = 0;
}*/


long ExtObject::eNumSectors( LPVAL params, ExpReturn& ret )
{
	return ret = sectors.size();
}


long ExtObject::eSectorString( LPVAL params, ExpReturn& ret )
{
	int idx = params[0].GetInt() - 1;
	if(sectors.size() == 0 || idx < 0 || idx > sectors.size())
		return ret.ReturnString(pRuntime, "No sectors");
	Sector& sec = sectors.at(idx);
	return ret.ReturnString(pRuntime, sec.toString());
}

long ExtObject::eNumMissions( LPVAL params, ExpReturn& ret )
{
	return ret = missions.size();
}


long ExtObject::eMissionString( LPVAL params, ExpReturn& ret )
{
	int id = params[0].GetInt() - 1;
	if(missions.size() == 0 || id < 0 || id > sectors.size())
		return ret.ReturnString(pRuntime, "No missions");
	Mission& mission = missions.at(id);
	return ret.ReturnString(pRuntime, mission.toString());
}

long ExtObject::eDropCost( LPVAL params, ExpReturn& ret )
{
	return ret = missions.at(params[0].GetInt() -1).dropCost();
}


long ExtObject::eRandomLine( LPVAL params, ExpReturn& ret )
{
	return ret.ReturnString(pRuntime, axeutils::randomLine(params[0].GetString()));
}


long ExtObject::eItemCount( LPVAL params, ExpReturn& ret )
{
	return ret = playerInventory.size();
}


long ExtObject::eInventoryItemString( LPVAL params, ExpReturn& ret )
{
	return ret.ReturnString(pRuntime,
		playerInventory.itemString(params[0].GetInt()));
}


long ExtObject::eErrorString( LPVAL params, ExpReturn& ret )
{
	return ret.ReturnString(pRuntime, errorString);
}


long ExtObject::eInventoryItemValue( LPVAL params, ExpReturn& ret )
{
	InventoryItem* itm = 0;
	if(params[0].GetInt() == 0)
		itm = &*currentItem;
	else
		itm = playerInventory[params[0].GetInt()];

	if(itm == 0)
		return ret = 0;

	CString pn = params[1].GetString();

	if(pn == _T("name"))
		return ret.ReturnString(pRuntime, itm->name().c_str());
	else if(pn == _T("id"))
		return ret = itm->id();
	else if(pn == _T("value"))
		return ret = itm->value();
	else if(pn == _T("location"))
		return ret = itm->location();
	else if(pn == _T("description"))
		return ret.ReturnString(pRuntime, "No description");
	else if(pn == _T("type"))
		return ret = 0;
	else if(pn == _T("condition"))
		return ret = 100;
	else if(pn == _T("appearance"))
		return ret = itm->appearance();
	else if(pn == _T("colour"))
		return ret = itm->colour();
	
	return ret = 0;
}

long ExtObject::eCurrentInventoryItem(LPVAL params, ExpReturn& ret)
{
	if(playerInventory.empty())
		return ret = 0;

	return ret = currentItem->id();
}

long ExtObject::eMissionValue(LPVAL params, ExpReturn &ret)
{
	int id = params[0].GetInt() - 1;
	CString pm = params[1].GetString();
	Mission* mission = 0;
	try {
		mission = &missions.at(id);

		if(pm == _T("sector"))
			return ret = mission->sector();
		else if(pm == _T("cost"))
			return ret = mission->dropCost();
		else
			return ret = mission->intprop(pm.GetBuffer());
	}
	catch (std::out_of_range oor) {
		RaiseConstructError("Mission ID out of range");
	}
	catch (Axception& ax) {
		RaiseConstructError(ax.what());
	}

	return ret = 0;
}

long ExtObject::eSectorProperty(LPVAL params, ExpReturn &ret)
{
	int id = params[0].GetInt() - 1;
	CString pm = params[1].GetString();
	Sector* sector = 0;
	try {
		sector = &sectors.at(id);

		if(pm == _T("name"))
			return ret.ReturnString(pRuntime, sector->sectorName().c_str());
		else if(pm == _T("difficulty"))
			return ret = sector->difficulty();
		else if(pm == _T("environment"))
			return ret = sector->environment;
		else if(pm == _T("enemies"))
			return ret = sector->enemies;
		else if(pm ==_T("visibility"))
			return ret = sector->visibility;
		else if(pm == _T("capability"))
			return ret = sector->capability;
		else
			throw Axception("Unknown mission property");
	}
	catch (std::out_of_range oor) {
		RaiseConstructError("No such sector");
	}
	catch (Axception& ax) {
		RaiseConstructError(ax.what());
	}

	return ret = 0;
}