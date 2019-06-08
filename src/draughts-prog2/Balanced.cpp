#include "Balanced.h"

Balanced::Balanced(MovementController* controller) : Strategy(controller)
{
}

string Balanced::getMovement() const
{
	List<Capture> v1 = controller->getCaptures(color);
	if (v1.empty())
	{
		List<Move> v2 = controller->getMovements(color);
		return string(getBest(v2));
	}
	else
	{
		return string(getBest(v1));
	}
}

Move Balanced::getBest(List<Move> list) const
{
	if (list.empty())
		return Move();
	auto v = controller->weightMovements(list);

	Move best = list[0];
	Weight weight = v[0];

	for (size_t i = 0; i < list.getSize(); i++)
	{
		if (v[i].defense + v[i].attack > weight.defense + weight.attack)
		{
			best = list[i];
			weight = v[i];
		}
	}
	return best;
}

Capture Balanced::getBest(List<Capture> list) const
{
	if (list.empty())
		return Capture();
	auto v = controller->weightMovements(list);

	Capture best = list[0];
	Weight weight = v[0];

	for (size_t i = 0; i < list.getSize(); i++)
	{
		if (v[i].defense + v[i].attack > weight.defense + weight.attack)
		{
			best = list[i];
			weight = v[i];
		}
	}
	return best;
}

string Balanced::toString() const
{
	return "balanced";
}
