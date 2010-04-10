#include "StdAfx.h"
#include "InventoryItem.h"

#include <boost/lexical_cast.hpp>

InventoryItem::InventoryItem() :
	_id(-1),
	_name("Nothing"),
	_value(0),
	_location(-1),
	_appearance(0),
	_colour(16777215)
{

}

InventoryItem::InventoryItem(const CString& name) :
	_id(-1),
	_name(name),
	_value(100),
	_location(-1),
	_appearance(1),
	_colour(16777215)
{

}

InventoryItem::InventoryItem(std::map<std::string, std::string>& parms) :
	_id(-1),
	_location(-1),
	_value(0),
	_appearance(1),
	_colour(255)
{
	using boost::lexical_cast;

	if(parms["name"].empty())
		throw Axception("No name specified in item file!");
	_name = parms["name"];
	if(!parms["value"].empty())
		_value = lexical_cast<int>(parms["value"]);
	if(!parms["colour"].empty())
		_colour = lexical_cast<int>(parms["colour"]);
	if(!parms["appearance"].empty())
		_appearance = lexical_cast<int>(parms["appearance"]);
}

//id name location
CString InventoryItem::toString() const
{
	if(_id == -1)
		throw Axception("Item ID shouldn't be -1");
	CString str;
	str.Format("%d|%s|%d", _id, _name.c_str(), _location);
	return str;
}

void InventoryItem::setName(const std::string& newname)
{
	_name = newname;
}

void InventoryItem::setName(const ATL::CString& newname)
{
	_name = newname;
}

void InventoryItem::setValue(const int newvalue)
{
	_value = newvalue;
}

void InventoryItem::setAppearance(const int newa)
{
	_appearance = newa;
}

void InventoryItem::setColour(const int newc)
{
	_colour = newc;
}