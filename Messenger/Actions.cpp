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

long ExtObject::aLoad(LPVAL params)
{
	CString filename = params[0].GetString();
	CStdioFile file;

	if(!file.Open(filename, CFile::modeRead))
		return 0;

	CString buffer;
	messages.RemoveAll();
	while(file.ReadString(buffer)) {
		messages.Add(buffer);
	}
	file.Close();
	newUpdates = true;
	return 0;
}

long ExtObject::aSave(LPVAL params)
{
	if(messages.IsEmpty())
		return 0;

	CString filename = params[0].GetString();
	CStdioFile file;
	if(!file.Open(filename, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
		return 0;

	for(int i = 0; i <= messages.GetUpperBound(); ++i) {
		file.WriteString(messages[i]);
		if(i != messages.GetUpperBound())
			file.WriteString("\n");
	}
	file.Close();

	return 0;
}

long ExtObject::aClear(LPVAL params)
{
	messages.RemoveAll();
	newUpdates = true;
	return 0;
}