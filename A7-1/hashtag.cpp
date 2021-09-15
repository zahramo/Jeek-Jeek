#include "hashtag.hpp"

Hashtag :: Hashtag(std::string name_)
{
	name = name_;
}

void Hashtag :: addJeek(int jeekId)
{
	jeekIds.push_back(jeekId);
}

std::string Hashtag :: getName()
{
	return name;
}

std::vector<int> Hashtag :: getJeekIds()
{
	return jeekIds;
}