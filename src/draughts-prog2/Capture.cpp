#include "Capture.h"

Capture::Capture()
{
	this->precursor = nullptr;
	this->subsequent = nullptr;
}

Capture::Capture(Coord source, Coord destination): Move(source, destination)
{
	this->precursor = nullptr;
	this->subsequent = nullptr;
}

Capture::Capture(Coord source, Coord destination, Capture* precursor): Move(source, destination)
{
	this->precursor = precursor;
	this->subsequent = nullptr;
}

Capture::Capture(const Capture& move)
{
	this->source = move.source;
	this->destination = move.destination;
	this->precursor = move.precursor;
	this->subsequent = move.subsequent;
}

void Capture::operator=(const Capture& move)
{
	this->source = move.source;
	this->destination = move.destination;
	this->precursor = move.precursor;
	this->subsequent = move.subsequent;
}

Capture::~Capture()
{
	if (this->subsequent)
		delete this->subsequent;
}

Capture* Capture::getPrecursor()
{
	return precursor;
}

Capture* Capture::getSubsequent()
{
	return subsequent;
}

Capture* Capture::createSubsequent(Coord destination)
{
	if (!this->subsequent)
		this->subsequent = new Capture(this->destination, destination, this);
	return this->subsequent;
}

Capture::operator string()
{
	if (!this->subsequent)
		return string(this->source) + " " + string(this->destination);
	return string(this->source) + " " + string(*this->subsequent);
}
