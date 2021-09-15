#ifndef _HASHTAG_
#define _HASHTAG_

#include <vector>
#include <string>
#include <sstream>

class Hashtag {
private:
	std::string name;
	std::vector<int> jeekIds;
public:
	Hashtag(std::string);
	void addJeek(int);
	std::string getName();
	std::vector<int> getJeekIds();
};

#endif