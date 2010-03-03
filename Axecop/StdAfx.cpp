// Include StdAfx.h
#include "StdAfx.h"
#include <fstream>
#include <boost/lexical_cast.hpp>

void EndProperties(int iMode, CVirtualPropItem* item, MicroEdittime* pm)
{
	if (iMode == MODE_INIT) {
		ASSIGN_CSTRING(item->Description, "");
		ASSIGN_CSTRING(item->Label, "");
		ASSIGN_CSTRING(item->Text, "");
		item->Type = -1;	// end
		pm->Proc(item);		// post end to property vector
	}
}

double axeutils::random(double low, double high)
{
	return tr1::uniform_real<double>(low, high)(mtwister);
}

CString axeutils::randomLine(const CString& filename)
{
	string ret = "Undefined";
	string line;
	int i = 0;
	std::ifstream file(filename);
	while(getline(file, line)) {
		++i;
		if(axeutils::random(0, i) < 1)
			ret = line;
	}
	return ret.c_str();
}