#include "jeek.hpp"

void Jeek :: setText(std::string text_)
{
	text = text_;
}

void Jeek :: addHashtag(std::string hashtag)
{
	hashtags.push_back(hashtag);
}

void Jeek :: setId(int id_)
{
	id = id_;
}

std::vector<std::string> Jeek :: getHashtags()
{
	return hashtags;
}

void Jeek :: addMentioned(std::string userName)
{
	mentioneds.push_back(userName);
}

std::vector<std::string> Jeek :: getMentioneds()
{
	return mentioneds;
}

int Jeek :: getId()
{
	return id;
}

void Jeek :: show()
{
	std::cout << publisher->getUserName() << std::endl << text << std::endl;
	for (int i = 0; i < hashtags.size(); i++)
	{
		std::cout << "#" << hashtags[i] << std::endl;
	}
	for (int i = 0 ; i < mentioneds.size() ; i++)
	{
		std::cout << "@" << mentioneds[i] << std::endl;
	}
	std::cout << "Likes " << likers.size() << std::endl;
	std::cout << "Rejeeks " << rejeeks << std::endl;
	std::cout << "comments:" << std::endl;
	for (int i = 0 ; i < commentIds.size() ; i++)
	{
		std::cout << commentIds[i] << std::endl;
	}
}

void Jeek :: setPublisher(User* publisher_)
{
	publisher = publisher_;
}

void Jeek :: showForUser()
{
	std::cout << id << " " << publisher->getDisplayName() << std::endl << text << std::endl;
}

void Jeek :: addLiker(User* newUser)
{
	if (findLiker(newUser->getUserName()) == NOT_FOUND)
	{
		likers.push_back(newUser);
	}
}

void Jeek :: removeLiker(std::string delUserName)
{
	int likerLocation = findLiker(delUserName);
	if (likerLocation != NOT_FOUND)
	{
		likers.erase(likers.begin() + likerLocation);
	}
}

int Jeek :: findLiker(std::string userName_)
{
	for (int i = 0; i < likers.size() ; i++)
	{
		if (likers[i]->getUserName() == userName_)
		{
			return i;
		}
	}
	return NOT_FOUND;
}

void Jeek :: addComment(int commentId)
{
	commentIds.push_back(commentId);
}

void Jeek :: addRejeek()
{
	rejeeks++;
}

void Jeek :: setRejeekText(std::string text_)
{
	text = "Rejeeked:" + text_;
}

std::string Jeek :: getText()
{
	return text;
}

User* Jeek :: getPublisher()
{
	return publisher;
}