#include "StdAfx.h"
#include "Inventory.h"

#include <fstream>
#include <sstream>

#include <boost/algorithm/string.hpp>

Inventory::iterator Inventory::erase( const_iterator whereit )
{
	return _items.erase(whereit);
}

void Inventory::clear()
{
	_items.clear();
}

InventoryItem* Inventory::lastItem()
{
	return &_items.at(_items.size() - 1);
}

void Inventory::loadItem(const std::string& fname)
{
	//boost config_file_iterator keeps crashing so doing this the old way
	std::ifstream config(fname.c_str());

	if(!config) {
		std::stringstream ss;
		ss << fname << " not found";
		throw Axception(ss.str());
	}

	std::string buffer;
	std::map<std::string, std::string> parameters;
	parameters["name"] = "Sausage";
	std::vector<std::string> results;
	while(!config.eof()) {
		getline(config, buffer);
		boost::split(results, buffer, boost::is_any_of("="));
		parameters[results[0]] = results[1];
	}
	config.close();
	add(InventoryItem(parameters));
}