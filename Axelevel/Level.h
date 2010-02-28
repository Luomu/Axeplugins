#ifndef Level_h__
#define Level_h__

class Level {
public:
	Level() : width(10), height(10) {}
	int width;
	int height;
	void clear() { rooms.clear(); }
	void addRoom(int rtype, int rangle);
private:
	std::vector<std::vector<int>> rooms;
};

void Level::addRoom( int rtype, int rangle )
{
	rooms.push_back(std::vector<int>());
	rooms.back().push_back(rtype);
	rooms.back().push_back(rangle);
}
#endif // Level_h__