#include "requestHandlers.hpp"

Response* LoginHandler :: callback(Request *req)
{
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    std::stringstream data;
    data << username << " " << password;
    try
    {
        JeekJeek::jeekJeek->login(data);
    }
    catch (InValidUserName e)
    {
        res->setBody(readFile(ADDRESS_OF_LOGINERROR_PAGE));
        return res;
    }
    std::string sessionId = to_string(rand());
    res->setSessionId(sessionId);
    JeekJeek::jeekJeek->setSessionId(sessionId, username);
    res->setBody(showHomePage(ADDRESS_OF_USERHOME_PAGE , sessionId));
    return res;
}

std::string LoginHandler :: showHomePage(std::string fileAddress , std::string sessionId)
{
    string result;
    ifstream fin;
    fin.open(fileAddress);
    char c;
    while (fin.get(c))
    {
        if (c != '$')
        {
            result += c;
        }
        else
        {
            fin.get(c);
            fin.get(c);
            std::string content;
            while (c != ')')
            {
                content += c;
                fin.get(c);
            }
            if (content == "name")
                result += JeekJeek :: jeekJeek->getCurUserName(sessionId);
            else if (content == "jeeks")
                result += JeekJeek :: jeekJeek->getJeeksString(sessionId);
        }
    }
    return result;
}


Response* ShowJeek :: callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string jeekId = req->getQueryParam("jeekId");
    res->setBody(showJeekPage(filePath.c_str() , req-> getSessionId() , jeekId));
    return res;
}

std::string JeekHandler :: showJeekPage(std::string fileAddress , std::string sessionId , std::string jeekId)
{
    string result;
    ifstream fin;
    fin.open(fileAddress);
    char c;
    while (fin.get(c))
    {
        if (c != '$')
        {
            result += c;
        }
        else
        {
            fin.get(c);
            fin.get(c);
            std::string content;
            while (c != ')')
            {
                content += c;
                fin.get(c);
            }
            if (content == "name")
                result += JeekJeek :: jeekJeek->getCurUserName(sessionId);
            else if (content == "jeek")
            {
                result += JeekJeek :: jeekJeek->getJeekString(stoi(jeekId));
                result += "<form action=\"/like\" method=\"get\">";
                result += "<input name=\"jeekId\" style=\"display:none\" value =\"" + jeekId + "placeholder=\"Id\"> ";
            }
        }
    }
    return result;

}

Response* LikeHandler :: callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string jeekId = req->getQueryParam("jeekId");
    JeekJeek :: jeekJeek->like(jeekId, req->getSessionId());
    res->setBody(showJeekPage(ADDRESS_OF_JEEK_PAGE , req-> getSessionId() , jeekId));
    return res;
}


Response* DisLikeHandler :: callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string jeekId = req->getQueryParam("jeekId");
    JeekJeek :: jeekJeek->dislike(jeekId, req->getSessionId());
    res->setBody(showJeekPage(ADDRESS_OF_JEEK_PAGE , req-> getSessionId() , jeekId));
    return res;
}

Response* LogOutHandler :: callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    JeekJeek :: jeekJeek->logout(req->getSessionId());
    res->setBody(readFile(ADDRESS_OF_LOGIN_PAGE));
    return res;
}

Response* ReJeekHandler :: callback(Request *req) {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string jeekId = req->getQueryParam("jeekId");
    JeekJeek :: jeekJeek->reJeek(jeekId, req->getSessionId());
    res->setBody(showJeekPage(ADDRESS_OF_JEEK_PAGE , req-> getSessionId() , jeekId));
    return res;
}

Response* SearchHandler :: callback(Request *req)
{
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string searchInput = req->getBodyParam("searchInput");
    std::stringstream data;
    data << searchInput;
    if (showSearchPage(ADDRESS_OF_SEARCH_PAGE , req->getSessionId() , searchInput) == "error")
    {
        res->setBody(showSearchPage(ADDRESS_OF_SEARCHERROR_PAGE , req->getSessionId() , searchInput));
    }
    else
    {
        res->setBody(showSearchPage(ADDRESS_OF_SEARCH_PAGE , req->getSessionId() , searchInput));
    }
    return res;
}


std::string SearchHandler :: showSearchPage(std::string fileAddress , std::string sessionId , std::string input )
{
    string result;
    ifstream fin;
    fin.open(fileAddress);
    char c;
    while (fin.get(c))
    {
        if (c != '$')
        {
            result += c;
        }
        else
        {
            fin.get(c);
            fin.get(c);
            std::string content;
            while (c != ')')
            {
                content += c;
                fin.get(c);
            }
            if (content == "name")
                result += JeekJeek :: jeekJeek->getCurUserName(sessionId);
            else if (content == "jeeks")
                try
                {
                    result += JeekJeek :: jeekJeek->handleSearch(input);
                }
                catch (...)
                {
                    return "error";
                }

        }
    }
    return result;
}

Response* SignUpHandler :: callback(Request *req) {
    Response* res = new Response;
    res->setHeader("Content-Type", "text/html");

    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    std::string displayName = req->getBodyParam("displayname");

    std::stringstream data;
    data << username << ' ' << displayName << ' ' << password;
    try {
        JeekJeek::jeekJeek->signUp(data);
    }
    catch (RepeatedUserName e)
    {
        res->setBody(readFile(ADDRESS_OF_SIGNUPERROR_PAGE));
        return res;

    }
    res->setBody(readFile(ADDRESS_OF_LOGIN_PAGE));
    return res;
}