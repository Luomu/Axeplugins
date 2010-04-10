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
	InventoryItem(std::map<std::string, std::string>&);
	CString toString() const;
	int id() { return _id; }
	int location() { return _location; }
	void setLocation(const int loc) { _location = loc; }
	const std::string& name() { return _name; }
	int value() const { return _value; }
	void setName(const std::string&);
	void setName(const ATL::CString&);
	void setValue(const int);
	int appearance() const { return _appearance; }
	void setAppearance(const int);
	int colour() const { return _colour; }
	void setColour(const int);
private:
	friend class boost::serialization::access;
	int _id;
	std::string _name;
	int _value;
	int _location; //storage, backpack, slot1, slot2...
	int _appearance; //frame number, basically
	int _colour; // 0 = black 2^32 = white
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & _id;
		ar & _name;
		ar & _value;
		ar & _location;
		ar & _appearance;
		ar & _colour;
	}
};
#endif // InventoryItem_h__