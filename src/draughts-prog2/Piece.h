#pragma once
#include <string>

using std::string;

class Piece
{
public:
	enum sprite
	{
		black,
		white
	};
private:
	sprite color;
public:
	Piece(sprite);
	virtual ~Piece();
	virtual bool black() const;
	virtual bool white() const;
	virtual bool crowned() const = 0;

	virtual operator char() const = 0;
	virtual operator string() const;
	virtual string render() const;
};

