#ifndef Sector_h__
#define Sector_h__

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Sector
{
public:
	Sector();
	Sector(int newid);
	CString toString();
	int id() const { return _id; }
	std::string sectorName() const { return name; }
	int difficulty() const { return _difficulty; }
private:
	friend class boost::serialization::access;
	int _id;
	std::string name;
	int capability;
	int _difficulty;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & _id;
		ar & name;
		ar & capability;
		ar & _difficulty;
	}
};


#endif // Sector_h__