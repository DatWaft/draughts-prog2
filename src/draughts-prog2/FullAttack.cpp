#include "FullAttack.h"

FullAttack::FullAttack(MovementController* controller) : Strategy(controller)
{
}

string FullAttack::getMovement() const
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

Move FullAttack::getBest(List<Move> list) const
{
	if (list.empty())
		return Move();
	auto v = controller->weightMovements(list);

	Move best = list[0];
	Weight weight = v[0];

	for (size_t i = 0; i < list.getSize(); i++)
	{
		if (v[i].attack > weight.attack)
		{
			best = list[i];
			weight = v[i];
		}
	}
	return best;
}

Capture FullAttack::getBest(List<Capture> list) const
{
	if (list.empty())
		return Capture();
	auto v = controller->weightMovements(list);

	Capture best = list[0];
	Weight weight = v[0];

	for (size_t i = 0; i < list.getSize(); i++)
	{
		if (v[i].attack > weight.attack)
		{
			best = list[i];
			weight = v[i];
		}
	}
	return best;
}
