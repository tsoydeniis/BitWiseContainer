#include <lib/header_files/Array.h>
#include <gtest/gtest.h>
#include <sstream>


TEST(TestSuite, DimTest1) {
    const int32_t dim_cnt = 4;
    const int32_t type_bit_size = 21;
    size_t a[dim_cnt] = {87, 6, 7, 12};
    Array list(dim_cnt, type_bit_size, a);

    for (int arg1 = 0; arg1 < a[0]; ++arg1) {
        for (int arg2 = 0; arg2 < a[1]; ++arg2) {
            for (int arg3 = 0; arg3 < a[2]; ++arg3) {
                for (int arg4 = 0; arg4 < a[3]; ++arg4) {
                    ASSERT_EQ(int(list[arg1][arg2][arg3][arg4]), 0);
                    for (int value = 0; value < type_bit_size * 3; ++value) {
                        list[arg1][arg2][arg3][arg4] = value;
                        ASSERT_EQ(int(list[arg1][arg2][arg3][arg4]), value % (1 << type_bit_size));
                    }
                }
            }
        }
    }
}

TEST(TestSuite, BitSetTest) {
    const int32_t dim_cnt = 1;
    const int32_t type_bit_size = 1;
    size_t a[dim_cnt] = {3000000};
    Array list(dim_cnt, type_bit_size, a);

    for (int i = 0; i < a[0]; ++i) {
        ASSERT_EQ(int(list[i]), 0);
        for (int value = 0; value < type_bit_size * 3; ++value) {
            list[i] = value;
            ASSERT_EQ(int(list[i]), value % (1 << type_bit_size));
        }
    }
}

TEST(TestSuite, MultTest) {
    const int32_t dim_cnt = 4;
    const int32_t type_bit_size = 14;
    const int32_t value = 99;
    size_t a[dim_cnt] = {87, 800, 7, 12};
    Array list(dim_cnt, type_bit_size, a);

    for (int arg1 = 0; arg1 < a[0]; ++arg1) {
        for (int arg2 = 0; arg2 < a[1]; ++arg2) {
            for (int arg3 = 0; arg3 < a[2]; ++arg3) {
                for (int arg4 = 0; arg4 < a[3]; ++arg4) {
                    list[arg1][arg2][arg3][arg4] = arg1 + arg2 + arg3 + arg4;
                }
            }
        }
    }
    list.Mult(value);
    for (int arg1 = 0; arg1 < a[0]; ++arg1) {
        for (int arg2 = 0; arg2 < a[1]; ++arg2) {
            for (int arg3 = 0; arg3 < a[2]; ++arg3) {
                for (int arg4 = 0; arg4 < a[3]; ++arg4) {
                    ASSERT_EQ(int(list[arg1][arg2][arg3][arg4]), (arg1 + arg2 + arg3 + arg4) * value % (1 << type_bit_size));
                }
            }
        }
    }
}

TEST(TestSuite, MakeListTest) {
    const int32_t arg1 = 63;
    const int32_t arg2 = 40;
    const int32_t arg3 = 70;
    Array list = Array::Array::MakeList(arg1, arg2, arg3);
    for (int iter1 = 0; iter1 < arg1; ++iter1) {
        for (int iter2 = 0; iter2 < arg2; ++iter2) {
            for (int iter3 = 0; iter3 < arg3; ++iter3) {
                ASSERT_EQ(int(list[iter1][iter2][iter3]), 0);
                for (int value = 0; value < 17 * 3; ++value) {
                    list[iter1][iter2][iter3] = value;
                    ASSERT_EQ(int(list[iter1][iter2][iter3]), value % (1 << 17));
                }
            }
        }
    }
}

TEST(TestSuite, CopyTest) {
    size_t a[4] = {37, 800, 7, 12};
    size_t b[1] = {8};
    Array list(4, 14, a);
    list = Array(1, 14, b);

    Array other_list = list;
    other_list[0] = 1;
    std::cout << int(other_list[0]) << '\n';
    ASSERT_EQ(int(other_list[0]), 1);
    ASSERT_EQ(int(list[0]), 0);

    ASSERT_THROW(list[b[0]], WrongIndex);
    ASSERT_THROW(list[0][0], BufferError);
}


