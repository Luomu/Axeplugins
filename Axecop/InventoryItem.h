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
private:
	friend class boost::serialization::access;
	int _id;
	std::string _name;
	int _value;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & _id;
		ar & _name;
		ar & _value;
	}
};
#endif // InventoryItem_h__