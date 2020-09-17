#include "games.h"

bool Fight::endGame(Unit& unit1, Unit& unit2) {
	return unit1.getHp() != 0 && unit2.getHp() != 0;
}
