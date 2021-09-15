#include "requestHandlers.hpp"

#include <sstream>

using namespace std;

void addJeek();

int main(int argc, char **argv) {
    addJeek();
    srand(time(0));
    try {
        Server server(argc > 1 ? atoi(argv[1]) : 5000, "htmlFiles/404.html");
        server.get("/home_icon", new ShowImage("htmlFiles/home.png"));
        server.get("/", new ShowPage("htmlFiles/home.html"));
        server.get("/home", new ShowPage("htmlFiles/home.html"));
        server.get("/signup_page", new ShowPage("htmlFiles/signup.html"));
        server.post("/signup", new SignUpHandler());
        server.get("/login_page", new ShowPage("htmlFiles/login.html"));
        server.post("/login", new LoginHandler());
        server.get("/search_page", new ShowPage("htmlFiles/search.html"));
        server.post("/search", new SearchHandler());
        server.get("/jeek", new ShowJeek("htmlFiles/jeek.html"));
        server.get("/like", new LikeHandler());
        server.get("/dislike", new DisLikeHandler());
        server.get("/rejeek", new ReJeekHandler());
        server.get("/logout", new LogOutHandler());
        server.run();
    } catch (Server::Exception e) {
        cout << e.getMessage() << endl;
    }
}

void addJeek()
{
    stringstream sin("zahramo zahra 123445");
    JeekJeek::jeekJeek->signUp(sin);
    sin = stringstream("zahramo 123445");
    JeekJeek::jeekJeek->login(sin);
    JeekJeek::jeekJeek->setSessionId("12" , "zahramo");
    stringstream sin2;
    sin2 << "text" << " " << "hello" << "\n" <<"publish";
    JeekJeek::jeekJeek->readJeek(sin2,"12");
    std::stringstream sin3 ;
    sin3 <<"text"<<" "<<"i am zahra"<<"\n"<<"tag"<<" "<<"jeeeeeek"<<"\n"<<"mention"<<" "<<"moosavi"<<"\n"<<"publish";
    JeekJeek::jeekJeek->readJeek(sin3,"12");
}
