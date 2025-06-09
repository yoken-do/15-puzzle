#include "with_string.h"


string strip(const string& str) {
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first) return "";
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}


vector<string> split(const string& target, const char& del)
{


	vector<string> str;
	string temp = "";


	for (char c : target)
	{

		if (c == del && !temp.empty())
		{

			str.push_back(strip(temp));
			temp.clear();
		}
		else
			temp += c;
	}


	if (!temp.empty())
		str.push_back(strip(temp));
	return str;

}