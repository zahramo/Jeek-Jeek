CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp src/jeekJeek.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/server_main.o: server/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/main.cpp -o $(BUILD_DIR)/server_main.o

comment.o : src/comment.cpp src/user.cpp
	g++ -c src/comment.cpp

hashtag.o: src/hashtag.cpp
	g++ -c src/hashtag.cpp

jeek.o: src/jeek.cpp src/user.cpp
	g++ -c src/jeek.cpp

jeekJeek.o: src/jeekJeek.cpp src/user.cpp src/hashtag.cpp src/comment.cpp src/jeek.cpp
	g++ -c src/jeekJeek.cpp

notifiction.o: src/notifiction.cpp 
	g++ -c src/notifiction.cpp

user.o: src/user.cpp src/notifiction.cpp
	g++ -c src/user.cpp


server.out: $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o src/main.o src/comment.o src/hashtag.o src/jeek.o src/jeekJeek.o src/notifiction.o src/user.o
	$(CC) $(CF) $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o -o src/main.o src/comment.o src/hashtag.o src/jeek.o src/jeekJeek.o src/notifiction.o src/user.o -o server.out 





.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
