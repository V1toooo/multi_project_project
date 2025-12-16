#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "sort.hpp"

TEST(ShellSortTest, SortDescendingArray) {
    std::vector<int> actual = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    srt::sort::shellsort(actual);
    
    ASSERT_EQ(expected.size(), actual.size())
        << "Разные размеры ожидаемого и отсортированного массивов";
    
    for (size_t i = 0; i < actual.size(); i++) {
        ASSERT_EQ(expected[i], actual[i])
            << "Массивы отличаются в элементе с индексом " << i;
    }
}

TEST(ShellSortTest, SortRandomArray) {
    std::vector<int> actual = {5, 2, 8, 1, 9, 3};
    std::vector<int> expected = {1, 2, 3, 5, 8, 9};
    
    srt::sort::shellsort(actual);
    
    ASSERT_THAT(actual, ::testing::ContainerEq(expected));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}