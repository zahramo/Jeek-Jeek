CC = g++ -std=c++11
all: a.out
	./a.out 
a.out : main.o comment.o hashtag.o jeek.o jeekJeek.o notifiction.o user.o
	$(CC) -g main.o comment.o hashtag.o jeek.o jeekJeek.o notifiction.o user.o
main.o : main.cpp jeekJeek.o
	$(CC) -c main.cpp
comment.o : comment.cpp user.cpp
	$(CC) -c comment.cpp
hashtag.o: hashtag.cpp
	$(CC) -c hashtag.cpp
jeek.o: jeek.cpp user.cpp
	$(CC) -c jeek.cpp
jeekJeek.o: jeekJeek.cpp user.cpp hashtag.cpp comment.cpp jeek.cpp
	$(CC) -c jeekJeek.cpp
notifiction.o: notifiction.cpp 
	$(CC) -c notifiction.cpp
user.o: user.cpp notifiction.cpp
	$(CC) -c user.cpp
clean:
	rm -f *.o
