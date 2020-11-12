#include "../JSON.h"
#include "../units.h"
#include "../Hero.h"
#include "../Monster.h"
#include <sstream>
#include <gtest/gtest.h>

TEST(MultTest,defaultfileparse)
{
	std::string expected_name="Fallen";
	int expected_hp=4;
	int expected_dmg=2;
	float expected_attackcooldown=1.6f;
	JSON output=JSON::parseFromFile("../Fallen.json");
    ASSERT_EQ(output.get<std::string>("name"),expected_name);
	ASSERT_EQ(output.get<int>("health_points"),expected_hp);
	ASSERT_EQ(output.get<int>("damage"),expected_dmg);
	ASSERT_EQ(output.get<float>("attack_cooldown"),expected_attackcooldown);

}
TEST(MultTest,istreamparse)
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
	ASSERT_EQ(output.get<int>("damage"),expected_dmg);
	ASSERT_EQ(output.get<float>("attack_cooldown"),expected_attackcooldown);
}
TEST(MultTest,stringparse)
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
TEST(MultTest,additionalWhitespaceParse)
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
TEST(MultTest,changedKeyOrderParse)
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
TEST(MultTest,getterAndMonserparserTest1)
{
	Monster unit = Monster::parse("../Zombie.json");
	EXPECT_EQ(unit.getName(),"Zombie");
	EXPECT_EQ(unit.getHealthPoints(),10);
	EXPECT_EQ(unit.getDamage(),1);
	EXPECT_FLOAT_EQ(unit.getAttackCoolDown(),2.8f);
}
TEST(MultTest,getterAndHeroparserTest2)
{
	Hero unit = Hero::parse("../Dark_Wanderer.json");
	EXPECT_EQ(unit.getName(),"Prince Aidan of Khanduras");
	EXPECT_EQ(unit.getHealthPoints(),30);
	EXPECT_EQ(unit.getDamage(),3);
	EXPECT_FLOAT_EQ(unit.getAttackCoolDown(),1.1f);
}
TEST(MultTest,FightTest1)
{
	Hero unit1 = Hero::parse("../Dark_Wanderer.json");
	Monster unit2 =Monster::parse("../Fallen.json");
	unit1.fightTilDeath(unit2);
	EXPECT_EQ(unit1.getHealthPoints(),28);
}
TEST(MultTest,FightTest2)
{
	Hero unit1 =Hero::parse("../Dark_Wanderer.json");
	Monster unit2 = Monster::parse("../Zombie.json");
	unit1.fightTilDeath(unit2);
	EXPECT_EQ(unit2.getHealthPoints(),0);
}
TEST(MultTest,dealDamageToTest1)
{
	Hero unit1 = Hero::parse("../Dark_Wanderer.json");
	Monster unit2 =Monster::parse("../Fallen.json");
	unit1.dealDamageTo(unit2);
	EXPECT_EQ(unit2.getHealthPoints(),1);
}
TEST(MultTest,dealDamageToTest2)
{
	Hero unit1 = Hero::parse("../Dark_Wanderer.json");
	Monster unit2 =Monster::parse("../Fallen.json");
	unit1.dealDamageTo(unit2);
	EXPECT_EQ(unit2.getHealthPoints(),1);
}
TEST(MultTest,exceptionTest1)
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
TEST(MultTest,exceptionTest2)
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

