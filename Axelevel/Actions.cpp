// Include StdAfx
#include "StdAfx.h"
#include <fstream>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

//////////////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////////////
long ExtObject::aSaveRoom( LPVAL params )
{
	try {
		std::ofstream ofs(params[0].GetString());
		boost::archive::text_oarchive oa(ofs);
		oa << roomObjects;
	} catch(...) {
		RaiseConstructError("Error trying to save " + params[0].GetString());
		
	}
	return 0;
}

long ExtObject::aLoadRoom( LPVAL params )
{
	try {
		std::ifstream ifs(params[0].GetString());
		boost::archive::text_iarchive ia(ifs);
		ia >> roomObjects;
	} catch(...) {
		RaiseConstructError("Error trying to load " + params[0].GetString());
	}
	return 0;
}

long ExtObject::aAddObjectString( LPVAL params )
{
	//roomObjects.push_back( std::string(params[0].GetString()) );
	return 0;
}

long ExtObject::aClearData( LPVAL params )
{
	roomObjects.clear();
	return 0;
}

//params:
//type
//name
//xpos
//ypos
//angle
//width
//height
//xdata
long ExtObject::aAddObject( LPVAL params )
{
	roomObjects.push_back(RoomObject());
	RoomObject& ro = roomObjects.back();
	ro.type = params[0].GetInt();
	ro.name = std::string(params[1].GetString());
	ro.xpos = params[2].GetInt();
	ro.ypos = params[3].GetInt();
	ro.angle = params[4].GetInt();
	ro.width = params[5].GetInt();
	ro.height = params[6].GetInt();
	ro.xdata = std::string("");
	return 0;
}


long ExtObject::aSetOffset( LPVAL params )
{
	offsetX = params[0].GetInt();
	offsetY = params[1].GetInt();
	roomAngle = params[2].GetInt();
	return 0;
}

long ExtObject::aSaveLevel( LPVAL params )
{
	return 0;
}

long ExtObject::aLoadLevel( LPVAL params )
{
	return 0;
}

long ExtObject::aClearLevelData( LPVAL params )
{
	level.clear();
	return 0;
}

long ExtObject::aAddRoom( LPVAL params )
{
	return 0;
}

// Load and create a room at position
long ExtObject::aLoadAndCreateRoom( LPVAL params )
{
	int xoff = params[1].GetInt();
	int yoff = params[2].GetInt();
	int rangle = params[3].GetInt();

	try {
		std::ifstream ifs(params[0].GetString());
		boost::archive::text_iarchive ia(ifs);
		ia >> roomObjects;
	}catch(...) {
		RaiseConstructError("Error trying to load " + params[0].GetString());
		return 0;
	}
	/*CRunObjType* ot = pRuntime->GetTypeFromName("block_wall");
	CRunLayer* l = pRuntime->GetLayer(pLayout, "Common");
	CRunObject* o = pRuntime->CreateObject(ot, l->number, pLayout);

	o->info.x = 40;
	o->info.y = 50;
	o->info.angle = 33;
	pRuntime->UpdateBoundingBox(o);*/
	try {
		if(roomObjects.empty())
			throw "No room loaded.";
		
		//go through objects
		vector<RoomObject>::iterator ro;
		ro = roomObjects.begin();
		while(ro != roomObjects.end()) {
			CRunObjType* ot = pRuntime->GetTypeFromName(ro->name.c_str());
			if(ot == NULL) throw "No matching object type.";

			CRunLayer* l = pRuntime->GetLayer(pLayout, "Common");
			if(l == NULL) throw "No layer Common found.";

			CRunObject* o = pRuntime->CreateObject(ot, l->number, pLayout);
			if(o == NULL) throw "Error while creating object.";

			o->info.x = ro->xpos + xoff;
			o->info.y = ro->ypos + yoff;
			if(ro->width > 0 && ro->height > 0) {
				o->info.w = ro->width;
				o->info.h = ro->height;
			}
			pRuntime->UpdateBoundingBox(o);

			++ro;
		}
	} catch(char* str) {
		RaiseConstructError(str);
	} catch(...) {
		RaiseConstructError("Unknown error while attempting to recreate objects.");
	}
	return 0;
}