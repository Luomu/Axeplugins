#include "StdAfx.h"
#include "InventoryItem.h"

InventoryItem::InventoryItem() :
	_id(-1),
	_name("Nothing"),
	_value(0),
	_location(-1)
{

}

InventoryItem::InventoryItem(const CString& name) :
	_id(-1),
	_name(name),
	_value(100),
	_location(-1)
{

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