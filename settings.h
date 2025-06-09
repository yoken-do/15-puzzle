#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "field.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;


enum class Control
{
	COMMON,	
	ARROW,
	WASD
};

ostream& operator<<(ostream& out, const Control& control);


extern string session_path;
extern string settings_path;
extern string map_path;

struct Meta
{
	Field current, solved;
	string creator, empty_cell;
	bool backward_mode;
	Control control = Control::COMMON;
	size_t n = 3;
};

void loadSettings(Meta& meta);

#endif