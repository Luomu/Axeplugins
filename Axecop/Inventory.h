#ifndef Inventory_h__
#define Inventory_h__

#include <vector>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "InventoryItem.h"

//typedef std::string InventoryItem;

class Inventory
{
public:
	Inventory() : _idcounter(1) {}
	~Inventory() {}

	typedef std::vector<InventoryItem>::const_iterator const_iterator;
	typedef std::vector<InventoryItem>::iterator iterator;
	const_iterator begin() const {
		return(_items.begin());
	}

	iterator begin() {
		return(_items.begin());
	}

	const_iterator end() const {
		return(_items.end());
	}

	iterator end() {
		return(_items.end());
	}

	bool empty() { return _items.empty(); }

	InventoryItem* operator[](const int& k) {
		for(int i = 0; i < _items.size(); ++i) {
			if(_items.at(i).id() == k)
				return &_items.at(i);
		}
		return 0;
	}

	InventoryItem* lastItem();

	int size() const {
		return _items.size();
	}

	void add(InventoryItem& itm) {
		itm._id = _idcounter;
		++_idcounter;
		itm.setLocation(0);
		_items.push_back(itm);
	}

	iterator erase(const_iterator whereit);

	CString itemString(int index) const {
		try {
			return _items.at(index - 1).toString();
		}
		catch(std::out_of_range oor) {
			return oor.what();
		}
	}

	void clear();
private:
	friend class boost::serialization::access;
	std::vector<InventoryItem> _items;
	int _idcounter;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & _items;
		ar & _idcounter;
	}
};
#endif // Inventory_h__