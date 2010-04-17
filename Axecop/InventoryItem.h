#ifndef InventoryItem_h__
#define InventoryItem_h__

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

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
		using boost::serialization::make_nvp;
		ar & make_nvp("id", _id);
		ar & make_nvp("name", _name);
		ar & make_nvp("value", _value);
		ar & make_nvp("location", _location);
		ar & make_nvp("appearance", _appearance);
		ar & make_nvp("colour", _colour);
	}
};
#endif // InventoryItem_h__