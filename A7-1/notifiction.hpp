#ifndef _NOTIFICATION_
#define _NOTIFICATION_

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Notification {
protected:
	std::string username;
	int id;
public:
	virtual void print() = 0;
	Notification(std::string, int);
};

class MentionNotif : public Notification {
private:
public:
	MentionNotif(std::string username_, int id_): Notification(username_, id_) {};
	void print();
};

class LikeNotif : public Notification {
private:
public:
	LikeNotif(std::string username_, int id_): Notification(username_, id_) {};
	void print();
};

class DislikeNotif : public Notification {
private:
public:
	DislikeNotif(std::string username_, int id_): Notification(username_, id_) {};
	void print();
};

class ReplyNotif : public Notification {
private:
public:
	ReplyNotif(std::string username_, int id_): Notification(username_, id_) {};
	void print();
};

class CommentNotif : public Notification {
private:
public:
	CommentNotif(std::string username_, int id_): Notification(username_, id_) {};
	void print();
};

class JeekNotif : public Notification {
private:
public:
	JeekNotif(std::string username_, int id_): Notification(username_, id_) {};
	void print();
};

class RejeekNotif : public Notification {
private:
public:
	RejeekNotif(std::string username_, int id_): Notification(username_, id_) {};
	void print();
};






#endif