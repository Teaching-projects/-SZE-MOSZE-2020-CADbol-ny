#include "../JSON.h"
#include "../units.h"
#include "../Hero.h"
#include "../Monster.h"
#include "../Game.h"
#include "../PreparedGame.h"
#include "../MarkedMap.h"
#include "../Map.h"
#include "../Renderer.h"
#include <sstream>
#include <gtest/gtest.h>

TEST(ParserTest,defaultfileparse)
{
	std::string expected_name="Fallen";
	int expected_hp=4;
	int expected_dmg=2;
	float expected_attackcooldown=1.6f;
	JSON output=JSON::parseFromFile("../Fallen.json");
    ASSERT_EQ(output.get<std::string>("name"),expected_name);
	ASSERT_EQ(output.get<int>("health_points"),expected_hp);
	ASSERT_EQ(output.get<int>("physical_damage"),expected_dmg);
	ASSERT_EQ(output.get<float>("attack_cooldown"),expected_attackcooldown);

}
TEST(ParserTest,istreamparse)
{
	std::string expected_name="Zombie";
	int expected_hp=10;
	int expected_dmg=1;
	float expected_attackcooldown=2.8f;
	std::ifstream input;
	input.open("../Zombie.json");
	JSON output=JSON::parseFromIstream(input);
	input.close();
    ASSERT_EQ(output.get<std::string>("name"),expected_name);
	ASSERT_EQ(output.get<int>("health_points"),expected_hp);
	ASSERT_EQ(output.get<int>("physical_damage"),expected_dmg);
	ASSERT_EQ(output.get<float>("attack_cooldown"),expected_attackcooldown);
}
TEST(ParserTest,stringparse)
{
	std::string expected_name="Maple";
	int expected_hp=150;
	int expected_dmg=10;
	std::string input="{\n \"name\" : \"Maple\",\n \"hp\"  150,\n \"dmg\": 10 \n}";
	JSON output=JSON::parseFromString(input);
    ASSERT_EQ(output.get<std::string>("name"),expected_name);
	ASSERT_EQ(output.get<int>("hp"),expected_hp);
	ASSERT_EQ(output.get<int>("dmg"),expected_dmg);
}
TEST(ParserTest,additionalWhitespaceParse)
{
	std::string expected_name="Maple";
	int expected_hp=150;
	int expected_dmg=10;
	std::string input="{\n \"name\" :      \"Maple\",\n \"hp\"  150,\n \"dmg\": 10 \n}";
	JSON output=JSON::parseFromString(input);
    ASSERT_EQ(output.get<std::string>("name"),expected_name);
	ASSERT_EQ(output.get<int>("hp"),expected_hp);
	ASSERT_EQ(output.get<int>("dmg"),expected_dmg);
}
TEST(ParserTest,changedKeyOrderParse)
{
	std::string expected_name="Maple";
	int expected_hp=150;
	int expected_dmg=10;
	std::string input="{\n \"hp\" : 150,\n \"dmg\" : 10,\n \"name\": \"Maple\" \n}";
	JSON output=JSON::parseFromString(input);
    ASSERT_EQ(output.get<std::string>("name"),expected_name);
	ASSERT_EQ(output.get<int>("hp"),expected_hp);
	ASSERT_EQ(output.get<int>("dmg"),expected_dmg);
}
TEST(ParserTest,arrayParse1){
	JSON::list expected_list={"Fallen.json","Fallen.json","Zombie.json","Fallen.json","Fallen.json","Zombie.json","Fallen.json","Blood_Raven.json"};
	JSON output=JSON::parseFromFile("../scenario1.json");
	std::string expected_hero="Dark_Wanderer.json";
	ASSERT_EQ(output.get<std::string>("hero"),expected_hero);
	ASSERT_EQ(output.get<JSON::list>("monsters"),expected_list);
}
TEST(ParserTest,arrayParse2){
	JSON::list expected_list={"Blood_Raven.json"};
	JSON output=JSON::parseFromFile("../scenario2.json");
	std::string expected_hero="Dark_Wanderer.json";
	ASSERT_EQ(output.get<std::string>("hero"),expected_hero);
	ASSERT_EQ(output.get<JSON::list>("monsters"),expected_list);
}
TEST(UnitTest,getterAndMonsterparserTest)
{
	Monster unit = Monster::parse("../Zombie.json");
	EXPECT_EQ(unit.getName(),"Zombie");
	EXPECT_EQ(unit.getHealthPoints(),10);
	EXPECT_EQ(unit.getFDamage(),1);
	EXPECT_FLOAT_EQ(unit.getAttackCoolDown(),2.8f);
}
TEST(UnitTest,getterAndHeroparserTest)
{
	Hero unit = Hero::parse("../Dark_Wanderer.json");
	EXPECT_EQ(unit.getName(),"Prince Aidan of Khanduras");
	EXPECT_EQ(unit.getHealthPoints(),30);
	EXPECT_EQ(unit.getFDamage(),3);
	EXPECT_EQ(unit.getMDamage(),2);
	EXPECT_FLOAT_EQ(unit.getAttackCoolDown(),1.1f);
	EXPECT_EQ(unit.getDefense(),1);
	EXPECT_EQ(unit.getLightRadius(),2);
}
TEST(UnitTest,FightTest1)
{
	Hero unit1 = Hero::parse("../Dark_Wanderer.json");
	Monster unit2 =Monster::parse("../Fallen.json");
	unit1.fightTilDeath(unit2);
	EXPECT_EQ(unit1.getHealthPoints(),29);
}
TEST(UnitTest,FightTest2)
{
	Hero unit1 =Hero::parse("../Dark_Wanderer.json");
	Monster unit2 = Monster::parse("../Zombie.json");
	unit1.fightTilDeath(unit2);
	EXPECT_EQ(unit2.getHealthPoints(),0);
}
TEST(UnitTest,levelUpTest)
{
	Hero unit1 = Hero::parse("../Dark_Wanderer.json");
	std::list<Monster> monsters;
	for(int i=0;i<6;i++){
		monsters.push_back(Monster::parse("../Fallen.json"));
	}
	for(auto monster:monsters){
		unit1.fightTilDeath(monster);
	}
	EXPECT_EQ(unit1.getLevel(),2);
}
TEST(UnitTest,dealPhysicalDamageToTest1)
{
	Hero unit1 = Hero::parse("../Dark_Wanderer.json");
	Monster unit2 =Monster::parse("../Fallen.json");
	unit1.dealPhysicalDamageTo(unit2);
	unit2.dealPhysicalDamageTo(unit1);
	EXPECT_EQ(unit2.getHealthPoints(),2);
	EXPECT_EQ(unit1.getHealthPoints(),29);
}
TEST(UnitTest,dealPhysicalDamageToTest2)
{
	Hero unit1 = Hero::parse("../Dark_Wanderer.json");
	Monster unit2 =Monster::parse("../Zombie.json");
	unit1.dealPhysicalDamageTo(unit2);
	unit2.dealPhysicalDamageTo(unit1);
	EXPECT_EQ(unit2.getHealthPoints(),9);
	EXPECT_EQ(unit1.getHealthPoints(),30);
}
TEST(UnitTest,dealMagicalDamageToTest1)
{
	Hero unit1 = Hero::parse("../Dark_Wanderer.json");
	Monster unit2 =Monster::parse("../Fallen.json");
	unit1.dealMagicalDamageTo(unit2);
	unit2.dealMagicalDamageTo(unit1);
	EXPECT_EQ(unit2.getHealthPoints(),2);
	EXPECT_EQ(unit1.getHealthPoints(),28);
}
TEST(UnitTest,dealMagicalDamageToTest2)
{
	Hero unit1 = Hero::parse("../Dark_Wanderer.json");
	Monster unit2 =Monster::parse("../Zombie.json");
	unit1.dealMagicalDamageTo(unit2);
	unit2.dealMagicalDamageTo(unit1);
	EXPECT_EQ(unit2.getHealthPoints(),8);
	EXPECT_EQ(unit1.getHealthPoints(),29);
}
TEST(MapTests,MapInitTest)
{
	std::vector<std::string> expected_map={"##############\r","#   #  ####  #\r","# ####  ##  # \r","#   #  ##  #  \r","### # ##  #   \r","#        #    \r","#### ####     "};
	Map output_map("../map.txt");
	EXPECT_EQ(expected_map,output_map.getMap());
}
TEST(MapTests,MapGetTestWall)
{
	int expected=1;
	Map output("../map.txt");
	EXPECT_EQ(output.get(0,0),expected);
}
TEST(MapTests,MapGetTestFree)
{
	int expected=0;
	Map output("../map.txt");
	EXPECT_EQ(output.get(1,1),expected);
}
TEST(MapTests,MarkedMapInitTest)
{
	MarkedMap output_map("../markedmap.txt");
	std::vector<std::string> expected_map={"##############\r","# H #  ####  #\r","# ####32##  # \r","# 12# 2##  #  \r","###1# ##  #   \r","#     1   #   \r","#########     "};
	EXPECT_EQ(expected_map,output_map.getMap());
}
TEST(MapTests,MapGetTestHero)
{
	MarkedMap output("../markedmap.txt");
	EXPECT_EQ('H',output.getMapField(1,2));
}
TEST(MapTests,MapGetTestMonster)
{
	MarkedMap output("../markedmap.txt");
	EXPECT_EQ('1',output.getMapField(3,2));
}
TEST(GameTests,heroIsPresent1){
	Game gameplay("../map.txt");
	Hero hero(Hero::parse("../Dark_Wanderer.json"));
	gameplay.putHero(hero,1,2);
	EXPECT_EQ(true,gameplay.heroIsPresent());
}
TEST(GameTests,heroIsPresent2){
	Game gameplay("../map.txt");
	EXPECT_EQ(false,gameplay.heroIsPresent());
}
TEST(GameTests,getMapSize){
	Game gameplay("../map.txt");
	EXPECT_EQ(gameplay.getMap().getMapSize(),7);
}
TEST(GameTests,getMapRowSize){
	Game gameplay("../map.txt");
	EXPECT_EQ(gameplay.getGameMapRowSize(0),15);
}
TEST(ExceptionTests,JSONexceptionTest1)
{
	std::string expected="Couldn't open file,the file doesn't exist.\n";
	testing::internal::CaptureStdout();
	try {
		Unit unit1 = Unit::parse("unit/uni2.json");
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what()<< std::endl;
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected,output);
}
TEST(ExceptionTests,JSONexceptionTest2)
{
	std::string expected="Couldn't open file,the file doesn't exist.\n";
	testing::internal::CaptureStdout();
	try {
		Unit unit1 = Unit::parse("units/unit22.json");
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what()<< std::endl;
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected,output);
}
TEST(ExceptionTests,OccupiedExceptionTest)
{
	std::string expected="The given field is not free.\n";
	Game gameplay("../map.txt");
	Hero hero(Hero::parse("../Dark_Wanderer.json"));
	testing::internal::CaptureStdout();
	try {
		gameplay.putHero(hero,0,0);
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what()<< std::endl;
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected,output);
}
TEST(ExceptionTests,AlreadyHasHeroExceptionTest)
{
	std::string expected="There is already a hero on the map, can't place another one.\n";
	Game gameplay("../map.txt");
	Hero hero1(Hero::parse("../Dark_Wanderer.json"));
	gameplay.putHero(hero1,1,2);
	Hero hero2(Hero::parse("../Dark_Wanderer.json"));
	testing::internal::CaptureStdout();
	try {
		gameplay.putHero(hero2,1,3);
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what()<< std::endl;
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected,output);
}
TEST(ExceptionTests,AlreadyHasUnitsExceptionTest)
{
	std::string expected="The map already has units, can't change it.\n";
	Game gameplay("../map.txt");
	Map map("../map.txt");
	Hero hero(Hero::parse("../Dark_Wanderer.json"));
	gameplay.putHero(hero,1,3);
	testing::internal::CaptureStdout();
	try {
		gameplay.setMap(map);
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what()<< std::endl;
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected,output);
}
TEST(ExceptionTests,NotInitializedExceptionTest)
{
	std::string expected="The map is not initialized or there is no hero on it.\n";
	Game gameplay("../map.txt");
	testing::internal::CaptureStdout();
	try {
		gameplay.run();
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what()<< std::endl;
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected,output);
}
TEST(ExceptionTests,WrongIndexExceptionTest1)
{
	std::string expected="Index was out of range. Must be non-negative and less than the size of the column.\n";
	Map map("../map.txt");
	testing::internal::CaptureStdout();
	try {
		map.get(30,8);
	}
	catch (std::logic_error& e)
	{
		std::cout << e.what()<< std::endl;
	}
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(expected,output);
}
TEST(ExceptionTests,WrongIndexExceptionTest2)
{
	std::string expected="Index was out of range. Must be non-negative and less than the size of the row.\n";
	Map map("../map.txt");
	testing::internal::CaptureStdout();
	try {
		map.get(6,18);
	}
	catch (std::logic_error& e)
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

