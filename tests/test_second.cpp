#include <gtest/gtest.h>
#include"SearchServer.h"
#include"InvertedIndex.h"


TEST(SearchServerTest, split_words_handles_empty_string)
{
    InvertedIndex idx;
    SearchServer server(idx);
    auto words = server.split_words("");
    EXPECT_TRUE(words.empty());
}

TEST(SearchServerTest, split_words_handles_single_word)
{
    InvertedIndex idx;
    SearchServer server(idx);
    auto words = server.split_words("test");
    ASSERT_EQ(words.size(), 1);
    EXPECT_EQ(words[0], "test");
}

TEST(SearchServerTest, split_words_handles_multiple_words)
{
    InvertedIndex idx;
    SearchServer server(idx);
    auto words = server.split_words("test multiple words");
    ASSERT_EQ(words.size(), 3);
    EXPECT_EQ(words[0], "test");
    EXPECT_EQ(words[1], "multiple");
    EXPECT_EQ(words[2], "words");
}

TEST(SearchServerTest, split_word_punctuation)
{
    InvertedIndex idx;
    SearchServer server(idx);
    auto words = server.split_words("test, punctuation!");
    ASSERT_EQ(words.size(), 2);
    EXPECT_EQ(words[0], "test");
    EXPECT_EQ(words[1], "punctuation");
}