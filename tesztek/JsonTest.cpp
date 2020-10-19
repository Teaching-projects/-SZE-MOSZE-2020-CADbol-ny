#include "../jsonparser.h"
#include <sstream>
#include <gtest/gtest.h>

TEST(MultTest,fileparse)
{
	std::map<std::string,std::string> expected;
	expected["name"]="Maple";
	expected["hp"]="150";
	expected["dmg"]="10";
	std::map<std::string,std::string> output=JsonParser::ParseFile("units/unit1.json");
    EXPECT_EQ(output,expected);
}
TEST(MultTest,istreamparse)
{
	std::map<std::string,std::string> expected;
	expected["name"]="Maple";
	expected["hp"]="150";
	expected["dmg"]="10";
	std::ifstream input;
	input.open("units/unit1.json");
	std::map<std::string,std::string> output=JsonParser::ParseIstream(input);
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
	std::map<std::string,std::string> output=JsonParser::ParseString(input);
    EXPECT_EQ(output,expected);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
