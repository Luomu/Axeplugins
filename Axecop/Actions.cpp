// Include StdAfx
#include "StdAfx.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/foreach.hpp>

//////////////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////////////
long ExtObject::aSave( LPVAL params )
{
	using boost::serialization::make_nvp;
	std::ofstream ofs(params[0].GetString());
	//boost::archive::text_oarchive oa(ofs);
	boost::archive::xml_oarchive oa(ofs);
	oa << make_nvp("sectors", sectors);
	oa << make_nvp("missions", missions);
	oa << make_nvp("inventory", playerInventory);
	return 0;
}


long ExtObject::aLoad( LPVAL params )
{
	using boost::serialization::make_nvp;
	std::ifstream ifs(params[0].GetString());
	//boost::archive::text_iarchive ia(ifs);
	boost::archive::xml_iarchive ia(ifs);
	ia >> make_nvp("sectors", sectors);
	ia >> make_nvp("missions", missions);
	ia >> make_nvp("inventory", playerInventory);
	return 0;
}


long ExtObject::aGenerateSectors( LPVAL params )
{
	missions.clear();
	sectors.clear();

	int numsectors = params[0].GetInt() + 1;

	for(int i = 1; i <= numsectors; ++i)
	{
		sectors.push_back(Sector(i));

		Sector& sec = sectors.back();
	}

	return 0;
}

long ExtObject::aGenerateMissions( LPVAL params )
{
	int howmany = params[0].GetInt();
	missions.clear();

	std::vector<int> availSectors;
	BOOST_FOREACH(const Sector& sec, sectors) {
		availSectors.push_back(sec.id());
	}

	if(availSectors.empty())
		return 0;

	while(howmany > 0) {
		int secid = axeutils::random(0, availSectors.size());
		availSectors.erase(availSectors.begin() + secid);
		missions.push_back(Mission(secid));
		Mission& newmiss = missions.back();
		newmiss.properties["visibility"] = axeutils::random(1, 5);
		newmiss.properties["enemylevel"] = axeutils::random(1, 5);
		newmiss.properties["environment"] = axeutils::random(1, 5);
		--howmany;
	}

	if(missions.empty())
		RaiseConstructError("Something wrong! No mozzions!");

	return 0;
}


long ExtObject::aAddItem(LPVAL params)
{
	playerInventory.add(InventoryItem(params[0].GetString()));
	return 0;
}


long ExtObject::aRemoveItem( LPVAL params)
{
	int idx = params[0].GetInt();

	int itemsRemoved = 0;

	try {
		vector<InventoryItem>::iterator it;
		it = playerInventory.begin();
		while(it != playerInventory.end()) {
			if(it->id() == idx) {
				playerInventory.erase(it);
				++itemsRemoved;
				break;
			}
			++it;
		}
		if(itemsRemoved == 0)
			throw Axception("Nothing was removed");
		if(itemsRemoved > 1)
			throw Axception("More than one item were removed");
	}
	catch (out_of_range oor) {
		RaiseConstructError("Out of range attempt");
	}
	catch(Axception& ae)
	{
		RaiseConstructError(ae.what());
	}
	catch(...) {
		RaiseConstructError("Unknown error while removing item");
	}
	return 0;
}


long ExtObject::aEquipItem( LPVAL params )
{
	int itmToEquip = params[0].GetInt();
	int locationId = params[1].GetInt();

	int success = 0;

	try
	{
		if(locationId < 0)
			throw Axception("No such location to equip in");
		//find out if location is already used
		vector<InventoryItem>::iterator it;
		it = playerInventory.begin();
		while(it != playerInventory.end()) {
			if(it->location() == locationId)
				it->setLocation(0);
			if(it->id() == itmToEquip) {
				it->setLocation(locationId);
				success++;
			}
			++it;
		}
		if(success == 0)
			throw Axception("No item was equipped");
		if(success > 1)
			throw Axception("Item was equipped more than once, what");
	}
	catch(Axception& ae)
	{
		RaiseConstructError(ae.what());
	}
	catch(...)
	{
		RaiseConstructError("Unknown error while equipping item");
	}

	return 0;
}

long ExtObject::aSetInventoryItemValue(LPVAL params)
{
	InventoryItem* itm;
	if(params[0].GetInt() == 0)
		itm = playerInventory.lastItem();
	else
		itm = playerInventory[params[0].GetInt()];

	if(itm == 0)
		return 0;

	CString pn = params[1].GetString();

	if(pn == _T("name"))
		itm->setName(params[2].GetString());
	else if(pn == _T("value"))
		itm->setValue(params[2].GetInt());
	else if(pn == _T("appearance"))
		itm->setAppearance(params[2].GetInt());
	else if(pn == _T("colour"))
		itm->setColour(params[2].GetInt());
	else if(pn == _T("location"))
		itm->setLocation(params[2].GetInt());
	else
		RaiseConstructError("No such item property.");

	return 0;
}

long ExtObject::aClearData(LPVAL params)
{
	missions.clear();
	sectors.clear();
	playerInventory.clear();
	return 0;
}

// Load item from an .item file
long ExtObject::aLoadItem(LPVAL params)
{
	try {
		playerInventory.loadItem(std::string(params[0].GetString()));
		playerInventory.lastItem()->setLocation(params[1].GetInt());
	}
	catch(Axception& ae) {
		RaiseConstructError(ae.what());
	}
	catch(std::exception& se) {
		RaiseConstructError(se.what());
	}

	return 0;
}