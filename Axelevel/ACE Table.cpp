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

	/////////////////////////////
	// Actions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	//ADDPARAM(PARAM_VALUE, "Example parameter", "Here is an example parameter.");
	//ADDACT("My action", "My category", "Example action (%0)", &ExtObject::aMyAction, "MyAction", 0);
	ADDPARAM(PARAM_STRING, "File name", "File to save to");
	ADDACT("Save room", "Rooms", "Save room to %0", &ExtObject::aSaveRoom, "SaveRoom", 0);
	ADDPARAM(PARAM_STRING, "File name", "File to load from");
	ADDACT("Load room", "Rooms", "Load room from %0", &ExtObject::aLoadRoom, "LoadRoom", 0);
	ADDACT("Clear room data", "Rooms", "Clear room data", &ExtObject::aClearData, "ClearRoomData", 0);
	ADDPARAM(PARAM_STRING, "Data string", "|-delimited string. See docs!");
	ADDACT("Add object from string", "Rooms", "Add %0 as string to objects", &ExtObject::aAddObjectString, "AddObjectString", 0);

	//Room saving
	ADDPARAM(PARAM_VALUE, "Type", "0=Sprite, 1=Tiled");
	ADDPARAM(PARAM_STRING, "Name", "Object name");
	ADDPARAM(PARAM_VALUE, "X", "X position");
	ADDPARAM(PARAM_VALUE, "Y", "Y position");
	ADDPARAM(PARAM_VALUE, "Angle", "Rotation");
	ADDPARAM(PARAM_VALUE, "Width", "Width");
	ADDPARAM(PARAM_VALUE, "Height", "Height");
	ADDPARAM(PARAM_STRING, "XData", "|-delimited string for custom data");
	ADDACT("Add object", "Rooms", "Add %1 to objects", &ExtObject::aAddObject, "AddObject", 0);

	ADDPARAM(PARAM_VALUE, "X offset", "Room object coordinates X offset");
	ADDPARAM(PARAM_VALUE, "Y offset", "Room object coordinates Y offset");
	ADDPARAM(PARAM_VALUE, "Angle", "Room object rotation (0/90/180/270)");
	ADDACT("Set offset", "Rooms", "Set offset to %0,%1 at %2 degrees", &ExtObject::aSetOffset, "SetOffset", 0);

	/////////////////////////////
	// Expressions
	// ADDEXP(List name, Category, Display string, Function address, Flags)
	//ADDEXP("My expression", "My category", "MyExpression", &ExtObject::eMyExpression, RETURN_INTEGER);
	ADDEXP("Object count", "Rooms", "ObjectCount", &ExtObject::eObjectCount, RETURN_VALUE);
	ADDPARAM(PARAM_VALUE, "Object number", "1-n");
	ADDEXP("Object", "Rooms", "Object", &ExtObject::eObject, RETURN_STRING);

	ADDPARAM(PARAM_VALUE, "Object number", "1-n");
	ADDPARAM(PARAM_VALUE, "Value index", "1-6");
	ADDEXP("Object value", "Rooms", "ObjectValue", &ExtObject::eObjectValue, RETURN_VALUE);
	ADDPARAM(PARAM_VALUE, "Object number", "1-n");
	ADDEXP("Object name", "Rooms", "ObjectName", &ExtObject::eObjectName, RETURN_STRING);
	ADDPARAM(PARAM_VALUE, "Object number", "1-n");
	ADDEXP("Object XData", "Rooms", "ObjectXData", &ExtObject::eObjectXData, RETURN_STRING);

	// This line includes your common ACEs as specified in Main.h
#include "..\Common\CommonAceTable.hpp"
}


