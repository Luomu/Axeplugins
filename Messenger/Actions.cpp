// Include StdAfx
#include "StdAfx.h"

//////////////////////////////////////////////////////////////////////////////////
// Actions
//////////////////////////////////////////////////////////////////////////////////
long ExtObject::aAddLine(LPVAL params)
{
	messages.Add(params[0].GetString());
	newUpdates = true;
	return 0;
}

long ExtObject::aAddTaggedLine(LPVAL params)
{
	taggedMessages.Add(Messenger::Message(params[0].GetString(),
					   params[1].GetString()));
	newUpdates = true;
	return 0;
}

long ExtObject::aLoad(LPVAL params)
{
	CString filename = params[0].GetString();
	CStdioFile file;

	if(!file.Open(filename, CFile::modeRead))
		return 0;

	CString buffer;
	messages.RemoveAll();
	while(file.ReadString(buffer)) {
		taggedMessages.Add(Messenger::Message(buffer, ""));
	}
	file.Close();
	newUpdates = true;
	return 0;
}

// Save with tags intact
long ExtObject::aSave(LPVAL params)
{
	if(taggedMessages.IsEmpty())
		return 0;

	CString filename = params[0].GetString();
	CStdioFile file;
	if(!file.Open(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
		return 0;

	for(int i = 0; i <= taggedMessages.GetUpperBound(); ++i) {
		file.WriteString(taggedMessages[i].tag);
		file.WriteString("|");
		file.WriteString(taggedMessages[i].text);
		if(i != taggedMessages.GetUpperBound())
			file.WriteString("\n");
	}
	file.Close();

	return 0;
}

// Save without tags
long ExtObject::aExport(LPVAL params)
{
	if(taggedMessages.IsEmpty())
		return 0;

	CString filename = params[0].GetString();
	CStdioFile file;
	if(!file.Open(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
		return 0;

	for(int i = 0; i <= taggedMessages.GetUpperBound(); ++i) {
		file.WriteString(taggedMessages[i].text);
		if(i != taggedMessages.GetUpperBound())
			file.WriteString("\n");
	}
	file.Close();

	return 0;
}

long ExtObject::aClear(LPVAL params)
{
	taggedMessages.RemoveAll();
	newUpdates = true;
	return 0;
}