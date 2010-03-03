#include "StdAfx.h"
#include "Sector.h"

Sector::Sector(int newid) :
	_id(newid),
	name(axeutils::randomLine("data\\sectornames.txt")),
	capability(static_cast<int>(axeutils::random(1,6))),
	difficulty(static_cast<int>(axeutils::random(1,6)))
{}

Sector::Sector() :
	_id(-1),
	name("Undefined"),
	capability(0),
	difficulty(0)
{

}

CString Sector::toString()
{
	CString str;
	str.Format(_T("%s|%d|%d"), name.c_str(), capability, difficulty);
	return str;
}