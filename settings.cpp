#include "settings.h"

string session_path = "sessions/";
string settings_path = "settings/config.txt";
string map_path = "maps/";

ostream& operator<<(ostream& out, const Control& control)
{
	switch (control)
	{
	case Control::COMMON:
		out << "COMMON";
		break;
	case Control::ARROW:
		out << "ARROW";
		break;
	case Control::WASD:
		out << "WASD";
		break;
	default:
		out << "COMMON";
	}
	return out;
}

void loadSettings(Meta& meta)
{
	ifstream in(settings_path);

	if (!in.is_open())
		return;

	string line;

	while (getline(in, line))
	{
		if (line.empty() || line.find("REM") == 0)
			continue;

        else if (line.find("ctrl") != string::npos)
		{
			if (line.find("wasd") != string::npos)
				meta.control = Control::WASD;
			
			else if (line.find(">") != string::npos)
				meta.control = Control::ARROW;
			
			else
				break;
		}


		else if (line.find("dim") != string::npos)
		{
			for (char c : line.substr(3))
			{
				if (c == ' ') continue;

				if (c >= '0' && c <= '9')
				{
					meta.n = (c - '0');
					break;
				}
				else
					break;
			}
		}
	}

}