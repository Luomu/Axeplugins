#ifndef MESSAGE_H
#define MESSAGE_H

namespace Messenger {
	struct Message {
		CString text;
		CString tag;

		Message() :
			text(""),
			tag("") {}

		Message(const CString& newtext, const CString& newtag) :
			text(newtext),
			tag(newtag) {

			}
	};
}

#endif