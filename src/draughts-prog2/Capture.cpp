#include "Capture.h"

Capture::Capture(): Move({ 0,0 }, { 0,0 })
{
	this->precursor = nullptr;
}

Capture::Capture(Coord source, Coord destination, List<Capture> derivations, List<Position*> captures, Capture* precursor): Move(source, destination)
{
	this->precursor = precursor;
	this->derivations = derivations;
	this->captures = captures;
}

Capture::Capture(const Capture& move): Move(move.getSource(), move.getDestination())
{
	this->precursor = move.precursor;
	this->derivations = move.derivations;
	this->captures = move.captures;
}

void Capture::operator=(const Capture& move)
{
	this->source = move.source;
	this->destination = move.destination;
	this->precursor = move.precursor;
	this->derivations = move.derivations;
	this->captures = move.captures;
}

Capture::~Capture()
{
}

Capture* Capture::getPrecursor()
{
	return this->precursor;
}

List<Capture> Capture::getDerivations()
{
	return this->derivations;
}

List<Position*> Capture::getCaptures()
{
	return this->captures;
}
