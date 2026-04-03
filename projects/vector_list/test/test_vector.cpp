#include <gtest/gtest.h>

#include "../src/vector.hpp"

using bvs::Vector;

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_EQ(v.get_size(), 0);
}

TEST(VectorTest, MultipleVectorsDifferentTypes) {
    Vector<int> vi;
    Vector<double> vd;
    Vector<char> vc;
    
    EXPECT_EQ(vi.get_size(), 0);
    EXPECT_EQ(vd.get_size(), 0);
    EXPECT_EQ(vc.get_size(), 0);
}

TEST(VectorTest, PushBackOneElement) {
    Vector<int> v;
    v.push_back(42);
    EXPECT_EQ(v.get_size(), 1);
}

TEST(VectorTest, PushBackMultipleElements) {
    Vector<int> v;
    for (int i = 0; i < 100; i++) {
        v.push_back(i);
    }
    EXPECT_EQ(v.get_size(), 100);
}

TEST(VectorTest, PushBackCheckOrder) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(20));
    EXPECT_TRUE(v.has_item(30));
}

TEST(VectorTest, HasItemEmptyVector) {
    Vector<int> v;
    EXPECT_FALSE(v.has_item(10));
}

TEST(VectorTest, HasItemExisting) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(20));
    EXPECT_TRUE(v.has_item(30));
}

TEST(VectorTest, HasItemNonExisting) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    
    EXPECT_FALSE(v.has_item(99));
}

TEST(VectorTest, HasItemWithDuplicates) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(10);
    
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(20));
}

TEST(VectorTest, InsertAtBeginning) {
    Vector<int> v;
    v.push_back(20);
    v.push_back(30);
    v.insert(0, 10);
    
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(10));
}

TEST(VectorTest, InsertAtMiddle) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.insert(1, 20);
    
    EXPECT_EQ(v.get_size(), 3);
}

TEST(VectorTest, InsertAtEnd) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.insert(2, 30);
    
    EXPECT_EQ(v.get_size(), 3);
}

TEST(VectorTest, InsertInvalidPosition) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    
    EXPECT_FALSE(v.insert(10, 99));
    EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, InsertIntoEmptyVector) {
    Vector<int> v;
    v.insert(0, 42);
    EXPECT_EQ(v.get_size(), 1);
}

TEST(VectorTest, InsertManyElements) {
    Vector<int> v;
    for (int i = 0; i < 50; i++) {
        v.insert(0, i);
    }
    EXPECT_EQ(v.get_size(), 50);
}

TEST(VectorTest, RemoveFirstExisting) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_TRUE(v.remove_first(20));
    EXPECT_EQ(v.get_size(), 2);
    EXPECT_FALSE(v.has_item(20));
}

TEST(VectorTest, RemoveFirstNonExisting) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    
    EXPECT_FALSE(v.remove_first(99));
    EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, RemoveFirstFromEmpty) {
    Vector<int> v;
    EXPECT_FALSE(v.remove_first(10));
    EXPECT_EQ(v.get_size(), 0);
}

TEST(VectorTest, RemoveFirstOnlyFirstOccurrence) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(10);
    v.push_back(30);
    
    EXPECT_TRUE(v.remove_first(10));
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(10));
}

TEST(VectorTest, RemoveFirstAndCheckOrder) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    
    v.remove_first(20);
    
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(30));
    EXPECT_TRUE(v.has_item(40));
}

TEST(VectorTest, PushBackAfterInsert) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.insert(1, 15);
    v.push_back(30);
    
    EXPECT_EQ(v.get_size(), 4);
}

TEST(VectorTest, InsertAfterRemove) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.remove_first(20);
    v.insert(1, 25);
    
    EXPECT_EQ(v.get_size(), 3);
}

TEST(VectorTest, MultipleOperations) {
    Vector<int> v;
    
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    EXPECT_EQ(v.get_size(), 3);
    
    v.insert(1, 15);
    EXPECT_EQ(v.get_size(), 4);
    
    v.remove_first(20);
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_FALSE(v.has_item(20));
    
    v.push_back(40);
    EXPECT_EQ(v.get_size(), 4);
    
    EXPECT_TRUE(v.has_item(10));
    EXPECT_TRUE(v.has_item(15));
    EXPECT_TRUE(v.has_item(30));
    EXPECT_TRUE(v.has_item(40));
}

TEST(VectorTest, BoundaryInsertRemove) {
    Vector<int> v;
    
    for (int i = 0; i < 100; i++) {
        v.insert(0, i);
    }
    EXPECT_EQ(v.get_size(), 100);
    
    for (int i = 0; i < 50; i++) {
        v.remove_first(i);
    }
    EXPECT_EQ(v.get_size(), 50);
}

TEST(VectorTest, StringVector) {
    Vector<std::string> v;
    v.push_back("hello");
    v.push_back("world");
    v.insert(1, "beautiful");
    
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item("hello"));
    EXPECT_TRUE(v.has_item("beautiful"));
    EXPECT_TRUE(v.has_item("world"));
}

TEST(VectorTest, DoubleVector) {
    Vector<double> v;
    v.push_back(1.1);
    v.push_back(2.2);
    v.push_back(3.3);
    
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item(2.2));
    v.remove_first(2.2);
    EXPECT_FALSE(v.has_item(2.2));
    EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, CharVector) {
    Vector<char> v;
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');
    
    EXPECT_EQ(v.get_size(), 3);
    EXPECT_TRUE(v.has_item('b'));
    v.remove_first('b');
    EXPECT_FALSE(v.has_item('b'));
    EXPECT_EQ(v.get_size(), 2);
}

TEST(VectorTest, PrintEmpty) {
    Vector<int> v;
    EXPECT_NO_THROW(v.print());
}

TEST(VectorTest, PrintNonEmpty) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    EXPECT_NO_THROW(v.print());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}