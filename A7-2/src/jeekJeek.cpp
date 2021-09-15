using namespace std;

#include "jeekJeek.hpp"


JeekJeek* JeekJeek::jeekJeek = new JeekJeek;

bool JeekJeek :: isUserActive()
{
	if (curUsers.size() == 0)
	{
		return false;
	}
	return true;

}


void JeekJeek :: reJeek(std::string jeekIdS , std::string sessionId)
{
	int curUserLocation = findUserBySessionId(sessionId);
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	int jeekId;
	if (jeekIdS.empty() == 1)
	{
		throw BadInputs();
	}
	jeekId = stoi(jeekIdS);
	int jeekLocation = findJeek(jeekId);
	if (jeekLocation == NOT_FOUND)
	{
		throw InValidUserName();
	}
	Jeek* newJeek = new Jeek;
	newJeek->setRejeekText(jeeks[jeekLocation]->getText());
	newJeek->setId(jeekID);
	newJeek->setPublisher(users[curUserLocation]);
	jeeks[jeekLocation]->addRejeek();
	jeeks.push_back(newJeek);
	users[curUserLocation]->addJeek(jeekID);
	jeekID++;
}

JeekJeek :: JeekJeek()
{
	jeekID = 0;
	commentID = 0;
}


void JeekJeek :: signUp(std::stringstream& inputStream)
{

	std::string userName , displayName , password;
	inputStream >> userName >> displayName >> password;
	if (userName.empty() == 1 || displayName.empty() == 1 || password.empty() == 1)
	{
		throw BadInputs();
	}
	if (findUserName(userName) == NOT_FOUND)
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
	return NOT_FOUND;
}

void JeekJeek :: checkUserNamePassword(std::string password , int userLoation)
{
	if (users[userLoation]->getPassword() != password)
	{
		throw InValidUserName();
	}
}

void JeekJeek :: login(std::stringstream& inputStream)
{
	std::string userName , password;
	inputStream >> userName >> password;
	if (userName.empty() == 1 || password.empty() == 1)
	{
		throw BadInputs();
	}
	if (findUserName(userName) == NOT_FOUND)
	{
		throw InValidUserName();
	}
	checkUserNamePassword(password, findUserName(userName));
	curUsers.push_back(users[findUserName(userName)]);
}

void JeekJeek :: setSessionId(std::string sessionId , std::string curUserName)
{
	int curUserLocation = findUserName(curUserName);
	users[curUserLocation]->setSessionId(sessionId);
}

std::string JeekJeek :: getCurUserName(std::string sessionId)
{
	int curUserLocation = findUserBySessionId(sessionId);
	return curUsers[curUserLocation]->getDisplayName();
}

void JeekJeek :: logout(std::string sessionId)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	int curUserLocation = findUserBySessionId(sessionId);
	curUsers.erase(curUsers.begin() + curUserLocation);
}

int JeekJeek :: findUserBySessionId(std:: string sessionId)
{
	for (int i = 0 ; i < curUsers.size() ; i++)
	{
		if (curUsers[i]->getSessionId() == sessionId)
		{
			return i;
		}
	}
	return NOT_FOUND;
}

void JeekJeek :: readJeek(std::stringstream& data, std::string sessionId)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}

	Jeek* newJeek = new Jeek;
	std::string line , input = "" , text;

	while (input != "abort" && input != "publish")
	{
		getline(data , line);
		std::stringstream inputStream(line);
		inputStream >> input;
		newJeek = handleJeek(input , inputStream , newJeek);
	}
	if (input == "abort")
	{
		return;
	}
	else if (input == "publish")
	{
		publishJeek(newJeek , sessionId);
		handleHashtags(newJeek);
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
		throw BadInputs();
	}
	return newJeek;
}

void JeekJeek :: publishJeek(Jeek* newJeek , std::string sessionId)
{
	int jeekId = jeekID;
	jeekID ++;
	int curUserLocation = findUserBySessionId(sessionId);
	newJeek->setId(jeekId);
	newJeek->setPublisher(curUsers[curUserLocation]);
	jeeks.push_back(newJeek);
	curUsers[curUserLocation]->addJeek(jeekId);
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


std::string JeekJeek :: getJeeksString(std::string sessionId)
{
	std::string result;
	int curUserLocation = findUserBySessionId(sessionId);
	std::vector<int> usersJeekIds = curUsers[curUserLocation]->getJeekIds();

	for (int i = jeeks.size()-1 ; i >=0 ; i--)
	{
		for (int j = 0 ; j < usersJeekIds.size() ; j++)
		{
			if (jeeks[i]->getId() == usersJeekIds[j])
			{
				result += jeeks[i]->getHtmlString();
			}
		}
	}



	return result;
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

std::string JeekJeek :: handleSearch(std::string input)
{
	if (input.empty() == 1)
	{
		throw BadInputs();
	}

	if (input[0] == '@')
	{
		std::string userName = seperateString(input);
		int userLoation = findUserName(userName);
		if (userLoation == NOT_FOUND)
		{
			throw InValidUserName();
		}
		return showUserJeeks(userLoation);
	}
	else if (input[0] == '#')
	{
		std::string hashtag_ = seperateString(input);
		int hashtagLocation = findHashtag(hashtag_);
		if (hashtagLocation == NOT_FOUND)
		{
			throw InValidHashtag();
		}
		return showHashtagJeeks(hashtagLocation);
	}
	else
	{
		throw BadInputs();
	}
}

std::string JeekJeek :: getJeekString(int jeekId)
{
	int jeekLocation = findJeek(jeekId);
	return jeeks[jeekLocation]->getCompleteHtmlString();
}

std::string JeekJeek :: seperateString(std::string input)
{
	input.erase(input.begin());
	return input;
}

std::string JeekJeek :: showUserJeeks(int userLoation)
{
	std::vector<int> jeekIds = users[userLoation]->getJeekIds();
	std::string result;
	result = "<p>" + users[userLoation]->getUserName() + "s jeeks :<br></p>";
	for (int i = jeekIds.size()-1 ; i >=0 ; i--)
	{
		result += jeeks[jeekIds[i]]->getHtmlString();
	}
	return result;
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
	return NOT_FOUND;
}

std::string JeekJeek :: showHashtagJeeks(int hashtagLocation)
{
	std::string result;
	std::vector<int> jeekIds = hashtags[hashtagLocation]->getJeekIds();
	for (int i = 0 ; i < jeekIds.size() ; i++)
	{
		result += (jeeks[jeekIds[i]]->getPublisher())->getUserName() + "s jeek :<br>";
		result += jeeks[jeekIds[i]]->getHtmlString();
	}

	return result;
}



void JeekJeek :: like(std::string jeekIdS , std::string sessionId)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	int jeekId = stoi(jeekIdS);
	int jeekLocation = findJeek(jeekId);
	int curUserLocation = findUserBySessionId(sessionId);
	jeeks[jeekLocation]->addLiker(curUsers[curUserLocation]);
}

void JeekJeek :: dislike(std::string jeekIdS , std::string sessionId)
{
	if (!isUserActive())
	{
		throw UserLoginException();
	}
	int jeekId;
	if (jeekIdS.empty() == 1)
	{
		throw BadInputs();
	}
	jeekId = stoi(jeekIdS);

	int jeekLocation = findJeek(jeekId);
	int curUserLocation = findUserBySessionId(sessionId);
	jeeks[jeekId]->removeLiker(curUsers[curUserLocation]->getUserName());
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
	return NOT_FOUND;
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
	return NOT_FOUND;
}

