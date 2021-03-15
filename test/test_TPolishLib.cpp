#include "../PolishLib/Polish.h"
#include "../gtest/gtest.h"

TEST(TPolish, can_create_polish)
{
  ASSERT_NO_THROW(TPolish P);
}

TEST(TPolish, operation_plus)
{
  TPolish P;
  char* s;

  s = "5+5+5";

  EXPECT_EQ(15, P.Calculate(s));
}

TEST(TPolish, operation_minus)
{
  TPolish P;
  char* s;

  s = "7-5";

  EXPECT_EQ(2, P.Calculate(s));
}

TEST(TPolish, operation_multiply)
{
  TPolish P;
  char* s;

  s = "5*5";

  EXPECT_EQ(25, P.Calculate(s));
}

TEST(TPolish, operation_division)
{
  TPolish P;
  char* s;

  s = "5/5";

  EXPECT_EQ(1, P.Calculate(s));
}

TEST(TPolish, division_by_zero_is_error)
{
  TPolish P;
  char* s;

  s = "5/0";

  ASSERT_ANY_THROW(P.Calculate(s));
}

TEST(TPolish, combined_operations)
{
  TPolish P1;

  char* s1;
  char* s2;
  char* s3;
  char* s4;
  char* s5;

  s1 = "5+5*5";
  s2 = "5*5+5";
  s3 = "(5+5)*5";
  s4 = "(5-5)+(5-5)";
  s5 = "0*0+0-0/1";

  EXPECT_EQ(30, P1.Calculate(s1));
  EXPECT_EQ(30, P1.Calculate(s2));
  EXPECT_EQ(50, P1.Calculate(s3));
  EXPECT_EQ(0, P1.Calculate(s4));
  EXPECT_EQ(0, P1.Calculate(s5));
}