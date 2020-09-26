#include "units.h"
#include <iostream>

void listUnitAttributes(Unit& unit1,Unit& unit2){	
	std::cout << unit1.getName() << ":HP:" << unit1.getHp() << ",DMG:" << unit1.getDamage() << std::endl;
	std::cout << unit2.getName() << ":HP:" <<unit2.getHp() << ",DMG:" <<unit2.getDamage() << std::endl;
}
void damageLog(Unit& unit1, Unit& unit2) {
		unit1.dealDamageTo(unit2);
		std::cout << unit1.getName() << "->" << unit2.getName() << std::endl;
}

void gamePlay(Unit& unit1, Unit& unit2){
	listUnitAttributes(unit1, unit2);
	while(unit1.getHp()!=0 && unit2.getHp()!=0){
		//Az első unit támad
		damageLog(unit1, unit2);
		listUnitAttributes(unit1, unit2);
		if(unit2.getHp() == 0){
			std::cout << unit2.getName() << " died." << unit1.getName() << " wins." << std::endl;
			break;
		}
		//A második unit támad
		damageLog(unit2, unit1);
		listUnitAttributes(unit1, unit2);
		if (unit1.getHp() == 0){
			std::cout << unit1.getName() << " died." << unit2.getName() << " wins." << std::endl;
		}
	}
}
int main(int argc,char* argv[])
{
	if (argc !=3){
		//Tesztelésre
		/*Unit unit1("Maple",150,10),unit2("Sally",45,30);
		gamePlay(unit1, unit2);*/
		std::cout << "A proper input example: ./a.out Maple 150 10 Sally 45 30" << std::endl;
	}
	else{
	Unit unit1,unit2;
	Unit::parseUnit(argv[1], unit1);
	Unit::parseUnit(argv[2], unit2);
	gamePlay(unit1, unit2);
	}
	std::cin.get();
}