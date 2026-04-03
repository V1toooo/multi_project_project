#include <gtest/gtest.h>

#include "../src/doubly_linked_list.hpp"

using bvs::DoublyLinkedList;

TEST(DoublyLinkedListTest, EmptyList) {
    DoublyLinkedList<int> list;
    EXPECT_EQ(list.get_size(), 0);
}

TEST(DoublyLinkedListTest, PushBackOneElement) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    EXPECT_EQ(list.get_size(), 1);
}

TEST(DoublyLinkedListTest, PushBackMultipleElements) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    EXPECT_EQ(list.get_size(), 3);
}

TEST(DoublyLinkedListTest, PushBackCheckOrder) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.has_item(10));
    EXPECT_TRUE(list.has_item(20));
    EXPECT_TRUE(list.has_item(30));
}

TEST(DoublyLinkedListTest, HasItemEmptyList) {
    DoublyLinkedList<int> list;
    EXPECT_FALSE(list.has_item(10));
}

TEST(DoublyLinkedListTest, HasItemExisting) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.has_item(10));
    EXPECT_TRUE(list.has_item(20));
    EXPECT_TRUE(list.has_item(30));
}

TEST(DoublyLinkedListTest, HasItemNonExisting) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    
    EXPECT_FALSE(list.has_item(99));
}

TEST(DoublyLinkedListTest, HasItemWithDuplicates) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(10);
    
    EXPECT_TRUE(list.has_item(10));
    EXPECT_TRUE(list.has_item(20));
}

TEST(DoublyLinkedListTest, RemoveFirstExisting) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.remove_first(20));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_FALSE(list.has_item(20));
}

TEST(DoublyLinkedListTest, RemoveFirstNonExisting) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    
    EXPECT_FALSE(list.remove_first(99));
    EXPECT_EQ(list.get_size(), 2);
}

TEST(DoublyLinkedListTest, RemoveFirstFromEmpty) {
    DoublyLinkedList<int> list;
    EXPECT_FALSE(list.remove_first(10));
    EXPECT_EQ(list.get_size(), 0);
}

TEST(DoublyLinkedListTest, RemoveFirstOnlyFirstOccurrence) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(10);
    list.push_back(30);
    
    EXPECT_TRUE(list.remove_first(10));
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_TRUE(list.has_item(10));
}

TEST(DoublyLinkedListTest, RemoveFirstAndCheckOrder) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    
    list.remove_first(20);
    
    EXPECT_TRUE(list.has_item(10));
    EXPECT_TRUE(list.has_item(30));
    EXPECT_TRUE(list.has_item(40));
    EXPECT_FALSE(list.has_item(20));
}

TEST(DoublyLinkedListTest, RemoveFirstElement) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.remove_first(10));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_FALSE(list.has_item(10));
}

TEST(DoublyLinkedListTest, RemoveLastElement) {
    DoublyLinkedList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    
    EXPECT_TRUE(list.remove_first(30));
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_FALSE(list.has_item(30));
}

TEST(DoublyLinkedListTest, RemoveOnlyElement) {
    DoublyLinkedList<int> list;
    list.push_back(42);
    
    EXPECT_TRUE(list.remove_first(42));
    EXPECT_EQ(list.get_size(), 0);
    EXPECT_FALSE(list.has_item(42));
}

TEST(DoublyLinkedListTest, PrintEmpty) {
    DoublyLinkedList<int> list;
    EXPECT_NO_THROW(list.print());
}

TEST(DoublyLinkedListTest, PrintNonEmpty) {
    DoublyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_NO_THROW(list.print());
}

TEST(DoublyLinkedListTest, MultipleOperations) {
    DoublyLinkedList<int> list;
    
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    EXPECT_EQ(list.get_size(), 3);
    
    list.remove_first(20);
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_FALSE(list.has_item(20));
    
    list.push_back(40);
    EXPECT_EQ(list.get_size(), 3);
    
    EXPECT_TRUE(list.has_item(10));
    EXPECT_TRUE(list.has_item(30));
    EXPECT_TRUE(list.has_item(40));
}

TEST(DoublyLinkedListTest, ManyElements) {
    DoublyLinkedList<int> list;
    for (int i = 0; i < 100; i++) {
        list.push_back(i);
    }
    EXPECT_EQ(list.get_size(), 100);
    
    for (int i = 0; i < 50; i++) {
        EXPECT_TRUE(list.has_item(i));
    }
    
    for (int i = 0; i < 50; i++) {
        list.remove_first(i);
    }
    EXPECT_EQ(list.get_size(), 50);
}

TEST(DoublyLinkedListTest, StringList) {
    DoublyLinkedList<std::string> list;
    list.push_back("hello");
    list.push_back("world");
    
    EXPECT_EQ(list.get_size(), 2);
    EXPECT_TRUE(list.has_item("hello"));
    EXPECT_TRUE(list.has_item("world"));
    EXPECT_FALSE(list.has_item("none"));
    
    list.remove_first("hello");
    EXPECT_EQ(list.get_size(), 1);
    EXPECT_FALSE(list.has_item("hello"));
}

TEST(DoublyLinkedListTest, DoubleList) {
    DoublyLinkedList<double> list;
    list.push_back(1.1);
    list.push_back(2.2);
    list.push_back(3.3);
    
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_TRUE(list.has_item(2.2));
    
    list.remove_first(2.2);
    EXPECT_FALSE(list.has_item(2.2));
    EXPECT_EQ(list.get_size(), 2);
}

TEST(DoublyLinkedListTest, CharList) {
    DoublyLinkedList<char> list;
    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    
    EXPECT_EQ(list.get_size(), 3);
    EXPECT_TRUE(list.has_item('b'));
    
    list.remove_first('b');
    EXPECT_FALSE(list.has_item('b'));
    EXPECT_EQ(list.get_size(), 2);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}