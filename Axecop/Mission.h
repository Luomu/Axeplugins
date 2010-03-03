#ifndef Mission_h__
#define Mission_h__

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class Mission
{
public:
	Mission();
	Mission(int sector);
	int dropCost() const { return cost; }
	int sector() const { return sectorId; }
	CString toString() const;
private:
	friend class boost::serialization::access;
	int cost;
	int sectorId;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar & sectorId;
		ar & cost;
	}
};

#endif // Mission_h__