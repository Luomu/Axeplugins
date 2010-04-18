#ifndef Sector_h__
#define Sector_h__

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

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
	friend class ExtObject;
	int _id;
	std::string name;
	int capability;
	int _difficulty;
	float environment;
	float visibility;
	float enemies;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		using boost::serialization::make_nvp;
		ar & make_nvp("id", _id);
		ar & make_nvp("name", name);
		ar & make_nvp("capability", capability);
		ar & make_nvp("difficulty", _difficulty);
		ar & make_nvp("environment", environment);
		ar & make_nvp("visibility", visibility);
		ar & make_nvp("enemies", enemies);
	}
};


#endif // Sector_h__