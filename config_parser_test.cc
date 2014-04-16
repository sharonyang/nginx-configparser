#include "gtest/gtest.h"
#include "config_parser.h"

TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
}

TEST(NginxConfigParserTest, ToString) {
  NginxConfigStatement statement;
  statement.tokens_.push_back("foo");
  statement.tokens_.push_back("bar");

  EXPECT_EQ("foo bar;\n", statement.ToString(0));
}

class NginxStringConfigTest: public::testing::Test {
  protected:
  	  bool ParseString(const std::string& config_string) {
        std::stringstream config_stream(config_string);
        return parser_.Parse(&config_stream, &out_config_);
  	  }
  	  NginxConfigParser parser_;
      NginxConfig out_config_;
};

TEST_F(NginxStringConfigTest, SimpleConfig) {
	ASSERT_TRUE(ParseString("price 100;"));
	EXPECT_EQ(1, out_config_.statements_.size());
	EXPECT_EQ(2, out_config_.statements_[0]->tokens_.size());
}

TEST_F(NginxStringConfigTest, SimpleBrokenConfig){
	EXPECT_FALSE(ParseString("price 100"));
}

TEST_F(NginxStringConfigTest, NestedConfig){
	EXPECT_TRUE(ParseString("cake { price 20; }"));
}

TEST_F(NginxStringConfigTest, DoubleNestedConfig){
	EXPECT_TRUE(ParseString("pastry { cake { price 20; } }"));
}