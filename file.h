#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "settings.h"

using namespace std;

class FileReadError {};

void readFile(ifstream& in, Meta& meta);

bool FileExistence(const string& file);

#endif