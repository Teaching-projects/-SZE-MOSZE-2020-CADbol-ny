#include "../JSON.h"
#include "../units.h"
#include <sstream>
#include <gtest/gtest.h>

TEST(MultTest,defaultfileparse)
{
	std::map<std::string,std::string> expected;
	expected["name"]="Maple";
	expected["hp"]="150";
	expected["dmg"]="10";
	expected["attackcooldown"]="6";
	JSON output=JSON::parseFromFile("units/unit1.json");
    	EXPECT_EQ(output,expected);
}
TEST(MultTest,istreamparse)
{
	std::map<std::string,std::string> expected;
	expected["name"]="Sally";
	expected["hp"]="45";
	expected["dmg"]="30";
	expected["attackcooldown"]="2";
	std::ifstream input;
	input.open("units/unit1.json");
	JSON output=JSON::parseFromIstream(input);
	input.close();
    	EXPECT_EQ(output,expected);
}
TEST(MultTest,stringparse)
{
	std::map<std::string,std::string> expected;
	expected["name"]="Maple";
	expected["hp"]="150";
	expected["dmg"]="10";
	std::string input="{\n name : \"Maple\",\n \"hp\"  150,\n \"dmg\": 10 \n}";
	JSON output=JSON::parseFromString(input);
    	EXPECT_EQ(output,expected);
}
TEST(MultTest,additionalWhitespaceParse)
{
	std::map<std::string,std::string> expected;
	expected["name"]="Maple";
	expected["hp"]="150";
	expected["dmg"]="10";
	std::string input="{\n name :      \"Maple\",\n \"hp\"  150,\n \"dmg\": 10 \n}";
	std::map<std::string,std::string> output=JsonParser::ParseString(input);
    EXPECT_EQ(output,expected);
}
TEST(MultTest,changedKeyOrderParse)
{
	std::map<std::string,std::string> expected;
	expected["name"]="Maple";
	expected["hp"]="150";
	expected["dmg"]="10";
	std::string input="{\n \"hp\" : 150,\n \"dmg\" : 10,\n \"name\": \"Maple\" \n}";
	std::map<std::string,std::string> output=JsonParser::ParseString(input);
    EXPECT_EQ(output,expected);
}
TEST(MultTest,GameplayTest1)
{
	std::string expected ="Sally wins.Remaining HP:50.\n";
	Unit* unit1 = Unit::parseUnit("units/unit1.json");
	Unit* unit2 = Unit::parseUnit("units/unit2.json");
	Unit::Fight(unit1, unit2);
	testing::internal::CaptureStdout();
	if (unit2->getHp() == 0) {
		std::cout << unit1->getName() << " wins.Remaining HP:" << unit1->getHp() << '.' << std::endl; 
	}
	if (unit1->getHp() == 0) {
		std::cout << unit2->getName() << " wins.Remaining HP:" << unit2->getHp() << '.' << std::endl; 
	}
	std::string output = testing::internal::GetCapturedStdout();
	delete unit1;
	delete unit2;
	EXPECT_EQ(output,expected);
}
TEST(MultTest,GameplayTest2)
{
	std::string expected ="Elfie wins.Remaining HP:90.\n";
	Unit* unit1 = Unit::parseUnit("units/unit1.json");
	Unit* unit2 = Unit::parseUnit("units/unit3.json");
	Unit::Fight(unit1, unit2);
	testing::internal::CaptureStdout();
	if (unit2->getHp() == 0) {
		std::cout << unit1->getName() << " wins.Remaining HP:" << unit1->getHp() << '.' << std::endl; 
	}
	if (unit1->getHp() == 0) {
		std::cout << unit2->getName() << " wins.Remaining HP:" << unit2->getHp() << '.' << std::endl; 
	}
	std::string output = testing::internal::GetCapturedStdout();
	delete unit1;
	delete unit2;
	EXPECT_EQ(output,expected);
}
TEST(MultTest,getterAndUnitparserTest1)
{
	Unit* unit = Unit::parseUnit("units/unit1.json");
	EXPECT_EQ(unit->getName(),"Maple");
	EXPECT_EQ(unit->getHp(),150);
	EXPECT_EQ(unit->getDamage(),10);
	EXPECT_FLOAT_EQ(unit->getAttackspeed(),6.0f);
}
TEST(MultTest,getterAndUnitparserTest2)
{
	Unit* unit = Unit::parseUnit("units/unit2.json");
	EXPECT_EQ(unit->getName(),"Sally");
	EXPECT_EQ(unit->getHp(),45);
	EXPECT_EQ(unit->getDamage(),30);
	EXPECT_FLOAT_EQ(unit->getAttackspeed(),2.0f);
}
TEST(MultTest,FightTest1)
{
	Unit* unit1 = Unit::parseUnit("units/unit1.json");
	Unit* unit2 = Unit::parseUnit("units/unit2.json");
	Unit::Fight(unit1,unit2);
	EXPECT_EQ(unit1->getHp(),0);
}
TEST(MultTest,FightTest2)
{
	Unit* unit1 = Unit::parseUnit("units/unit2.json");
	Unit* unit2 = Unit::parseUnit("units/unit1.json");
	Unit::Fight(unit1,unit2);
	EXPECT_EQ(unit2->getHp(),0);
}
TEST(MultTest,dealDamageToTest1)
{
	Unit* unit1 = Unit::parseUnit("units/unit1.json");
	Unit* unit2 = Unit::parseUnit("units/unit2.json");
	unit1->dealDamageTo(*unit2);
	EXPECT_EQ(unit2->getHp(),35);
}
TEST(MultTest,dealDamageToTest2)
{
	Unit* unit1 = Unit::parseUnit("units/unit2.json");
	Unit* unit2 = Unit::parseUnit("units/unit1.json");
	unit1->dealDamageTo(*unit2);
	EXPECT_EQ(unit2->getHp(),120);
}
TEST(MultTest,exceptionTest1)
{
	std::string expected="Couldn't open file,the file doesn't exist.\n";
	testing::internal::CaptureStdout();
	try {
		Unit* unit1 = Unit::parseUnit("unit/uni2.json");
		delete unit1;
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what()<< std::endl;
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected,output);
}
TEST(MultTest,exceptionTest2)
{
	std::string expected="Couldn't open file,the file doesn't exist.\n";
	testing::internal::CaptureStdout();
	try {
		Unit* unit1 = Unit::parseUnit("units/unit22.json");
		delete unit1;
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what()<< std::endl;
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected,output);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

