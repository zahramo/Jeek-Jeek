#include "../utils/utilities.hpp"
#include "server.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include "../src/jeekJeek.hpp"

#define ADDRESS_OF_LOGIN_PAGE "htmlFiles/login.html"
#define ADDRESS_OF_LOGINERROR_PAGE "htmlFiles/loginError.html"
#define ADDRESS_OF_SIGNUP_PAGE "htmlFiles/signup.html"
#define ADDRESS_OF_SIGNUPERROR_PAGE "htmlFiles/signupError.html"
#define ADDRESS_OF_HOME_PAGE "htmlFiles/home.html"
#define ADDRESS_OF_USERHOME_PAGE "htmlFiles/userHome.html"
#define ADDRESS_OF_SEARCH_PAGE "htmlFiles/search.html"
#define ADDRESS_OF_SEARCHERROR_PAGE "htmlFiles/searchError.html"
#define ADDRESS_OF_JEEK_PAGE "htmlFiles/jeek.html"

using namespace std;

class JeekHandler : public RequestHandler{
public:
    std::string showJeekPage(std::string,std::string,std::string);
};

class ShowJeek : public JeekHandler {
    string filePath;

public:
    ShowJeek(string _filePath) { filePath = _filePath; }
    Response *callback(Request *req) ;
};

class LoginHandler : public RequestHandler {
public:
    Response *callback(Request *req);
    std::string showHomePage(std::string,std::string);
};

class LikeHandler : public JeekHandler {
public:
    Response *callback(Request *req);
};

class LogOutHandler : public RequestHandler {
public:
    Response *callback(Request *req);
};

class DisLikeHandler : public JeekHandler {
public:
    Response *callback(Request *req);
};

class ReJeekHandler : public JeekHandler {
public:
    Response *callback(Request *req);
};


class SearchHandler : public RequestHandler {
public:
    Response *callback(Request *req);
    std::string showSearchPage(std::string,std::string,std::string);
};

class SignUpHandler : public RequestHandler {
public:
    Response *callback(Request *req);
};
