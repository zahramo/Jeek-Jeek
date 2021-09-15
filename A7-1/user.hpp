#ifndef _USER_
#define _USER_

#include <vector>
#include <string>
#include "notifiction.hpp"
#include <sstream>

#define NOT_FOUND -1

class User {
private:
	std::string userName , displayName , password;
	std::vector<int> jeekIds;
	std::vector<Notification*> notifications;
	std::vector<User*> followers, followings;
public:
	User(std::string userName, std::string displayName, std::string password);
	std::string getUserName();
	void addJeek(int);
	void addNotification(Notification*);
	std::vector<int> getJeekIds();
	std::string getDisplayName();
	void addFollower(User*);
	void addFollowing(User*);
	void removeFollower(std::string);
	void removeFollowing(std::string);
	int findFollower(std::string);
	int findFollowing(std::string);
	User* findFollowing(User*);
	void showNotifications();
	std::string getPassword();
};

#endif