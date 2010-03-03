#ifndef Room_h__
#define Room_h__

class Room {
public:
	Room();
	~Room();
	std::string toString() const;
	void addData(const std::string&);
	int objectCount();
private:
	std::vector<std::string> data_;

};

inline Room::Room()
{

}

inline Room::~Room()
{

}
#endif // Room_h__