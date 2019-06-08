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

bool Capture::operator==(const Capture& move)
{
	if(this->source != move.source || this->destination != move.destination)
		return false;

	if ((this->subsequent && !move.subsequent) || (!this->subsequent && move.subsequent))
		return false;

	if (!this->subsequent)
		return true;

	Capture* p = this->subsequent;
	Capture* m = move.subsequent;

	while (m && p)
	{
		if (m->source != p->source || m->destination != p->destination)
			return false;
		m = m->subsequent;
		p = p->subsequent;
		if ((p && !m) || (!p && m))
			return false;
	}
	return true;
}

Capture::~Capture()
{
	if (this->subsequent)
		delete this->subsequent;
}

Coord Capture::getEnd() const
{
	Capture* p = this->subsequent;
	if (!p)
		return this->getDestination();
	while (p->subsequent)
		p = p->subsequent;
	return p->getDestination();
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

List<Coord> Capture::getCaptures()
{
	List<Coord> list;

	if (!this->subsequent)
	{
		Coord coord = source;
		if (source.i - destination.i == -2)
			coord = coord + Coord{ 1, 0 };
		else
			coord = coord + Coord{ -1, 0 };
		if (source.j - destination.j == -2)
			coord = coord + Coord{ 0, 1 };
		else
			coord = coord + Coord{ 0, -1 };
		list.insert(coord);
	}
	else
	{
		Coord coord = source;
		if (source.i - destination.i == -2)
			coord = coord + Coord{ 1, 0 };
		else
			coord = coord + Coord{ -1, 0 };
		if (source.j - destination.j == -2)
			coord = coord + Coord{ 0, 1 };
		else
			coord = coord + Coord{ 0, -1 };
		list.insert(coord);
		list.append(this->subsequent->getCaptures());
	}

	return list;
}

int Capture::getNumberCaptures()
{
	if (!this->subsequent)
		return 1;
	return 1 + this->subsequent->getNumberCaptures();
}

Capture::operator bool() const
{
	if (!this->subsequent)
		return this->Move::operator bool();

	if (!(bool(source) && bool(destination)))
		return false;

	Capture* p = this->subsequent;
	while (p)
	{
		if (!(bool(p->source) && bool(p->destination)))
			return false;
		p = p->subsequent;
	}
	return true;
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