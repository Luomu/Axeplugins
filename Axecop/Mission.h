#ifndef Mission_h__
#define Mission_h__

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/map.hpp> 
#include <boost/serialization/variant.hpp>
#include <boost/variant.hpp>
#include <map>

class Mission
{
public:
	Mission();
	Mission(int sector);
	int dropCost() const { return cost; }
	int sector() const { return sectorId; }
	CString toString() const;
	int const intprop(const std::string&);
private:
	friend class boost::serialization::access;
	friend class ExtObject;
	int cost;
	int sectorId;
	std::map<std::string, boost::variant<int, std::string>> properties;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		using boost::serialization::make_nvp;
		ar & make_nvp("id", sectorId);
		ar & make_nvp("cost", cost);
		ar & make_nvp("properties", properties);
	}
};

#endif // Mission_h__