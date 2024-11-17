#include "tset.h"

#include <gtest.h>

class TSet_Test : public ::testing::Test {
protected:
    void SetUp() {
        set = new TSet(4);

        set1_s4 = new TSet(4);
        set2_s4 = new TSet(4);
        set3_s4 = new TSet(4);

        set2_s6 = new TSet(6);
        set3_s6 = new TSet(6);
    }
    void TearDown() {
    }
    TSet* set;
    TSet* set1_s4;
    TSet* set2_s4;
    TSet* set3_s4;
    TSet* set2_s6;
    TSet* set3_s6;
};

TEST_F(TSet_Test, can_get_max_power_set) {
    EXPECT_EQ(4, set->GetMaxPower());
}

TEST_F(TSet_Test, can_insert_non_existing_element) {
    set->InsElem(3);

    EXPECT_EQ(set->IsMember(3), 1);
}

TEST_F(TSet_Test, can_insert_existing_element) {
    set->InsElem(3);
    set->InsElem(3);

    EXPECT_EQ(set->IsMember(3), 1);
}
TEST_F(TSet_Test, can_delete_non_existing_element) {
    set->DelElem(3);

    EXPECT_EQ(set->IsMember(3), 0);
}

TEST_F(TSet_Test, can_delete_existing_element) {

    set->InsElem(3);
    EXPECT_GT(set->IsMember(3), 0);

    set->DelElem(3);
    EXPECT_EQ(set->IsMember(3), 0);
}

TEST_F(TSet_Test, compare_two_sets_of_non_equal_sizes) {
    EXPECT_EQ(1, set1_s4 != set2_s6);
}

TEST_F(TSet_Test, compare_two_equal_sets) {
    set1_s4->InsElem(1);
    set1_s4->InsElem(3);
    set2_s4->InsElem(1);
    set2_s4->InsElem(3);

    EXPECT_EQ(*set1_s4, *set2_s4);
}

TEST_F(TSet_Test, compare_two_non_equal_sets) {
    set1_s4->InsElem(1);
    set1_s4->InsElem(3);
    set2_s4->InsElem(1);
    set2_s4->InsElem(2);

    EXPECT_EQ(1, set1_s4 != set2_s4);
}

TEST_F(TSet_Test, can_assign_set_of_equal_size) {
    set1_s4->InsElem(1);
    set1_s4->InsElem(3);
    *set2_s4 = *set1_s4;

    EXPECT_EQ(*set1_s4, *set2_s4);
}

TEST_F(TSet_Test, can_assign_set_of_greater_size) {
    set2_s6->InsElem(1);
    set2_s6->InsElem(3);
    *set1_s4 = *set2_s6;

    EXPECT_EQ(*set1_s4, *set2_s6);
}

TEST_F(TSet_Test, can_assign_set_of_less_size) {
    set1_s4->InsElem(1);
    set1_s4->InsElem(3);
    *set2_s6 = *set1_s4;

    EXPECT_EQ(*set1_s4, *set2_s6);
}

TEST_F(TSet_Test, can_insert_non_existing_element_using_plus_operator) {
    const int k = 3;
    *set1_s4 = *set1_s4 + k;

    EXPECT_EQ(1, set1_s4->IsMember(k));
}

TEST_F(TSet_Test, throws_when_insert_non_existing_element_out_of_range_using_plus_operator) {
    const int k = 6;

    ASSERT_ANY_THROW(*set1_s4 = *set + k);
}

TEST_F(TSet_Test, can_insert_existing_element_using_plus_operator) {
    const int k = 3;
    *set1_s4 = *set + k;

    EXPECT_EQ(1, set->IsMember(k));
}

TEST_F(TSet_Test, check_size_of_the_combination_of_two_sets_of_equal_size) {
    // set = {1, 2, 3}
    set->InsElem(1);
    set->InsElem(2);
    set->InsElem(3);
    // set1_s4 = {0, 1, 2}
    set1_s4->InsElem(0);
    set1_s4->InsElem(1);
    set1_s4->InsElem(2);
    *set2_s4 = *set1_s4 + *set;

    EXPECT_EQ(4, set2_s4->GetMaxPower());
}

TEST_F(TSet_Test, can_combine_two_sets_of_equal_size) {
    // set1_s4 = {1, 2}
    set1_s4->InsElem(1);
    set1_s4->InsElem(2);
    // set2_s4 = {0, 1}
    set2_s4->InsElem(0);
    set2_s4->InsElem(1);
    *set3_s4 = *set1_s4 + *set2_s4;
    // set3_s4 = {0, 1, 2}
    set->InsElem(0);
    set->InsElem(1);
    set->InsElem(2);

    EXPECT_EQ(*set3_s4, *set);
}

TEST_F(TSet_Test, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size) {
    // set1_s4 = {1, 2, 3}
    set1_s4->InsElem(1);
    set1_s4->InsElem(2);
    set1_s4->InsElem(3);
    // set2_s6 = {0, 1, 2}
    set2_s6->InsElem(0);
    set2_s6->InsElem(1);
    set2_s6->InsElem(2);
    *set = *set2_s6 + *set1_s4;

    EXPECT_EQ(6, set->GetMaxPower());
}

TEST_F(TSet_Test, can_combine_two_sets_of_non_equal_size) {
    // set1 = {1, 2, 3}
    set1_s4->InsElem(1);
    set1_s4->InsElem(2);
    set1_s4->InsElem(3);
    // set2 = {0, 1, 2}
    set2_s6->InsElem(0);
    set2_s6->InsElem(1);
    set2_s6->InsElem(2);
    *set = *set1_s4 + *set2_s6;
    // expSet = {0, 1, 2, 3}
    set3_s6->InsElem(0);
    set3_s6->InsElem(1);
    set3_s6->InsElem(2);
    set3_s6->InsElem(3);

    EXPECT_EQ(*set, *set3_s6);
}

TEST_F(TSet_Test, can_intersect_two_sets_of_equal_size) {
    // set1 = {1, 2, 3}
    set1_s4->InsElem(1);
    set1_s4->InsElem(2);
    set1_s4->InsElem(3);
    // set2 = {0, 1, 2}
    set2_s4->InsElem(0);
    set2_s4->InsElem(1);
    set2_s4->InsElem(2);
    *set3_s4 = *set1_s4 * *set2_s4;
    // expSet = {1, 2}
    set->InsElem(1);
    set->InsElem(2);

    EXPECT_EQ(*set, *set3_s4);
}

TEST_F(TSet_Test, can_intersect_two_sets_of_non_equal_size) {
    // set1 = {1, 2, 3}
    set1_s4->InsElem(1);
    set1_s4->InsElem(2);
    set1_s4->InsElem(3);
    // set2 = {0, 1, 2, 3, 5}
    set2_s6->InsElem(0);
    set2_s6->InsElem(1);
    set2_s6->InsElem(2);
    set2_s6->InsElem(3);
    set2_s6->InsElem(5);

    // expSet = {1, 2, 3}
    set3_s6->InsElem(1);
    set3_s6->InsElem(2);
    set3_s6->InsElem(3);

    EXPECT_EQ(*set3_s6, *set1_s4 * *set2_s6);
}

TEST_F(TSet_Test, check_negation_operator) {
    // set = {1, 3}
    set->InsElem(1);
    set->InsElem(3);
    *set1_s4 = ~*set;
    // set2_s4 = {0, 2}
    set2_s4->InsElem(0);    
    set2_s4->InsElem(2);

    EXPECT_EQ(*set2_s4, *set1_s4);
}
TEST_F(TSet_Test, throws_when_negative_index_in_IsMember) {
  ASSERT_ANY_THROW(set->IsMember(-3));
}
TEST_F(TSet_Test, throws_when_negative_index_in_InsElem) {
  ASSERT_ANY_THROW(set->InsElem(-3));
}
TEST_F(TSet_Test, throws_when_negative_index_in_DelElem) {
  ASSERT_ANY_THROW(set->DelElem(-3));
}
TEST_F(TSet_Test, correct_IsMember) {
    set->InsElem(2);

    EXPECT_EQ(set->IsMember(2), 1);
}
TEST_F(TSet_Test, correct_InsElem) {
    set->InsElem(2);
    set->DelElem(2);

    EXPECT_EQ(set->IsMember(2), 0);
}
TEST_F(TSet_Test, correct_DelElem) {
    set->DelElem(2);

    EXPECT_EQ(set->IsMember(2), 0);
}
TEST_F(TSet_Test, associativity_operator_and) {
    set1_s4->InsElem(1);
    set1_s4->InsElem(3);
    set->InsElem(1);
    set->InsElem(2);

  EXPECT_EQ(*set * *set1_s4, *set1_s4 * *set);
}
TEST_F(TSet_Test, associativity_operator_or) {
    set1_s4->InsElem(1);
    set1_s4->InsElem(3);
    set->InsElem(1);
    set->InsElem(2);

    EXPECT_EQ(*set + *set1_s4, *set1_s4 + *set);
}
TEST_F(TSet_Test, associativity_operator_equality) {
    set1_s4->InsElem(1);
    set1_s4->InsElem(3);
    set->InsElem(1);
    set->InsElem(2);

    EXPECT_EQ(*set == *set1_s4, *set1_s4 == *set);
}
TEST_F(TSet_Test, associativity_operator_inequality) {
    set1_s4->InsElem(1);
    set1_s4->InsElem(3);
    set->InsElem(1);
    set->InsElem(2);

    EXPECT_EQ(*set != *set1_s4, *set1_s4 != *set);
}
TEST_F(TSet_Test, correct_operator_negative_and_operator_and) {
    set->InsElem(2);
    *set1_s4 = ~*set;

    EXPECT_EQ(*set1_s4 + 2, ~*set3_s4);
}