
#include "MultyStack.h"
#include <../gtest/gtest.h>

TEST(MultyStack, can_create_multystack_with_default_constructor)
{
    ASSERT_NO_THROW(MultyStack<int> s);
}

TEST(MultyStack, can_create_multystack_with_size_one)
{
    MultyStack<double> s(1, 1);
    //ASSERT_NO_THROW();
}

TEST(MultyStack, can_create_multystack_with_positive_length)
{
    ASSERT_NO_THROW(MultyStack<double> s(10,5));
}

TEST(MultyStack, throws_when_create_multystack_with_zero_size)
{
    ASSERT_ANY_THROW(MultyStack<double> s(0,0));
}

TEST(MultyStack, throws_when_create_multystack_with_negative_length)
{
    ASSERT_ANY_THROW(MultyStack<double> s(-1,5));
}

TEST(MultyStack, can_create_copied_multystack)
{
    MultyStack<int> s(10, 5);
    ASSERT_NO_THROW(MultyStack<int> s1(s));
}


TEST(MultyStack, can_get_size)
{
    MultyStack<int> s(5,3);

    EXPECT_EQ(5, s.GetLength());
}

TEST(MultyStack, can_get_count)
{
    MultyStack<int> s(5, 3);

    EXPECT_EQ(3, s.GetCount());
}

TEST(MultyStack, can_set_and_get_element)
{
    MultyStack<int> s(4,2);
    s.push(6,1);
    EXPECT_EQ(6, s.pull(1));
}

TEST(MultyStack, can_assign_multystack_to_itself)
{
    MultyStack<int> s(5,2);
    ASSERT_NO_THROW(s = s);
    
}

TEST(MultyStack, can_assign_multystacks_of_equal_size)
{
    MultyStack<int> s1(5,2);
    MultyStack<int> s2(5,2);
    for (int i = 0; i < s1.GetCount(); i++)
        s1.push(i,i);
    ASSERT_NO_THROW(s1 = s2);
}

TEST(MultyStack, can_assign_multystacks_of_different_size)
{
    MultyStack<int> s1(10,3);
    MultyStack<int> s2(5,2);
    for (int i = 0; i < s1.GetCount(); i++)
    {
        s1.push(i,i);
    }
    for (int i = 0; i < s2.GetCount(); i++)
    {
        s2.push(i+1,i);
    }
    ASSERT_NO_THROW(s1 = s2);
}
TEST(MultyStack, multystack_is_full)
{
    MultyStack<int>s(1, 1);
    s.push(5, 0);
    EXPECT_EQ(s.IsFull(0), 1);
}

TEST(MultyStack, multystack_is_empty)
{
    MultyStack<int>s(1, 1);
    EXPECT_EQ(s.IsEmpty(0), 1);
}
TEST(MultyStack, can_reorganize_memory_of_multystack)
{
    MultyStack<int>s(6, 3);
    s.push(5, 0);
    s.push(5, 0);
    ASSERT_NO_THROW(s.push(5, 0));
}