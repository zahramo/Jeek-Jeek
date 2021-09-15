#include "user.hpp"

User :: User(std::string userName_, std::string displayName_, std::string password_)
{
	userName = userName_;
	displayName = displayName_;
	password = password_;
}

std::string User :: getUserName()
{
	return userName;
}

void User :: addJeek(int jeekId)
{
	jeekIds.push_back(jeekId);
}

void User :: addNotification(Notification* newNotif)
{
	notifications.push_back(newNotif);
}

std::vector<int> User :: getJeekIds()
{
	return jeekIds;
}

std:: string User :: getPassword()
{
	return password;
}

std::string User :: getDisplayName()
{
	return displayName;
}

void User :: addFollower(User* newFollower)
{
	if (findFollower(newFollower->getUserName()) == NOT_FOUND)

		followers.push_back(newFollower);
}

void User :: addFollowing(User* newFollowing)
{
	if (findFollowing(newFollowing->getUserName()) == NOT_FOUND)

		followings.push_back(newFollowing);
}

void User :: removeFollower(std::string delUserName)
{
	int followerLocation = findFollower(delUserName);
	if (followerLocation != NOT_FOUND)
	{
		followers.erase(followers.begin() + followerLocation);
	}
}

void User :: removeFollowing(std::string delUserName)
{
	int followingLocation = findFollowing(delUserName);
	if (followingLocation != NOT_FOUND)
	{
		followings.erase(followings.begin() + followingLocation);
	}
}

int User :: findFollower(std::string userName_)
{
	for (int i = 0 ; i < followers.size() ; i++)
	{
		if (followers[i]->getUserName() == userName_)
		{
			return i;
		}
	}
	return NOT_FOUND;
}

int User :: findFollowing(std::string userName_)
{
	for (int i = 0 ; i < followings.size() ; i++)
	{
		if (followings[i]->getUserName() == userName_)
		{
			return i;
		}
	}
	return NOT_FOUND;
}

User* User :: findFollowing(User*)
{
	for (int i = 0 ; i < followings.size() ; i++)
	{
		if (followings[i]->getUserName() == userName)
		{
			return followings[i];
		}
	}
	return NULL;
}

void User :: showNotifications()
{
	for (int i = 0 ; i < notifications.size(); i++)
	{
		notifications[i]->print();
	}
	notifications.clear();
}