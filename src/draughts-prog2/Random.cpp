#include "Random.h"

Random::Random(MovementController* controller): Strategy(controller)
{
	srand(time(0));
}

string Random::getMovement() const
{
	auto v1 = controller->getCaptures(color);
	if (v1.empty())
	{
		auto v2 = controller->getMovements(color);
		if (v2.empty())
			return "00 00";
		return string(v2[rand() % v2.getSize()]);
	}
	else
	{
		return string(v1[rand() % v1.getSize()]);
	}
}

string Random::toString() const
{
	return "random";
}
