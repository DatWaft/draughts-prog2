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
	if (move.precursor)
		throw Exception("No se deben crear copias directas de movimientos que no sean la raíz");
	this->precursor = nullptr;
	if (move.subsequent)
	{
		this->subsequent = new Capture(this->destination, move.subsequent->destination, this);
		Capture* p = this->subsequent;
		Capture* m = move.subsequent;

		m = m->subsequent;
		while (m)
		{
			p = p->createSubsequent(m->destination);
			m = m->subsequent;
		}
	}
	else
		this->subsequent = nullptr;
}

void Capture::operator=(const Capture& move)
{
	this->source = move.source;
	this->destination = move.destination;
	if (move.precursor)
		throw Exception("No se deben crear copias directas de movimientos que no sean la raíz");
	this->precursor = nullptr;
	if (move.subsequent)
	{
		this->subsequent = new Capture(this->destination, move.subsequent->destination, this);
		Capture* p = this->subsequent;
		Capture* m = move.subsequent;

		m = m->subsequent;
		while (m)
		{
			p = p->createSubsequent(m->destination);
			m = m->subsequent;
		}
	}
	else
		this->subsequent = nullptr;
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

Capture* Capture::createSubsequent(Capture move)
{
	if (!this->subsequent)
		this->subsequent = new Capture(move);
	return this->subsequent;
}

Capture::operator string() const
{
	if (!this->subsequent)
		return string(this->source) + " " + string(this->destination);
	return string(this->source) + " " + string(*this->subsequent);
}

ostream& operator<<(ostream& out, const Capture& move)
{
	out << string(move);
	return out;
}