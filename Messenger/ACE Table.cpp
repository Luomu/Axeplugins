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
	ADDCND("Updated", "Messages", "%o Updated", &ExtObject::cUpdated, "Updated", 0);

	/////////////////////////////
	// Actions
	// Format:
	// ADDCND(List name, Category, Display string, Function address, Script name, Flags)
	//ADDPARAM(PARAM_VALUE, "Example parameter", "Here is an example parameter.");
	//ADDACT("My action", "My category", "Example action (%0)", &ExtObject::aMyAction, "MyAction", 0);
	ADDPARAM(PARAM_STRING, "Message", "Message to add");
	//ADDPARAM(PARAM_STRING, "Tag", "Tag to categorize the message");
	ADDACT("Add", "Messages", "Add %0", &ExtObject::aAddLine, "Add", 0);

	ADDPARAM(PARAM_STRING, "Message", "Message to add");
	ADDPARAM(PARAM_STRING, "Tag", "Tag to categorize the message");
	ADDACT("Add tagged", "Messages", "Add %0 (%1)", &ExtObject::aAddTaggedLine, "AddTagged", 0);

	ADDPARAM(PARAM_STRING, "File", "File to save to");
	ADDACT("Save to file", "Data", "Save to %0", &ExtObject::aSave, "Save", 0);
	ADDPARAM(PARAM_STRING, "File", "File to load from");
	ADDACT("Load from file", "Data", "Load from %0", &ExtObject::aLoad, "Load", 0);
	ADDPARAM(PARAM_STRING, "File", "File to save to");
	ADDACT("Export without tags", "Data", "Export to %0", &ExtObject::aSave, "Export", 0);
	ADDPARAM(PARAM_STRING, "File", "File to load from");
	ADDACT("Import without tags", "Data", "Import from %0", &ExtObject::aLoad, "Import", 0);

	ADDACT("Clear", "Data", "Clear", &ExtObject::aClear, "Clear", 0);

	/////////////////////////////
	// Expressions
	// ADDEXP(List name, Category, Display string, Function address, Flags)
	//ADDEXP("My expression", "My category", "MyExpression", &ExtObject::eMyExpression, RETURN_INTEGER);
	// This line includes your common ACEs as specified in Main.h
	ADDPARAM(PARAM_VALUE, "Start", "First line to retrieve");
	ADDPARAM(PARAM_VALUE, "End", "Last line to retrieve");
	//ADDPARAM(PARAM_STRING, "Tags", "Only retrieve messages matching tags");
	ADDEXP("Get messages", "Messages", "GetMessages", &ExtObject::eGetMessages, RETURN_STRING);

	ADDPARAM(PARAM_VALUE, "Start", "First line to retrieve");
	ADDPARAM(PARAM_VALUE, "End", "Last line to retrieve");
	ADDPARAM(PARAM_STRING, "Tags", "Only retrieve messages matching tags");
	ADDEXP("Get messages by tags", "Messages", "GetMessagesByTags", &ExtObject::eGetMessagesByTags, RETURN_STRING);

	ADDEXP("Count", "Messages", "Count", &ExtObject::eCount, RETURN_VALUE);
#include "..\Common\CommonAceTable.hpp"
}


