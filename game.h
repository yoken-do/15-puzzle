#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include "conio.h"
#include "file.h"
#include <iomanip>
#include "field.h"
#include <ctime>

struct Session
{
	vector<Field> fields;
	int count;
	time_t time;
	string status;
};

class Game
{
	Session session;
	Meta meta;
	void handleArrows(int ch, Field& field, size_t& empty_i, size_t& empty_j);
	void handleWASD(int ch, Field& field, size_t& empty_i, size_t& empty_j);
	Field generateSolved();
	Field shuffleField(const Field& solved);
	void backward();
public:
	Game() {};
	Game(const bool& backward_mode);
	Game(const string& map_name, const bool& backward_mode);
	void printBoard() const;
	void handleInput();
	bool isSolved();
	void printHelp();
	void save();
};

#endif