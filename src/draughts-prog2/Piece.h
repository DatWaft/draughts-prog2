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
	virtual bool isBlack() const;
	virtual bool isWhite() const;
	virtual bool isCrowned() const = 0;

	virtual operator char() const = 0;
	virtual operator string() const;
	virtual string render() const;
};

