#include "InvertedIndex.h"
#include <gtest/gtest.h>

TEST(InvertedIndexTest, empty_document_base)
{
    InvertedIndex index;
    std::vector<std::string> input_docs;
    index.update_document_base(input_docs);
    auto word_count = index.get_word_count("test");
    EXPECT_TRUE(word_count.empty());
}

TEST(InvertedIndexTest, single_word) 
{
    InvertedIndex index;
    std::vector<std::string> input_docs = { "test" };
    index.update_document_base(input_docs);
    auto word_count = index.get_word_count("test");
    EXPECT_EQ(word_count.size(), 1);
    EXPECT_EQ(word_count[0], 1);
}

TEST(InvertedIndexTest, multiple_words) 
{
    InvertedIndex index;
    std::vector<std::string> input_docs = { "test", "test test", "another test" };
    index.update_document_base(input_docs);
    auto word_count_test = index.get_word_count("test");
    auto word_count_another = index.get_word_count("another");

    EXPECT_EQ(word_count_test.size(), 3);
    EXPECT_EQ(word_count_test[0], 1);
    EXPECT_EQ(word_count_test[1], 2);
    EXPECT_EQ(word_count_test[2], 1);

    EXPECT_EQ(word_count_another.size(), 1);
    EXPECT_EQ(word_count_another[2], 1);
}

TEST(InvertedIndexTest, punctuation)
{
    InvertedIndex index;
    std::vector<std::string> input_docs = { "test.", "test, test!", "another test?" };
    index.update_document_base(input_docs);
    auto word_count = index.get_word_count("test");
    EXPECT_EQ(word_count.size(), 3);
    EXPECT_EQ(word_count[0], 1);
    EXPECT_EQ(word_count[1], 2);
    EXPECT_EQ(word_count[2], 1);
}