using namespace std;
#include "jeekJeek.hpp"

JeekJeek* JeekJeek::jeekJeek = new JeekJeek;
bool JeekJeek :: isUserActive()
{
	if (curUser == NULL)
	{
		return false;
	}
	return true;

}

void JeekJeek :: handleInputs(std::string input, std::stringstream& inputStream)
{
	std::cout << std::endl << std::endl;
	if (input == "signup")
	{
		signUp(inputStream);
	}
	else if (input == "login")
	{
		login(inputStream);
	}
	else if (input == "logout")
	{
		logout(inputStream);
	}
	else if (input == "jeek")
	{
		readJeek();
	}
	else if (input == "showJeek")
	{
		showJeek(inputStream);
	}
	else if (input == "search")
	{
		handleSearch(inputStream);
	}
	else if (input == "follow")
	{
		follow(inputStream);
	}
	else if (input == "unfollow")
	{
		unfollow(inputStream);
	}
	else if (input == "like")
	{
		like(inputStream);
	}
	else if (input == "dislike")
	{
		dislike(inputStream);
	}
	else if (input == "comment")
	{
		addComment(inputStream);
	}
	else if (input == "reply")
	{
		reply(inputStream);
	}
	else if (input == "rejeek")
	{
		reJeek(inputStream);
	}
	else if (input == "showComment")
	{
		showComment(inputStream);
	}
	else if (input == "showReply")
	{
		showComment(inputStream);
	}
	else if (input == "notifications")
	{
		showNotifications();
	}
	else
	{
		throw BadInputs();
	}
}

void JeekJeek :: showNotifications()
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	curUser->showNotifications();
}

void JeekJeek :: showComment(std::stringstream& inputStream)
{
	std::string commentIdS;
	int commentId;
	inputStream >> commentIdS;
	if (commentIdS.empty() == 1)
	{
		throw BadInputs();
	}
	checkValidId(commentIdS);
	commentId = stoi(commentIdS);
	int commentLocation = findComment(commentId);
	if (commentLocation == -1)
	{
		throw InValidId();
	}
	comments[commentLocation]->show();
}

void JeekJeek :: reJeek(std::stringstream& inputStream)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	std::string jeekIdS;
	int jeekId;
	inputStream >> jeekIdS;
	if (jeekIdS.empty() == 1)
	{
		throw BadInputs();
	}
	checkValidId(jeekIdS);
	jeekId = stoi(jeekIdS);
	int jeekLocation = findJeek(jeekId);
	if (jeekLocation == -1)
	{
		throw InValidUserName();
	}
	Jeek* newJeek = new Jeek;
	newJeek->setRejeekText(jeeks[jeekLocation]->getText());
	newJeek->setId(jeekID);
	newJeek->setPublisher(curUser);
	jeeks[jeekLocation]->addRejeek();
	jeeks.push_back(newJeek);
	curUser->addJeek(jeekID);
	jeekID++;
	RejeekNotif* newNotif = new RejeekNotif(curUser->getUserName(), jeekId);
	(jeeks[jeekLocation]->getPublisher())->addNotification(newNotif);
}

JeekJeek :: JeekJeek()
{
	jeekID = 0;
	commentID = 0;
	curUser = NULL;
}

void JeekJeek :: addComment(std::stringstream& inputStream)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	int jeekId;
	std::string jeekIdS;
	std::string text;
	inputStream >> jeekIdS ;
	getline(inputStream , text);
	if (jeekIdS.empty() == 1 || text.empty() == 1)
	{
		throw BadInputs();
	}
	checkValidId(jeekIdS);
	jeekId = stoi(jeekIdS);
	Comment* newComment = new Comment(text, commentID);
	newComment->setPublisher(curUser);
	comments.push_back(newComment);
	int jeekLocation = findJeek(jeekId);
	jeeks[jeekLocation]->addComment(commentID);
	commentID ++;
	CommentNotif* newNotif = new CommentNotif(curUser->getUserName(), jeekId);
	(jeeks[jeekLocation]->getPublisher())->addNotification(newNotif);
}

void JeekJeek :: readInputs()
{
	std::string line, input;
	while (getline(std::cin , line))
	{
		try {
			std::stringstream inputStream;
			inputStream << line;
			inputStream >> input;
			handleInputs(input, inputStream);
		} catch (BadInputs e1)
		{
			std::cout << "Bad Inputs" << std::endl;
		}
		catch (RepeatedUserName e2)
		{
			std::cout << "Repeated UserName" << std::endl;
		}
		catch (UserLoginException e3)
		{
			std::cout << "UserLogin Exception" << std::endl;
		}
		catch (InValidUserName e4)
		{
			std::cout << "InValid UserName" << std::endl;
		}
		catch (InValidId e5)
		{
			std::cout << "InValid id" << std::endl;
		}
		catch (InValidHashtag e6)
		{
			std::cout << "InValid Hashtag" << std::endl;
		}
	}
}


void JeekJeek :: signUp(std::stringstream& inputStream)
{
	if (isUserActive())
	{
		throw UserLoginException();
	}
	std::string userName , displayName , password;
	inputStream >> userName >> displayName >> password;
	if (userName.empty() == 1 || displayName.empty() == 1 || password.empty() == 1)
	{
		throw BadInputs();
	}
	if (findUserName(userName) == -1)
	{
		User* newUser = new User(userName, displayName, password);
		users.push_back(newUser);
	}
	else
	{
		throw RepeatedUserName();
	}
}

int JeekJeek :: findUserName(std::string userName)
{
	for (int i = 0 ; i < users.size() ; i++)
	{
		if (users[i]->getUserName() == userName)
		{
			return i;
		}
	}
	return -1;
}

void JeekJeek :: checkUserNamePassword(std::string password , int userLoation)
{
	if(users[userLoation]->getPassword() != password)
	{
		throw InValidUserName();
	}
}

void JeekJeek :: login(std::stringstream& inputStream)
{
	std::string userName , password;
	if (isUserActive())
	{
		throw UserLoginException();
	}
	inputStream >> userName >> password;
	if (userName.empty() == 1 || password.empty() == 1)
	{
		throw BadInputs();
	}
	if (findUserName(userName) == -1)
	{
		throw InValidUserName();
	}
	checkUserNamePassword(password,findUserName(userName));
	curUser = users[findUserName(userName)];
}

void JeekJeek :: setSessionId(std::string sessionId)
{
	curUser->setSessionId(sessionId);
}

void JeekJeek :: logout(std::stringstream& inputStream)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	curUser = NULL;
}

void JeekJeek :: readJeek()
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}

	Jeek* newJeek = new Jeek;
	std::string line , input = "" , text;

	while (input != "abort" && input != "publish")
	{
		getline(std::cin , line);
		std::stringstream inputStream(line);
		inputStream >> input;
		std::cout << "input : " << input << std::endl;
		newJeek = handleJeek(input , inputStream , newJeek);
	}
	if (input == "abort")
	{
		return;
	}
	else if (input == "publish")
	{
		publishJeek(newJeek);
		handleHashtags(newJeek);
		handleMention(newJeek);
	}
}

Jeek* JeekJeek :: handleJeek(std::string input, std::stringstream& inputStream , Jeek* newJeek)
{
	if (input == "text")
	{
		std::string text;
		getline(inputStream, text);
		if (text.empty() == 1 || text.size() > 140)
		{
			throw BadInputs();
		}
		newJeek->setText(text);
	}
	else if (input == "tag")
	{
		std::string hashtag;
		inputStream >> hashtag;
		if (hashtag.empty() == 1)
		{
			throw BadInputs();
		}
		newJeek ->addHashtag(hashtag);
	}
	else if (input == "mention")
	{
		std::string userName;
		inputStream >> userName;
		if (userName.empty() == 1)
		{
			throw BadInputs();
		}
		newJeek ->addMentioned(userName);
	}
	else if (input != "publish" && input != "abort")
	{
		std::cout << "heree" << std::endl;
		throw BadInputs();
	}
	return newJeek;
}

void JeekJeek :: publishJeek(Jeek* newJeek)
{
	int jeekId = jeekID;
	jeekID ++;
	newJeek->setId(jeekId);
	newJeek->setPublisher(curUser);
	jeeks.push_back(newJeek);
	curUser->addJeek(jeekId);
	handleFollowingsJeek(jeekId);
}

void JeekJeek :: handleHashtags(Jeek* newJeek)
{
	std::vector<std::string> jeekHashtags = newJeek->getHashtags();
	for (int i = 0 ; i < jeekHashtags.size() ; i++)
	{
		Hashtag* newHashtag = new Hashtag(jeekHashtags[i]);
		newHashtag->addJeek(newJeek->getId());
		hashtags.push_back(newHashtag);
	}
}

void JeekJeek :: handleMention(Jeek* newJeek)
{
	std::vector<std::string> jeekMentioneds = newJeek->getMentioneds();
	int userLoation;
	for (int i = 0 ; i < jeekMentioneds.size() ; i++)
	{
		userLoation = findUserName(jeekMentioneds[i]);
		if (userLoation != -1)
		{
			MentionNotif* newNotif = new MentionNotif(curUser->getUserName(), newJeek->getId());
			users[userLoation]->addNotification(newNotif);
		}
		else
		{
			throw InValidUserName();
		}
	}
}

void JeekJeek :: showJeek(std::stringstream& inputStream)
{
	std::string jeekIdS;
	inputStream >> jeekIdS;
	checkValidId(jeekIdS);
	int jeekId = stoi(jeekIdS);
	jeeks[jeekId]->show();
}

void JeekJeek :: checkValidId(std::string id)
{
	for (int i = 0 ; i < id.size() ; i++)
	{
		if (id[i] < '0' || id[i] > '9')
		{
			throw InValidId();
		}
	}
}

void JeekJeek :: handleSearch(std::stringstream& inputStream)
{
	std::string input;
	inputStream >> input;
	if (input.empty() == 1)
	{
		throw BadInputs();
	}

	if (input[0] == '@')
	{
		std::string userName = seperateString(input);
		int userLoation = findUserName(userName);
		if (userLoation == -1)
		{
			throw InValidUserName();
		}
		showUserJeeks(userLoation);
	}
	else if (input[0] == '#')
	{
		std::string hashtag_ = seperateString(input);
		int hashtagLocation = findHashtag(hashtag_);
		if (hashtagLocation == -1)
		{
			throw InValidHashtag();
		}
		showHashtagJeeks(hashtagLocation);
	}
	else
	{
		throw BadInputs();
	}
}

std::string JeekJeek :: seperateString(std::string input)
{
	input.erase(input.begin());
	return input;
}

void JeekJeek :: showUserJeeks(int userLoation)
{
	std::vector<int> jeekIds = users[userLoation]->getJeekIds();
	for (int i = 0 ; i < jeekIds.size() ; i++)
	{
		jeeks[jeekIds[i]]->showForUser();
	}
}

int JeekJeek :: findHashtag(std:: string hashtag_)
{
	for (int i = 0 ; i < hashtags.size() ; i++)
	{
		if (hashtag_ == hashtags[i]->getName())
		{
			return i;
		}
	}
	return -1;
}

void JeekJeek :: showHashtagJeeks(int hashtagLocation)
{
	std::vector<int> jeekIds = hashtags[hashtagLocation]->getJeekIds();
	for (int i = 0 ; i < jeekIds.size() ; i++)
	{
		jeeks[jeekIds[i]]->showForUser();
	}
}

void JeekJeek :: follow(std::stringstream& inputStream)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	std::string userName;
	inputStream >> userName;
	if (userName.empty() == 1)
	{
		throw BadInputs();
	}
	if (findUserName(userName) == -1)
	{
		throw InValidUserName();
	}
	curUser->addFollowing(users[findUserName(userName)]);
	users[findUserName(userName)]->addFollower(curUser);
}

void JeekJeek :: unfollow(std::stringstream& inputStream)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	std::string userName;
	inputStream >> userName;
	if (userName.empty() == 1)
	{
		throw BadInputs();
	}
	if (findUserName(userName) == -1)
	{
		throw InValidUserName();
	}
	curUser->removeFollowing(userName);
	users[findUserName(userName)]->removeFollower(curUser->getUserName());
}

void JeekJeek :: like(std::stringstream& inputStream)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	int jeekId;
	std::string jeekIdS;
	inputStream >> jeekIdS;
	if (jeekIdS.empty() == 1)
	{
		throw BadInputs();
	}
	checkValidId(jeekIdS);
	jeekId = stoi(jeekIdS);
	int jeekLocation = findJeek(jeekId);
	jeeks[jeekLocation]->addLiker(curUser);
	LikeNotif* newNotif = new LikeNotif(curUser->getUserName(), jeekId);
	(jeeks[jeekLocation]->getPublisher())->addNotification(newNotif);
}

void JeekJeek :: dislike(std::stringstream& inputStream)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	int jeekId;
	std::string jeekIdS;
	inputStream >> jeekIdS;
	if (jeekIdS.empty() == 1)
	{
		throw BadInputs();
	}
	checkValidId(jeekIdS);
	jeekId = stoi(jeekIdS);

	int jeekLocation = findJeek(jeekId);
	jeeks[jeekId]->removeLiker(curUser->getUserName());
	DislikeNotif* newNotif = new DislikeNotif(curUser->getUserName(), jeekId);
	(jeeks[jeekLocation]->getPublisher())->addNotification(newNotif);
}

int JeekJeek :: findJeek(int jeekId)
{
	for (int i = 0 ; i < jeeks.size() ; i++)
	{
		if (jeeks[i]->getId() == jeekId)
		{
			return i;
		}
	}
	return -1;
}

int JeekJeek :: findComment(int commentId)
{
	for (int i = 0 ; i < comments.size() ; i++)
	{
		if (comments[i]->getId() == commentId)
		{
			return i;
		}
	}
	return -1;
}

void JeekJeek :: reply(std::stringstream& inputStream)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	int commentId;
	std::string commentIdS;
	std::string text;
	inputStream >> commentIdS;
	getline(inputStream, text);
	if (text.empty() == 1 || commentIdS.empty() == 1)
	{
		throw BadInputs();
	}
	checkValidId(commentIdS);
	commentId = stoi(commentIdS);
	Comment* newComment = new Comment(text, commentID);
	newComment->setPublisher(curUser);
	comments.push_back(newComment);
	int commentLocation = findComment(commentId);
	comments[commentLocation]->addReply(commentID);
	commentID ++;
	ReplyNotif* newNotif = new ReplyNotif(curUser->getUserName(), commentId);
	(comments[commentLocation]->getPublisher())->addNotification(newNotif);
}

void JeekJeek :: handleFollowingsJeek(int jeekId)
{
	for (int i = 0 ; i < users.size() ; i++)
	{
		if (users[i]->findFollowing(curUser))
		{
			JeekNotif* newNotif = new JeekNotif(curUser->getUserName(), jeekId);
			(users[i]->findFollowing(curUser))->addNotification(newNotif);
		}
	}
}