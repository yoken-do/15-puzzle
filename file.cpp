#include "file.h"
#include "with_string.h"

void readFile(ifstream& in, Meta& meta)
{
	string line;
	vector<vector<string>> current_state, solved_state;
	vector<vector<string>>* active = nullptr;

	while (getline(in, line))
	{
		if (line.empty()) 
			{
                continue;
            }

        if (line.find("REM current") == 0) {
            active = &current_state;
            continue;
        }
        else if (line.find("REM solved") == 0) {
            active = &solved_state;
            continue;
        }
        else if (line.find("REM ") == 0) {
            active = nullptr;
            continue;
        }

		else if (line.find("#EMPTY") == 0)
		{
			meta.empty_cell = strip(line.substr(7));
			continue;
		}

		else if (line.find("#CREATOR") == 0)
		{
			meta.creator = strip(line.substr(9));
			continue;
		}

		if (active)
		{
			vector<string> row = split(line, ';');
			active->push_back(row);
			continue;
		}
	}

	meta.current = Field(current_state);
	meta.solved = Field(solved_state);

	size_t i, j;
	if (!meta.solved.findEmpty(meta.empty_cell, i, j) || !meta.current.findEmpty(meta.empty_cell, i, j))
	{
		throw EmptyCellError();
	}

}


bool FileExistence(const string& file)
{

	string filename = file;
	if (filename.find(".txt") == string::npos)
		filename = filename + ".txt";

	string path = map_path + filename;

	ifstream in(path);

	if (in.is_open())
		return true;

	return false;
}