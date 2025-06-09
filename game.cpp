#include "game.h"


Game::Game(const bool& backward_mode)
{
	loadSettings(meta);
	meta.solved = generateSolved();
	meta.current = shuffleField(meta.solved);
	meta.creator = "yoken-do";
	session.count = 0;
	meta.backward_mode = backward_mode;
	session.fields.push_back(meta.current);
	session.time = time(nullptr);
}


Game::Game(const string& map_name, const bool& backward_mode)
{
	loadSettings(meta);

	string filename = map_name;

	if (map_name.find(".txt") == string::npos) 
        filename = map_name + ".txt";

	string path = map_path + filename;

	ifstream in(path);

	if (!in.is_open())
	{
		throw FileReadError();
	}
	readFile(in, meta);
	meta.backward_mode = backward_mode;
	session.count = 0;
	session.fields.push_back(meta.current);
	session.time = time(nullptr);
}


Field Game::shuffleField(const Field& solved)
{

	Field shuff = solved;

	size_t size = shuff.getPlain().size();

	size_t empty_i = size - 1, empty_j = size - 1;

	for (int i = 0; i < size * 20; i++)
	{
		int direct = rand() % 4;

		switch (direct)
		{
		case 0:
			if (empty_i > 0)
			{
			shuff.swapElem(meta.empty_cell, empty_i - 1, empty_j);
			empty_i--;
			}
			break;
		case 1:
			if (empty_i < size - 1)
			{
				shuff.swapElem(meta.empty_cell, empty_i + 1, empty_j);
				empty_i++;
			}
			break;
		case 2:
			if (empty_j > 0)
			{
				shuff.swapElem(meta.empty_cell, empty_i, empty_j - 1);
				empty_j--;
			}
			break;
		case 3:
			if (empty_j < size - 1)
			{
				shuff.swapElem(meta.empty_cell, empty_i, empty_j + 1);
				empty_j++;
			}
			break;
		default:
			break;
		}
	}
	return shuff;

}

Field Game::generateSolved()
{

	size_t size = meta.n;
	vector<vector<string>> plain(size, vector<string>(size));
	int counter = 1;

	if (size <= 3)
		meta.empty_cell = "_";
	else
		meta.empty_cell = "__";

	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i == size - 1 && j == size - 1)
				plain[i][j] = meta.empty_cell;

			else if (counter <= 9 && size > 3)
				plain[i][j] = "_" + to_string(counter++);

			else if (counter <= 9 && size <= 3)
				plain[i][j] = to_string(counter++);

			else
				plain[i][j] = to_string(counter++);
		}
	}

	return Field(plain);
}

void Game::backward()
{
	if (session.fields.size() > 1)
	{
		session.fields.pop_back();
		meta.current = session.fields[session.fields.size() - 1];
		if (session.count < 0)
			session.count = 0;
		else
			session.count -= 1;
	}
}

void Game::save()
{
	string filename = "session_" + to_string(time(nullptr)) + ".txt";
	string path = session_path + filename;
	ofstream out(path);

	if (!out.is_open())
	{
		FileReadError();
		return;
	}

	session.time = time(nullptr) - session.time;

	if (isSolved())
		session.status = "true";
	else
		session.status = "false";

	string mode = meta.backward_mode ? "backward" : "standart";

	int i = 0;
	out << "Number of moves: " << session.count << endl;
	out << "Game time: " << session.time << " seconds" << endl;
	out << "Mode: " << mode << endl;
	out << "Game is over: " << session.status << endl;

	for (const auto& plain : session.fields)
	{
		out << "#CURRENT_STATE " << i++ << endl;
		for (const auto& row : plain.getPlain())
		{
			for (const auto& cell : row)
			{
				out << cell << "; ";
			}
			out << endl;
		}
		out << "====================" << endl;
	}
	out.close();
	system("cls");
	cout << "Game is over!" << endl;
	cout << "Status: " << session.status << endl;
	cout << "Mode: " << mode << endl;
	cout << "Game time: " << session.time << endl;
	cout << "Number of moves: " << session.count << endl;
	cout << "Game saved: " << filename;

}




void Game::printBoard() const
{
	system("cls");
	cout << "Number of moves: " << session.count << endl;
	cout << meta.current;
}

bool Game::isSolved()
{
	return meta.current == meta.solved;
}

void Game::handleArrows(int ch, Field& field, size_t& empty_i, size_t& empty_j)
{
	if (ch == 0 || ch == 224)
	{
		ch = _getch();
		switch (ch)
		{
		case 72:
			field.swapElem(meta.empty_cell, empty_i - 1, empty_j);
			break;
		case 80:
			field.swapElem(meta.empty_cell, empty_i + 1, empty_j);
			break;
		case 75:
			field.swapElem(meta.empty_cell, empty_i, empty_j - 1);
			break;
		case 77:
			field.swapElem(meta.empty_cell, empty_i, empty_j + 1);
			break;
		default:
			return;
		}
	}
}

void Game::handleWASD(int ch, Field& field, size_t& empty_i, size_t& empty_j)
{
	switch (tolower(ch))
	{
	case 'w':
		field.swapElem(meta.empty_cell, empty_i - 1, empty_j);
		break;
	case 's':
		field.swapElem(meta.empty_cell, empty_i + 1, empty_j);
		break;
	case 'a':
		field.swapElem(meta.empty_cell, empty_i, empty_j - 1);
		break;
	case 'd':
		field.swapElem(meta.empty_cell, empty_i, empty_j + 1);
		break;
	default:
		return;
	}
}

void Game::printHelp()
{
	string mode = meta.backward_mode ? "backward" : "standart";
	system("cls");
	cout << "=== 15 PUZZLE ===" << endl;
	cout << "Control: " << meta.control << endl;
	cout << "ESC - help" << endl;
	cout << "Game mode: " << mode << endl;
	cout << "N - back moves (backward mode)" << endl;
	cout << "Q - exit" << endl;
	cout << "----------------" << endl;
	cout << "MAP:" << endl;
	cout << "Creator: " << meta.creator << endl;
	cout << "Empty Cell: " << meta.empty_cell << endl;
	cout << "Solved State: " << endl << meta.solved << endl;
	cout << "=================" << endl;
	cout << "Click for exit";
	_getch();
}

void Game::handleInput()
{
	int ch = _getch();


	if (ch == 'q' || ch == 'Q')
	{
		save();
		exit(0);
	}

	else if ((ch == 'N' || ch == 'n') && meta.backward_mode)
	{
		backward();
	}

	else if (ch == 27)
	{
		printHelp();
		return;
	}

	size_t empty_i, empty_j;

	meta.current.findEmpty(meta.empty_cell, empty_i, empty_j);


	Field new_field = meta.current;


	switch (meta.control)
	{

	case Control::ARROW:
		handleArrows(ch, new_field, empty_i, empty_j);
		break;
	case Control::WASD:
		handleWASD(ch, new_field, empty_i, empty_j);
		break;
	case Control::COMMON:
		handleArrows(ch, new_field, empty_i, empty_j);
		handleWASD(ch, new_field, empty_i, empty_j);
		break;
	default:
		break;
	}

	if (meta.current != new_field)
	{
		session.fields.push_back(new_field);
		session.count++;
		meta.current = new_field;
	}
}