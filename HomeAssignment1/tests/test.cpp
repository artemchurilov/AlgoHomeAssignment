#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "../include/encode.h"
#include "../include/decode.h"

TEST(EncodeDecodeTest, FourZerosEncodeToZ) {
    std::vector<uint8_t> input(4, 0);
    std::string result = encode_block(input, 4);
    EXPECT_EQ(result, "z");
}

TEST(DecodeTest, ZInGroup) {
    std::istringstream in("azbc");
    std::ostringstream out;
    EXPECT_THROW(decode(in, out), std::runtime_error);
}


TEST(EncodeDecodeTest, ASCII85) {
    std::string original = "ASCII85!";
    std::istringstream ein(original);
    std::ostringstream eout;
    encode(ein, eout);
    std::istringstream din(eout.str());
    std::ostringstream dout;
    decode(din, dout);
    
    EXPECT_EQ(original, dout.str());
}

TEST(EncodeDecodeTest, MatMeh) {
    std::string original = "Matmeh!";
    std::istringstream ein(original);
    std::ostringstream eout;
    encode(ein, eout);
    std::istringstream din(eout.str());
    std::ostringstream dout;
    decode(din, dout);
    EXPECT_EQ(original, dout.str());
}

TEST(EncodeDecodeTest, Alpha) {
    std::string original = "a b c d e f g h .... I forgot..";
    std::istringstream ein(original);
    std::ostringstream eout;
    encode(ein, eout);
    std::istringstream din(eout.str());
    std::ostringstream dout;
    decode(din, dout);
    
    EXPECT_EQ(original, dout.str());
}


TEST(DecodeTest, InvalidCharacterHandling) {
    std::istringstream in("Abc~Def");
    std::ostringstream out;
    EXPECT_THROW(decode(in, out), std::runtime_error);
}

TEST(EncodeTest, RussianCharacter) {
    std::istringstream in("кот");
    std::ostringstream out;
    encode(in, out);
    EXPECT_EQ((out.str()),"d(7T<d=M");
}

TEST(EncodeTest, SomeText) {
    std::istringstream in("some text");
    std::ostringstream out;
    encode(in, out);
    EXPECT_EQ((out.str()),"F)Po,+EV1>F8");
}

TEST(DecodeTest, InvalidRussianCharacter) {
    std::istringstream in("Матмех");
    std::ostringstream out;
    EXPECT_THROW(decode(in, out), std::runtime_error);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}