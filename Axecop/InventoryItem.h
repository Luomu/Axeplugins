#ifndef InventoryItem_h__
#define InventoryItem_h__

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class InventoryItem
{
	friend class Inventory;
public:
	InventoryItem();
	InventoryItem(const CString&);
	CString toString() const;
	int id() { return _id; }
	int location() { return _location; }
	void setLocation(const int loc) { _location = loc; }
private:
	friend class boost::serialization::access;
	int _id;
	std::string _name;
	int _value;
	int _location; //storage, backpack, slot1, slot2...
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & _id;
		ar & _name;
		ar & _value;
		ar & _location;
	}
};
#endif // InventoryItem_h__