all: a.out
	./a.out <test.txt
a.out : main.o comment.o hashtag.o jeek.o jeekJeek.o notifiction.o user.o
	g++ -g main.o comment.o hashtag.o jeek.o jeekJeek.o notifiction.o user.o
main.o : main.cpp jeekJeek.o
	g++ -c main.cpp
comment.o : comment.cpp user.cpp
	g++ -c comment.cpp
hashtag.o: hashtag.cpp
	g++ -c hashtag.cpp
jeek.o: jeek.cpp user.cpp
	g++ -c jeek.cpp
jeekJeek.o: jeekJeek.cpp user.cpp hashtag.cpp comment.cpp jeek.cpp
	g++ -c jeekJeek.cpp
notifiction.o: notifiction.cpp 
	g++ -c notifiction.cpp
user.o: user.cpp notifiction.cpp
	g++ -c user.cpp
clean:
	rm -f *.o
