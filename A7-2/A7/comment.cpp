#include "comment.hpp"

Comment :: Comment (std::string text_ , int id_)
{
	text= text_;
	id = id_;
}

int Comment :: getId()
{
	return id;
}

void Comment :: addReply(int replyId)
{
	replyIds.push_back(replyId);
}

void Comment :: show()
{
	std::cout<<publisher->getDisplayName()<<std::endl;
	std::cout<<text<<std::endl;
	std::cout<<"Replies:"<<std::endl;
	for(int i=0 ; i<replyIds.size() ; i++)
	{
		std::cout<<replyIds[i]<<std::endl;
	}
}

void Comment :: setPublisher(User* publisher_)
{
	publisher = publisher_;
}

User* Comment :: getPublisher()
{
	return publisher;
}