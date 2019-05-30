#pragma once
#include <string>
#include "Position.h"

using std::string;

class Position;

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
	Position* position;
public:
	Piece(sprite, Position*);
	virtual ~Piece();
	virtual bool isBlack() const;
	virtual bool isWhite() const;
	virtual bool isCrowned() const = 0;

	virtual sprite getColor() const;

	virtual operator char() const = 0;
	virtual operator string() const;
	virtual string render() const;
};

