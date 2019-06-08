#include "Weight.h"

Weight::operator string() const
{
	return "Weight{attack: " + to_string(this->attack) + ", defense: " + to_string(this->defense) + "}";
}

void Weight::operator=(const Weight& object)
{
	this->attack = object.attack;
	this->defense = object.defense;
}

bool Weight::operator==(const Weight& object)
{
	return this->attack == object.attack && this->defense == object.defense;
}

bool Weight::operator!=(const Weight& object)
{
	return !(*this == object);
}

Weight Weight::operator+(const Weight& object)
{
	return { this->attack + object.attack, this->defense + object.defense };
}

Weight Weight::operator-(const Weight& object)
{
	return { this->attack - object.attack, this->defense - object.defense };
}

void Weight::operator+=(const Weight& object)
{
	*this = *this + object;
}

void Weight::operator-=(const Weight& object)
{
	*this = *this - object;
}

ostream& operator<<(ostream& out, const Weight& object)
{
	out << string(object);
	return out;
}