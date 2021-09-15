#include "../utils/utilities.hpp"
#include "server.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include "../src/jeekJeek.hpp"

using namespace std;

class ShowPage : public RequestHandler {
    string filePath;

public:
    ShowPage(string _filePath) { filePath = _filePath; }
    Response *callback(Request *req) {
        Response *res = new Response;
        res->setHeader("Content-Type", "text/html");
        string body = readFile(filePath.c_str());
        res->setBody(readFile(filePath.c_str()));
        return res;
    }
};

class ShowImage : public RequestHandler {
    string filePath;
public:
    ShowImage(string _filePath) { filePath = _filePath; }
    Response *callback(Request *req) {
        Response *res = new Response;
        res->setHeader("Content-Type", "image/png");
        string body = readFile(filePath.c_str());
        res->setBody(body);
        return res;
    }
};

class LoginHandler : public RequestHandler {
public:
    Response *callback(Request *req) {
        Response *res = new Response;
        res->setHeader("Content-Type", "text/html");
        string username = req->getBodyParam("username");
        string password = req->getBodyParam("password");
        cout << "Received Data: " << username << " - " << password << endl;

        std::stringstream data;
        data << username << " " << password;
        try
        {
            JeekJeek::jeekJeek->login(data);
        }
        catch (InValidUserName e)
        {
            res->setBody(readFile("htmlFiles/login.html"));
            return res;
        }

        // req->getSesionId();
        res->setBody(readFile("htmlFiles/login.html"));
        std::string sessionId = to_string(rand());
        res->setSessionId(sessionId);
        JeekJeek::jeekJeek->setSessionId(sessionId);
        return res;
    }
    // std::string generateHomePage()
    // {
    //     string result;
    //     ifstream fin;
    //     fin.open("htmlFiles/user.html");
    //     char c;
    //     while(fin.get(c))
    //     {
    //         if(c != '$')
    //         {
    //             result += c;
    //         }
    //         else
    //         {
    //             while(c != ')')
    //             {
    //                 fin.get(c);
    //             }
    //             result += "amir";
    //         }
    //     }
    //     return result;
    // }
};

class SignUpHandler : public RequestHandler {
public:
    Response *callback(Request *req) {
        Response *res = new Response;
        res->setHeader("Content-Type", "text/html");
        string username = req->getBodyParam("username");
        string password = req->getBodyParam("password");
        string displayname = req->getBodyParam("displayname");
        cout << "Received Data: " << username << " - " << password << " - " << displayname << endl;
        std::stringstream data;
        data << username << " " << displayname << " " << password;
        try
        {
            JeekJeek::jeekJeek->signUp(data);
        }
        catch (BadInputs e1)
        {
            std::cout << "Bad Inputs" << std::endl;
        }
        catch (RepeatedUserName e2)
        {
            std::cout << "Repeated UserName" << std::endl;
            res->setBody(readFile("htmlFiles/signupError.html"));
            return res;
        }
        catch (UserLoginException e3)
        {
            std::cout << "UserLogin Exception" << std::endl;
        }
       // std::cout <<"hi" << std::endl;
        res->setBody("Salam");
       // std::cout <<"bye" << std::endl;

        return res;
    }
};



int main(int argc, char **argv) {
    char *header_buffer = new char[8096];
  
    // readFile("htmlFiles/login.html");
    srand(time(0));
    try {
        Server server(argc > 1 ? atoi(argv[1]) : 5000);
        server.get("/home_icon", new ShowImage("htmlFiles/home.png"));
        server.get("/", new ShowPage("htmlFiles/home.html"));
        server.get("/home", new ShowPage("htmlFiles/home.html"));
        server.get("/signup_page", new ShowPage("htmlFiles/signup.html"));
        server.post("/signup", new SignUpHandler());
        server.get("/login_page", new ShowPage("htmlFiles/login.html"));
        server.post("/login", new LoginHandler());
        server.run();
    } catch (Server::Exception e) {
        cout << e.getMessage() << endl;
    }
}
