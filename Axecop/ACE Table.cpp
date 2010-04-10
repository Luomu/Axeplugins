// Include StdAfx
#include "StdAfx.h"

// Include any used common ACE definitions.
#ifdef RUN_ONLY
#include "..\Common\CommonAceDef.hpp"
#endif

//////////////////////////////////////////////////////////////////////////////////
// ACE table
//////////////////////////////////////////////////////////////////////////////////

void DefineACES(MicroAceTime* at)
{
	// Define your ACE tables here.
	// Use ADDPARAM before each ADDACT/ADDCND/ADDEXP to add parameters.
	// See the documentation for full details.

	// Note in the display string, %o is your object icon and %0-%9 make up parameters.
	// Note the script name should be a name suitable for the routine as if it were a member function in a
	// scripting language, eg. "Clear Stored Items" -> "ClearStoredItems"

	/////////////////////////////
	// Conditions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	//ADDCND("My condition", "My category", "%o My condition", &ExtObject::cMyCondition, "MyCondition", 0);
	ADDCND("For each item", "Player inventory", "%o For each item", &ExtObject::cForEachItem, "ForEachItem", SOL_MODIFIER);

	/////////////////////////////
	// Actions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	//ADDPARAM(PARAM_VALUE, "Example parameter", "Here is an example parameter.");
	//ADDACT("My action", "My category", "Example action (%0)", &ExtObject::aMyAction, "MyAction", 0);
	ADDPARAM(PARAM_STRING, "Filename", "File to save to.");
	ADDACT("Save", "Data", "Save to %0", &ExtObject::aSave, "Save", 0);
	ADDPARAM(PARAM_STRING, "Filename", "File to load from.");
	ADDACT("Load", "Data", "Load from %0", &ExtObject::aLoad, "Load", 0);

	ADDPARAM(PARAM_VALUE, "Count", "Number of sectors to create");
	ADDACT("Generate sectors", "Sectors", "Generate %0 sectors", &ExtObject::aGenerateSectors, "GenerateSectors", 0);
	ADDPARAM(PARAM_VALUE, "Count", "Max number of missions to create");
	ADDACT("Generate missions", "Missions", "Generate %0 missions", &ExtObject::aGenerateMissions, "GenerateMissions", 0);

	ADDPARAM(PARAM_STRING, "Item string", "|-delimited item structure");
	ADDACT("Add item", "Player inventory", "Add %0 to inventory", &ExtObject::aAddItem, "AddItem", 0);
	ADDPARAM(PARAM_VALUE, "Item ID", "Identifier of item to remove");
	ADDACT("Remove item", "Player inventory", "Remove item %0", &ExtObject::aRemoveItem, "RemoveItem", 0);

	ADDPARAM(PARAM_VALUE, "Item ID", "Item identifier");
	ADDPARAM(PARAM_VALUE, "Location ID", "0=Storage 1=Slot1 2=Slot2");
	ADDACT("Equip item", "Player inventory", "Equip item %0 in %1",
		&ExtObject::aEquipItem, "EquipItem", 0);

	ADDPARAM(PARAM_VALUE, "Item ID", "Inventory item identifier");
	ADDPARAM(PARAM_STRING, "Property name", "Item property name");
	ADDPARAM(PARAM_VALUE, "New value", "New value for the property");
	ADDACT("Set item property", "Player inventory", "Set %1 in item %0 to %2",
		&ExtObject::aSetInventoryItemValue, "SetItemProperty", 0);

	ADDACT("Clear data", "Data", "Clear data", &ExtObject::aClearData, "ClearData", 0);

	ADDCND("Error occurred", "Utils", "%o Error occurred", &ExtObject::cErrorOccurred, "ErrorOccurred", 0);

	/////////////////////////////
	// Expressions
	// ADDEXP(List name, Category, Display string, Function address, Flags)
	//ADDEXP("My expression", "My category", "MyExpression", &ExtObject::eMyExpression, RETURN_INTEGER);
	ADDEXP("Number of sectors", "Sectors", "NumSectors", &ExtObject::eNumSectors, RETURN_INTEGER);
	ADDPARAM(PARAM_VALUE, "Sector number", "Sector number");
	ADDEXP("Sector string", "Sectors", "SectorString", &ExtObject::eSectorString, RETURN_STRING);
	
	ADDEXP("Number of missions", "Missions", "NumMissions", &ExtObject::eNumMissions, RETURN_INTEGER);
	ADDPARAM(PARAM_VALUE, "Mission number", "1-n");
	ADDEXP("Mission string", "Missions", "MissionString", &ExtObject::eMissionString, RETURN_STRING);
	ADDPARAM(PARAM_VALUE, "Mission number", "1-n");
	ADDEXP("Drop cost", "Missions", "DropCost", &ExtObject::eDropCost, RETURN_INTEGER);

	ADDPARAM(PARAM_STRING, "File name", "File to read lines from");
	ADDEXP("Get random line from file", "Utils", "RandomLine", &ExtObject::eRandomLine, RETURN_STRING);
	ADDEXP("Get last error string", "Utils", "GetLastErrorString", &ExtObject::eErrorString, RETURN_STRING);

	ADDEXP("Number of items", "Player inventory", "NumberOfItems", &ExtObject::eItemCount, RETURN_VALUE);

	ADDPARAM(PARAM_VALUE, "Item index", "Item to return as | delimited string (1-n)");
	ADDEXP("Item string", "Player inventory", "InventoryItemString", &ExtObject::eInventoryItemString, RETURN_STRING);

	ADDPARAM(PARAM_VALUE, "Item ID", "Inventory item identifier");
	ADDPARAM(PARAM_STRING, "Property name", "Item property name");
	ADDEXP("Item property", "Player inventory", "ItemProperty", &ExtObject::eInventoryItemValue, 0);

	ADDEXP("Current item", "Player inventory", "CurrItem", &ExtObject::eCurrentInventoryItem, SOL_MODIFIER);

	ADDPARAM(PARAM_VALUE, "Mission ID", "Mission ID (number)");
	ADDPARAM(PARAM_STRING, "Property name", "Mission property name");
	ADDEXP("Mission property", "Missions", "MissionProperty", &ExtObject::eMissionValue, 0);

	ADDPARAM(PARAM_VALUE, "Sector ID", "Sector ID (number)");
	ADDPARAM(PARAM_STRING, "Property name", "Sector property name");
	ADDEXP("Sector property", "Sectors", "SectorProperty", &ExtObject::eSectorProperty, 0);

	ADDPARAM(PARAM_STRING, "File name", ".item file to load, with full path");
	ADDPARAM(PARAM_VALUE, "Location", "Location identifier for the new item");
	ADDACT("Load item", "Player inventory", "Load item %0 into %1", &ExtObject::aLoadItem, "LoadItem", 0);

	// This line includes your common ACEs as specified in Main.h
#include "..\Common\CommonAceTable.hpp"
}


