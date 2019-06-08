#pragma once
#include <string>

using std::string;
using std::ostream;
using std::to_string;

struct Weight
{
	int attack{0};
	int defense{0};

	operator string() const;

	void operator =(const Weight&);
	bool operator ==(const Weight&);
	bool operator !=(const Weight&);

	Weight operator +(const Weight&);
	Weight operator -(const Weight&);
	void operator +=(const Weight&);
	void operator -=(const Weight&);
};

