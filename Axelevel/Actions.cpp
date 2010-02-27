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
	std::ofstream ofs(params[0].GetString());
	boost::archive::text_oarchive oa(ofs);
	oa << roomObjects;
	return 0;
}

long ExtObject::aLoadRoom( LPVAL params )
{
	std::ifstream ifs(params[0].GetString());
	boost::archive::text_iarchive ia(ifs);
	ia >> roomObjects;
	return 0;
}

long ExtObject::aAddObject( LPVAL params )
{
	roomObjects.push_back( std::string(params[0].GetString()) );
	return 0;
}

long ExtObject::aClearData( LPVAL params )
{
	roomObjects.clear();
	return 0;
}