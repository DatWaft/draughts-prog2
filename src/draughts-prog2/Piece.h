#pragma once
#include <string>
#include "Coord.h"

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
	Coord position;
public:
	Piece(sprite, Coord);
	virtual ~Piece();
	virtual bool isBlack() const;
	virtual bool isWhite() const;
	virtual bool isCrowned() const = 0;

	void setPosition(Coord);
	virtual sprite getColor() const;
	Coord getPosition() const;

	virtual operator char() const = 0;
	virtual operator string() const;
	virtual string render() const;
};

