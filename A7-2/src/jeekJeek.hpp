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

#define NOT_FOUND -1

class JeekJeek{
private:
	std::vector<User*> users;
	std::vector<User*> curUsers;
	std::vector<Jeek*> jeeks;
	std::vector<Hashtag*> hashtags;
	std::vector<Comment*> comments;
	int jeekID , commentID;
public:
	static JeekJeek* jeekJeek;
	JeekJeek();
	void signUp(std::stringstream&);
	int findUserName(std::string);
	void login(std::stringstream&);
	void logout(std::string);
	Jeek* handleJeek(std::string input, std::stringstream& inputStream , Jeek* newJeek);
	void readJeek(std::stringstream& , std::string);
	void publishJeek(Jeek* , std::string);
	void handleHashtags(Jeek* newJeek);
	void handleMention(Jeek*);
	void showJeek(std::stringstream&);
	std::string handleSearch(std::string);
	std::string seperateString(std::string input);
	std::string showUserJeeks(int userLoation);
	int findHashtag(std:: string hashtag_);
	std::string showHashtagJeeks(int hashtagLocation);
	void like(std::string,std::string);
	void dislike(std::string,std::string);
	int findJeek(int);
	int findComment(int);
	void reJeek(std::string , std::string);
	void handleFollowingsJeek(int);
	bool isUserActive();
	void checkValidId(std::string);
	void checkUserNamePassword(std::string,int);
	void setSessionId(std::string , std::string);
	std::string getCurUserName(std::string);
	std::string getJeeksString(std::string);
	int findUserBySessionId(std:: string sessionId);
	std::string getJeekString(int);
};

#endif