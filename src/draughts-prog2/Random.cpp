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
		return string(v2[rand() % v2.getSize()]);
	}
	else
	{
		return string(v1[rand() % v1.getSize()]);
	}
}
