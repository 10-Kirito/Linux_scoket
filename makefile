all : chat_server

chat_server : chat_server.cpp
	g++ -Wall -g -o server chat_server.cpp -std=c++11
