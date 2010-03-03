// Include StdAfx
#include "StdAfx.h"
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/foreach.hpp>

//////////////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////////////

/*long ExtObject::aMyAction(LPVAL params)
{
	// Get the example parameter
	int param = params[0].GetInt();

	// Do nothing
	return 0;
}*/


long ExtObject::aSave( LPVAL params )
{
	std::ofstream ofs(params[0].GetString());
	boost::archive::text_oarchive oa(ofs);
	oa & sectors;
	oa & missions;
	oa & playerInventory;
	return 0;
}


long ExtObject::aLoad( LPVAL params )
{
	std::ifstream ifs(params[0].GetString());
	boost::archive::text_iarchive ia(ifs);
	ia & sectors;
	ia & missions;
	ia & playerInventory;
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
	int idx = params[0].GetInt() - 1;
	if(idx < 0 || idx > playerInventory.size())
		return 0;

	try {
		playerInventory.erase(playerInventory.begin() + idx);
	}
	catch (out_of_range oor) {
		RaiseConstructError("Out of range attempt");
	}
	return 0;
}
