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