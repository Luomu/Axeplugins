#include "StdAfx.h"
#include "Mission.h"


Mission::Mission() :
	sectorId(-1),
	cost(0)
{
}

Mission::Mission(int sector) :
	sectorId(sector),
	cost(100)
{
}

CString Mission::toString() const
{
	CString str;
	str.Format("%d|%d", sectorId, cost);
	return str;
}

int const Mission::intprop(const std::string& propname)
{
	return boost::get<int>(properties[propname]);
}