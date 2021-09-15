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

$(BUILD_DIR)/server_main.o: server/main.cpp
	$(CC) $(CF) -c server/main.cpp -o $(BUILD_DIR)/server_main.o

$(BUILD_DIR)/requestHandlers.o: server/requestHandlers.cpp  server/requestHandlers.hpp
	$(CC) $(CF) -c server/requestHandlers.cpp -o $(BUILD_DIR)/requestHandlers.o

$(BUILD_DIR)/comment.o: src/comment.cpp src/comment.hpp
	$(CC) $(CF) -c src/comment.cpp -o $(BUILD_DIR)/comment.o

$(BUILD_DIR)/hashtag.o: src/hashtag.cpp src/hashtag.hpp
	$(CC) $(CF) -c src/hashtag.cpp -o $(BUILD_DIR)/hashtag.o

$(BUILD_DIR)/jeek.o: src/jeek.cpp src/jeek.hpp
	$(CC) $(CF) -c src/jeek.cpp -o $(BUILD_DIR)/jeek.o

$(BUILD_DIR)/jeekJeek.o: src/jeekJeek.cpp src/jeekJeek.hpp
	$(CC) $(CF) -c src/jeekJeek.cpp -o $(BUILD_DIR)/jeekJeek.o

$(BUILD_DIR)/notifiction.o: src/notifiction.cpp src/notifiction.hpp
	$(CC) $(CF) -c src/notifiction.cpp -o $(BUILD_DIR)/notifiction.o

$(BUILD_DIR)/user.o: src/user.cpp src/user.hpp
	$(CC) $(CF) -c src/user.cpp -o $(BUILD_DIR)/user.o


server.out: $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/hashtag.o $(BUILD_DIR)/jeek.o $(BUILD_DIR)/jeekJeek.o $(BUILD_DIR)/notifiction.o $(BUILD_DIR)/user.o $(BUILD_DIR)/requestHandlers.o
	$(CC) $(CF) $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/hashtag.o $(BUILD_DIR)/jeek.o $(BUILD_DIR)/jeekJeek.o $(BUILD_DIR)/notifiction.o $(BUILD_DIR)/user.o $(BUILD_DIR)/requestHandlers.o -o server.out 


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
