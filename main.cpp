#include "units.h"
#include <iostream>
/**
 *  This function calls the game with 2 units who fight each other.
 * 
 * 
 * 
*/
void gamePlay(Unit* unit1, Unit* unit2) {
	Unit::Fight(unit1, unit2);
	if (unit2->getHp() == 0) {
		std::cout << unit1->getName() << " wins.Remaining HP:" << unit1->getHp() << '.' << std::endl; 
	}
	if (unit1->getHp() == 0) {
		std::cout << unit2->getName() << " wins.Remaining HP:" << unit2->getHp() << '.' << std::endl; 
	}
}
/**
 * This is the main function.
 * 
 * It checks the parameters, and if everything is good it runs the gameplay. At the end the memory is freed.
 * 
 * 
 * 
*/

int main(int argc,char* argv[])
{
	if (argc !=3){
		//Tesztelésre
		//gamePlay(unit1,unit2);
		std::cout << "A proper input example: ./a.out file1 file2" << std::endl;
	}
	else{
		try {
			Unit* unit1 = Unit::parseUnit(argv[1]);
			Unit* unit2 = Unit::parseUnit(argv[2]);
			gamePlay(unit1,unit2);
			delete unit1;
			delete unit2;
		}
		catch (int x)
		{
			std::cout << "The file doesn't exist,error number:" << x << std::endl;
		}
	}
	std::cin.get();
}