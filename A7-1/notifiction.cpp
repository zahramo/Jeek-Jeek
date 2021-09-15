#include "notifiction.hpp"

Notification :: Notification(std::string username_, int id_)
{
	username = username_;
	id = id_;
}

void LikeNotif :: print()
{
	std::cout << username << " liked " << id << std::endl;
}

void DislikeNotif :: print()
{
	std::cout << username << " disliked " << id << std::endl;
}

void MentionNotif :: print()
{
	std::cout << username << " mentioned you in " << id << std::endl;
}

void CommentNotif :: print()
{
	std::cout << username << " commented " << id << std::endl;
}

void ReplyNotif :: print()
{
	std::cout << username << " replied " << id << std::endl;
}

void JeekNotif :: print()
{
	std::cout << username << " jeeked " << id << std::endl;
}

void RejeekNotif :: print()
{
	std::cout << username << " rejeeked " << id << std::endl;
}