#include "StdAfx.h"
#include "Sector.h"

Sector::Sector(int newid) :
	_id(newid),
	name(axeutils::randomLine("data\\sectornames.txt")),
	capability(static_cast<int>(axeutils::random(1,6))),
	_difficulty(static_cast<int>(axeutils::random(1,6))),
	environment(static_cast<float>(axeutils::random(1,5))),
	enemies(static_cast<float>(axeutils::random(1,5)))
{}

Sector::Sector() :
	_id(-1),
	name("Undefined"),
	capability(0),
	_difficulty(0),
	environment(0)
{

}

CString Sector::toString()
{
	CString str;
	str.Format(_T("%s|%d|%d"), name.c_str(), capability, _difficulty);
	return str;
}