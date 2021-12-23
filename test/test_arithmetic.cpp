// тесты для вычисления арифметических выражений

#include <gtest.h>
#include "arithmetic.h"

TEST(myexpression, can_create_expression)
{
	ASSERT_NO_THROW(myexpression());
}

TEST(myexpression, can_create_expression_from_string)
{
	string s = "1+2";
	ASSERT_NO_THROW(myexpression(s));
}

TEST(myexpression, can_copy_expression)
{
	myexpression exp("1+2");
	ASSERT_NO_THROW(myexpression(exp));
}

TEST(myexpression, can_assign_expression)
{
	myexpression exp("1+2");
	ASSERT_NO_THROW(myexpression exp1 = exp);
}

TEST(myexpression, number_variable_op)
{
	string exp = "2+a";

	ASSERT_EQ(true, number(exp[0]));
	ASSERT_EQ(false, number(exp[1]));
	ASSERT_EQ(false, number(exp[2]));

	ASSERT_EQ(true, letter(exp[2]));
	ASSERT_EQ(false, letter(exp[1]));
	ASSERT_EQ(false, letter(exp[0]));

	ASSERT_EQ(true, op(exp[1]));
	ASSERT_EQ(false, op(exp[0]));
	ASSERT_EQ(false, op(exp[2]));
}

TEST(myexpression, correct_expression)
{
	myexpression exp("2+a");
	ASSERT_EQ(true, exp.correct());

	exp = string("22");
	ASSERT_EQ(true, exp.correct());

	exp = string("-22");
	ASSERT_EQ(true, exp.correct());

	exp = string("22-");
	ASSERT_EQ(false, exp.correct());

	exp = string("+22");
	ASSERT_EQ(false, exp.correct());

	exp = string("2.2");
	ASSERT_EQ(true, exp.correct());

	exp = string(".2");
	ASSERT_EQ(true, exp.correct());

	exp = string("2.");
	ASSERT_EQ(true, exp.correct());

	exp = string("a+.");
	ASSERT_EQ(true, exp.correct());

	exp = string("2.+aB");
	ASSERT_EQ(true, exp.correct());

	exp = string(".+a");
	ASSERT_EQ(true, exp.correct());

	exp = string("(2/a)");
	ASSERT_EQ(true, exp.correct());

	exp = string("(2+a)()");
	ASSERT_EQ(false, exp.correct());

	exp = string("(2+a))");
	ASSERT_EQ(false, exp.correct());

	exp = string("((2+a)");
	ASSERT_EQ(false, exp.correct());

	exp = string("(2+a()");
	ASSERT_EQ(false, exp.correct());

	exp = string("2+Ag@");
	ASSERT_EQ(false, exp.correct());

	exp = string("2+3/");
	ASSERT_EQ(false, exp.correct());

	exp = string("(2+3)/(2-3)");
	ASSERT_EQ(true, exp.correct());

	exp = string("(2+3)/(+2-3)");
	ASSERT_EQ(false, exp.correct());

	exp = string("(2+3)/(-2-3)");
	ASSERT_EQ(true, exp.correct());

	exp = string("2+2+2");
	ASSERT_EQ(true, exp.correct());

	exp = string("2.a");
	ASSERT_EQ(false, exp.correct());

	exp = string("2.2.2");
	ASSERT_EQ(false, exp.correct());

	exp = string("2..2");
	ASSERT_EQ(false, exp.correct());
}

TEST(postfix_entry, can_create)
{
	myexpression exp("3+4*2/(1-5)");
	ASSERT_NO_THROW(postfix_entry pe(exp));
}

TEST(postfix_entry, can_convert)
{
	myexpression exp("3+a*2/(1-5)");
	postfix_entry pe(exp);
	ASSERT_EQ(pe.get_postfix_entry(), "3 a 2 * 1 5 - / +");

	exp = string("2*(1.3+2)");
	pe = exp;
	ASSERT_EQ(pe.get_postfix_entry(), "2 1.3 2 + *");

	exp = string("5*(-3+8)");
	pe = exp;
	ASSERT_EQ(pe.get_postfix_entry(), "5 3 ~ 8 + *");
}

TEST(postfix_entry, can_calculate)
{
	myexpression exp = string("2*(1.3+2)");
	postfix_entry pe = exp;
	ASSERT_EQ(pe.computation(), 6.6);

	exp = string("5*(-3+8)");
	pe = exp;
	ASSERT_EQ(pe.computation(), 25);

	exp = string("5-3");
	pe = exp;
	ASSERT_EQ(pe.computation(), 2);

	exp = string("5/3");
	pe = exp;
	ASSERT_EQ(pe.computation(), 5.0 / 3);

	exp = string("3+2*2/(1-5)");
	pe = exp;
	ASSERT_EQ(pe.computation(), 2);
}