

#include <iostream>
#include "locale.h"
#include "settings.h"
#include "game.h"
#include <string>
using namespace std;

void helper();

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");

	Meta meta;

	loadSettings(meta);

	if (argc < 2)
	{
		Game game(false);

		game.printBoard();

		do
		{
			game.handleInput();
			game.printBoard();
		} while (!game.isSolved());

		game.save();

	}

	else if (argc == 2 && argv[1] == string("-backward"))
	{
		Game game(true);

		game.printBoard();

		do
		{
			game.handleInput();
			game.printBoard();
		} while (!game.isSolved());

		game.save();
	}

    else if (argc == 3 && FileExistence(argv[1]) && argv[2] == string("-backward"))
	{
		Game game(argv[1], true);

		game.printBoard();

		do
		{
			game.handleInput();
			game.printBoard();
		} while (!game.isSolved());

		game.save();
	}

	else if (argc == 2 && FileExistence(argv[1]))
	{
		Game game(argv[1], false);

		game.printBoard();

		do
		{
			game.handleInput();
			game.printBoard();
		} while (!game.isSolved());

		game.save();
	}

	else
		helper();
	
	return 0;
}

void helper()
{
	cout << "15 Puzzle Game" << endl;
	cout << "Game history is saved in sessions/" << endl;
	cout << "Game settings are stored in settings/config.txt:" << endl;
	cout << "- 'ctrl >' : arrow keys control" << endl;
	cout << "- 'ctrl wasd' : WASD keys control" << endl;
	cout << "- 'empty file or any other value' : both arrow keys and WASD control" << endl;
	cout << "- 'dim n' : we give the value to the standard field size" << endl;
	cout << "- 'empty file or any other value' : n = 3" << endl << endl;
	cout << "Map creation pseudosyntax:" << endl;
	cout << "'REM' : comment" << endl;
	cout << "# fn (-) : declaration, where '-' is:" << endl;
	cout << "* 'solved' : solved field state" << endl;
	cout << "* 'field' : initial field state" << endl;
	cout << "* 'desc' : map description" << endl;
	cout << "'# endfn' : end of declaration" << endl;
	cout << "'#EMPTY' : empty cell value" << endl;
	cout << "'#CREATOR' : map creator's name" << endl;
}