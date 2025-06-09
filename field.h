#ifndef _FIELD_H_
#define _FIELD_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Field
{
private:
	vector<vector<string>> plain;
	
public:
	Field() {};
	Field(const vector<vector<string>>& aplain);
	vector<vector<string>> getPlain() const;
	void swapElem(const string& target, size_t i, size_t j); 
	bool findEmpty(const string& target, size_t& out_i, size_t& out_j);
	friend ostream& operator << (ostream& out, const Field& field);
	bool operator ==(const Field& other) const;
	bool operator !=(const Field& other) const;
	size_t maxLength() const;
};

class FieldError {};
class MoveError {};
class EmptyCellError {};

#endif