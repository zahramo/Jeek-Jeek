#include <string>
#include <vector>
#include "user.hpp"
#include <iostream>

class Comment{
private:
	std::string text;
	int id;
	std::vector<int> replyIds;
	User* publisher;
public:
	Comment(std::string , int);
	int getId();
	void addReply(int);
	void show();
	void setPublisher(User*);
	User* getPublisher();
};