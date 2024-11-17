#include "tbitfield.h"

#include <gtest.h>

class TBitField_Test : public ::testing::Test {
protected:
    void SetUp() {
        bf = new TBitField(5);
        
        // bf = 01101
        bf->SetBit(1);
        bf->SetBit(2);
        bf->SetBit(4);

        bf1_s5 = new TBitField(5);
        bf2_s5 = new TBitField(5);
        bf3_s5 = new TBitField(5);
        bf1_s3 = new TBitField(3);

        // bf1_s3 = 011
        bf1_s3->SetBit(1);
        bf1_s3->SetBit(2);

        // bf1_s5 = 01110
        bf1_s5->SetBit(1);
        bf1_s5->SetBit(2);
        bf1_s5->SetBit(3);

        // bf2_s5 = 01010
        bf2_s5->SetBit(1);
        bf2_s5->SetBit(3);
        
        // bf3 = 01000
        bf3_s5->SetBit(1);
    }
    void SetUpNewLenght(int lenn) {
        bf = new TBitField(lenn);
    }
    void TearDown() {
        delete bf;
        delete bf1_s5;
        delete bf2_s5;
        delete bf3_s5;
        delete bf1_s3;
    }
    TBitField* bf;
    TBitField* bf1_s5;
    TBitField* bf2_s5;
    TBitField* bf3_s5;
    TBitField* bf1_s3;
};


TEST_F(TBitField_Test, can_create_bitfield_with_positive_length) {
    ASSERT_NO_THROW(this->SetUpNewLenght(13));
}
TEST_F(TBitField_Test, can_get_length) {
    EXPECT_EQ(bf->GetLength(), 5);
}
TEST_F(TBitField_Test, can_set_bit) {
    EXPECT_EQ(0, bf->GetBit(3));
}
TEST_F(TBitField_Test, can_clear_bit){
    bf->ClrBit(1);
    EXPECT_EQ(0, bf->GetBit(1));
}
TEST_F(TBitField_Test, new_bitfield_is_set_to_zero) {
    this->SetUpNewLenght(100);

    int sum = 0;
    for (int i = 0; i < this->bf->GetLength(); i++)
    sum += bf->GetBit(i);

    EXPECT_EQ(0, sum);
}
TEST_F(TBitField_Test, throws_when_create_bitfield_with_negative_length) {
     ASSERT_ANY_THROW(this->SetUpNewLenght(-13));
}
TEST_F(TBitField_Test, throws_when_set_bit_with_negative_index) {
     ASSERT_ANY_THROW(bf->SetBit(-3));
}
TEST_F(TBitField_Test, throws_when_set_bit_with_too_large_index) {
     ASSERT_ANY_THROW(bf->SetBit(11));
}
TEST_F(TBitField_Test, throws_when_get_bit_with_negative_index) {
    ASSERT_ANY_THROW(bf->GetBit(-3));
}
TEST_F(TBitField_Test, throws_when_get_bit_with_too_large_index) {
    ASSERT_ANY_THROW(bf->GetBit(11));
}
TEST_F(TBitField_Test, throws_when_clear_bit_with_negative_index) {
    ASSERT_ANY_THROW(bf->ClrBit(-3));
}
TEST_F(TBitField_Test, throws_when_clear_bit_with_too_large_index) {
    ASSERT_ANY_THROW(bf->ClrBit(11));
}

TEST_F(TBitField_Test, can_assign_bitfields_of_equal_size) {
    *bf2_s5 = *bf1_s5;

    EXPECT_EQ(1, bf2_s5->GetBit(2));
}

TEST_F(TBitField_Test, assign_operator_changes_bitfield_size) {
    *bf1_s5 = *bf1_s5;

    EXPECT_EQ(5, bf1_s5->GetLength());
}

TEST_F(TBitField_Test, can_assign_bitfields_of_non_equal_size) {
    *bf1_s3 = *bf1_s5;

    EXPECT_EQ(5, bf1_s3->GetLength());
}

TEST_F(TBitField_Test, compare_equal_bitfields_of_equal_size) {
    *bf2_s5 = *bf1_s5;

    EXPECT_EQ(*bf1_s5, *bf2_s5);
}
TEST_F(TBitField_Test, or_operator_applied_to_bitfields_of_equal_size) {
    EXPECT_EQ(*bf1_s5, *(bf1_s5) | *(bf2_s5));
}

TEST_F(TBitField_Test, or_operator_applied_to_bitfields_of_non_equal_size) {
    EXPECT_EQ(*bf1_s5, *bf1_s3 | *bf2_s5);
}

TEST_F(TBitField_Test, and_operator_applied_to_bitfields_of_equal_size) {
    EXPECT_EQ(*bf2_s5, *bf1_s5 & *bf2_s5);
}

TEST_F(TBitField_Test, and_operator_applied_to_bitfields_of_non_equal_size) {
    EXPECT_EQ(*bf3_s5, *bf1_s3 & *bf2_s5);
}

TEST_F(TBitField_Test, can_invert_bitfield) {
    *bf1_s5 = ~(*bf);

    EXPECT_NE(*bf, *bf1_s5);
}


TEST_F(TBitField_Test, invert_plus_and_operator_on_different_size_bitfield) {
    *bf1_s3 = ~(*bf1_s3);
    
    bf3_s5->ClrBit(1);
    EXPECT_EQ(*bf1_s5 & *bf1_s3, *bf3_s5);
}

TEST_F(TBitField_Test, can_invert_many_random_bits_bitfield) {
    *bf = ~(*bf2_s5);

    bf->ClrBit(0);
    bf->ClrBit(2);
    bf->ClrBit(4);
    bf3_s5->ClrBit(1);

    EXPECT_EQ(*bf, *bf3_s5);
}

TEST_F(TBitField_Test, bitfields_with_different_bits_are_not_equal_) {
    EXPECT_NE(*bf3_s5, *bf1_s5);
}

TEST_F(TBitField_Test, doulbe_negative) {
    *bf = ~(*bf2_s5);

	EXPECT_EQ(~(*bf), *bf2_s5);
}

TEST_F(TBitField_Test, associativity_operator_and) {

  EXPECT_EQ(*bf2_s5 & *bf1_s5, *bf1_s5 & *bf2_s5);
}

TEST_F(TBitField_Test, associativity_operator_or) {
  EXPECT_EQ(*bf2_s5 | *bf1_s5, *bf1_s5 | *bf2_s5);
}

TEST_F(TBitField_Test, associativity_operator_equality) {
  EXPECT_EQ(*bf2_s5 == *bf1_s5, *bf1_s5 == *bf2_s5);
}

TEST_F(TBitField_Test, associativity_operator_inequality) {
  EXPECT_EQ(*bf2_s5 != *bf1_s5, *bf1_s5 != *bf2_s5);
}
