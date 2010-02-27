#ifndef RoomObject_h__
#define RoomObject_h__

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class RoomObject {
public:
	RoomObject();
	int type; // tiled, sprite, whatelse?
	std::string name;
	int xpos;
	int ypos;
	int angle;
	int width;
	int height;
	std::string xdata;
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & type;
		ar & name;
		ar & xpos;
		ar & ypos;
		ar & angle;
		ar & width;
		ar & height;
		ar & xdata;
	}
};

#endif // RoomObject_h__