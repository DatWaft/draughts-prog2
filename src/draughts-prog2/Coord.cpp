#include "Coord.h"

ostream& operator<<(ostream& out, const Coord& coord)
{
	out << "[" << coord.i << "," << coord.j << "]";
	return out;
}