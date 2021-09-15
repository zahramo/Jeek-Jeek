#ifndef _JeekJeek_
#define _JeekJeek_

#include "user.hpp"
#include "hashtag.hpp"
#include "comment.hpp"
#include "jeek.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include "exeption.hpp"

class JeekJeek{
private:
	std::vector<User*> users;
	User* curUser;
	std::vector<Jeek*> jeeks;
	std::vector<Hashtag*> hashtags;
	std::vector<Comment*> comments;
	int jeekID , commentID;
public:
	JeekJeek();
	void handleInputs(std::string, std::stringstream&);
	void readInputs();
	void signUp(std::stringstream&);
	int findUserName(std::string);
	void login(std::stringstream&);
	void logout(std::stringstream&);
	Jeek* handleJeek(std::string input, std::stringstream& inputStream , Jeek* newJeek);
	void readJeek();
	void publishJeek(Jeek*);
	void handleHashtags(Jeek* newJeek);
	void handleMention(Jeek*);
	void showJeek(std::stringstream&);
	void handleSearch(std::stringstream&);
	std::string seperateString(std::string input);
	void showUserJeeks(int userLoation);
	int findHashtag(std:: string hashtag_);
	void showHashtagJeeks(int hashtagLocation);
	void follow(std::stringstream&);
	void unfollow(std::stringstream&);
	void like(std::stringstream&);
	void dislike(std::stringstream&);
	void addComment(std::stringstream&);
	int findJeek(int);
	int findComment(int);
	void reply(std::stringstream&);
	void reJeek(std::stringstream&);
	void showComment(std::stringstream&);
	void showNotifications();
	void handleFollowingsJeek(int);
	bool isUserActive();
	void checkValidId(std::string);
	void checkUserNamePassword(std::string,int);
};

#endif