#include "Capture.h"

Capture::Capture(Coord source, Coord destination): Move(source, destination)
{
	this->precursor = nullptr;
	this->derivations = new List<Capture>;
	this->captures = new List<Piece*>;
}

Capture::~Capture()
{
	delete this->derivations;
	delete this->captures;
}

void Capture::setPrecursor(Capture* move)
{
	this->precursor = move;
}

Capture* Capture::getPrecursor()
{
	return this->precursor;
}

void Capture::addCapture(Piece* piece)
{
	this->captures->insert(piece);
}

Capture Capture::createDerivation(Coord destination)
{
	Capture aux = Capture(this->destination, destination);
	this->derivations->insert(aux);
	return aux;
}

Capture Capture::searchDerivation(string)
{
	return ;
}

List<Capture>* Capture::getDerivations()
{
	return nullptr;
}

List<Piece*>* Capture::getCaptures()
{
	return nullptr;
}
