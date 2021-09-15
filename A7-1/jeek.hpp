#ifndef _JEEK_
#define _JEEK_

#include "user.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#define NOT_FOUND -1

class Jeek {
protected:
	int id;
	User* publisher;
	std::string text;
	std::vector<std::string> hashtags;
	std::vector<User*> likers;
	std::vector<std::string> mentioneds;
	int rejeeks ;
	std::vector<int> commentIds;
public:
	Jeek() {rejeeks = 0;}
	void setPublisher(User*);
	void setText(std::string);
	void addHashtag(std::string);
	void setId(int);
	std::vector<std::string> getHashtags();
	void addMentioned(std::string);
	std::vector<std::string> getMentioneds();
	int getId();
	void show();
	void showForUser();
	void addLiker(User*);
	void removeLiker(std::string);
	int findLiker(std::string);
	void addComment(int);
	void addRejeek();
	void setRejeekText(std::string);
	std::string getText();
	User* getPublisher();
};

#endif