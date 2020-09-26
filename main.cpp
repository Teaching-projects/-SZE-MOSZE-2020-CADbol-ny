#include "units.h"

void gamePlay(Unit& unit1, Unit& unit2){
	while(unit1.getHp()!=0 && unit2.getHp()!=0){
		//Az első unit támad
		unit1.dealDamageTo(unit2);
		if(unit2.getHp() == 0){
			std::cout << unit1.getName() << " wins.Remaining HP:" <<unit1.getHp() <<'.' << std::endl;
			break;
		}
		//A második unit támad
		unit2.dealDamageTo(unit1);
		if (unit1.getHp() == 0){
			std::cout << unit2.getName() << " wins.Remaining HP:" << unit2.getHp() << '.' << std::endl;
		}
	}
}
int main(int argc,char* argv[])
{
	if (argc !=3){
		//Tesztelésre
		/*Unit unit1, unit2;
		Unit::parseUnit("units/unit3.txt", unit1);
		Unit::parseUnit("units/unit2.txt", unit2);
		gamePlay(unit1, unit2);*/
		std::cout << "A proper input example: ./a.out file1 file2" << std::endl;
	}
	else{
		try {
			Unit unit1, unit2;
			Unit::parseUnit(argv[1], unit1);
			Unit::parseUnit(argv[2], unit2);
			gamePlay(unit1, unit2);
		}
		catch (int x)
		{
			std::cout << "The file doesn't exist,error number:" << x << std::endl;
		}
	}
	std::cin.get();
}