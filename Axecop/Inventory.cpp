#include "StdAfx.h"
#include "Inventory.h"

Inventory::iterator Inventory::erase( const_iterator whereit )
{
	return _items.erase(whereit);
}

InventoryItem* Inventory::lastItem()
{
	return &_items.at(_items.size() - 1);
}