#include "../src/wc.hpp"
#include <gtest/gtest.h>

TEST(FILECOUNT, Counts){
    std::string ts = "This is a test string \nit has 4 lines\n and many different characters\n\r\t 1 2 3 4 5 6 7 8 9 ";
    std::istringstream s(ts); // Use istringstream for string stream
    FH::Counts cs;
    cs = FH::getWordLineCharCounts(s, true, false, false);
    EXPECT_EQ(cs.lines, 4);
    EXPECT_EQ(cs.words, 0);
    EXPECT_EQ(cs.characters, 0);

    s.clear(); s.seekg(0, std::ios::beg); // Reset stream


    cs = FH::getWordLineCharCounts(s, false, true, false);
    EXPECT_EQ(cs.lines, 0);
    EXPECT_EQ(cs.words, 22);
    EXPECT_EQ(cs.characters, 0);

    s.clear(); s.seekg(0, std::ios::beg); // Reset stream

    cs = FH::getWordLineCharCounts(s, false, false, true);
    EXPECT_EQ(cs.lines, 0);
    EXPECT_EQ(cs.words, 0);
    EXPECT_EQ(cs.characters, 91);

    s.clear(); s.seekg(0, std::ios::beg); // Reset stream


    cs = FH::getWordLineCharCounts(s, true, true, true);
    EXPECT_EQ(cs.lines, 4);
    EXPECT_EQ(cs.words, 22);
    EXPECT_EQ(cs.characters, 91);
}