#include "gtest/gtest.h"
#include "../include/decode.h"
#include "../include/encode.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Encoder, EncodeTest)
{
    EXPECT_TRUE(encodeAscii85("Matmeh25") == "9jr-\\AS<hV");
}

TEST(Decoder, DecodeTest)
{
    EXPECT_TRUE(decodeAscii85("9jr-\\AS<hV") == "Matmeh25");
}

TEST(Coder, DeEncode)
{
    EXPECT_TRUE(decodeAscii85(encodeAscii85("Matmeh25")) == "Matmeh25");
}

TEST(Coder, EnDecode)
{
    EXPECT_TRUE(encodeAscii85(decodeAscii85("9jr-\\AS<hV")) == "9jr-\\AS<hV");
}

