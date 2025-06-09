#include "field.h"

vector<vector<string>> Field::getPlain() const { 
	return plain; 
}

Field::Field(const vector<vector<string>>& aplain)
{
	if (aplain.empty() || aplain[0].empty())
		throw FieldError();

	for (const auto& item : aplain)
	{
		if (aplain.size() != item.size() || item.empty())
			throw FieldError();
	}

	plain = aplain;
}

void Field::swapElem(const string& target, size_t i, size_t j)
{

	if (i >= plain.size() || j >= plain[i].size())
		return;

	size_t empty_i, empty_j;
	findEmpty(target, empty_i, empty_j);


	bool adj = (i == empty_i && abs((int)j - (int)empty_j) == 1) || (j == empty_j && abs((int)i - (int)empty_i) == 1);

	if (!adj)
		throw MoveError();

	string temp = plain[i][j];
	plain[i][j] = plain[empty_i][empty_j];
	plain[empty_i][empty_j] = temp;

}

bool Field::findEmpty(const string& target, size_t& out_i, size_t& out_j)
{

	for (size_t i = 0; i < plain.size(); i++)
	{
		for (size_t j = 0; j < plain[i].size(); j++)
		{
			if (plain[i][j] == target)
			{
				out_i = i;
				out_j = j;
				return true;
			}
		}
	}

	return false;
}


ostream& operator << (ostream& out, const Field& field)
{

	size_t length = field.maxLength();

	vector<vector<string>> plain = field.getPlain();
	for (size_t i = 0; i < plain.size(); i++)
	{
		for (size_t j = 0; j < plain[i].size(); j++)
		{
			out << left << setw(length) << plain[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

bool Field::operator ==(const Field& other) const
{
	vector<vector<string>> aplain = other.getPlain();

	if (plain.size() != aplain.size())
		return false;

	for (size_t i = 0; i < plain.size(); i++)
	{
		for (size_t j = 0; j < plain[i].size(); j++)
			if (plain[i][j] != aplain[i][j])
				return false;
	}
	return true;

}

bool Field::operator !=(const Field& other) const
{
	return !(*this == other);
}

size_t Field::maxLength() const
{
	size_t m = 0;
	for (const vector<string>& row : plain)
	{
		for (const string& elem : row)
		{
			m = elem.length() > m ? elem.length() : m;
		}
	}

	return m;

}