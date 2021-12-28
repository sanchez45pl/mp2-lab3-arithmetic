// тесты для стека

#include "stack.h"
#include <gtest.h>

TEST(stack, can_create_stack)
{
	ASSERT_NO_THROW(stack <int> (10));
}

TEST(stack, can_empty)
{
	stack <int> s(0);
	ASSERT_EQ(s.empty(), true);
}

TEST(stack, can_push)
{
	stack <int> s(10);
	ASSERT_NO_THROW(s.push(1));
}

TEST(stack, push_change_size)
{
	stack <int> s(10);
	s.push(1);
	ASSERT_EQ(s.empty(), false);
}


TEST(stack, can_return_size)
{
	stack <int> s(10);
	s.push(1);
	s.push(2);
	ASSERT_EQ(s.stack_size(), 2);
}



TEST(stack, cant_push_in_MAX_SIZE)
{
	stack <int> s(50000);
	for (size_t i = 0; i < MAX_STACK_CAPACITY; i++)
	{
		s.push(i);
	}
	ASSERT_ANY_THROW(s.push(1));
}

TEST(stack, can_top)
{
	stack <int> s(2);
	s.push(1);
	ASSERT_EQ(s.top(), 1);
}

TEST(stack, cant_top_in_empty_stack)
{
	stack <int> s(2);
	ASSERT_ANY_THROW(s.top());
}

TEST(stack, cant_pop_in_empty_stack)
{
	stack <int> s(2);
	ASSERT_ANY_THROW(s.pop());
}

TEST(stack, can_pop)
{
	stack <int> s(2);
	s.push(1);
	ASSERT_EQ(s.pop(), 1);
}

TEST(stack, pop_change_size)
{
	stack <int> s(2);
	s.push(1);
	s.pop();
	ASSERT_EQ(s.stack_size(), 0);
}

TEST(stack, can_clear)
{
	stack <int> s(2);
	s.push(1);
	s.clear();
	ASSERT_EQ(s.stack_size(), 0);
}