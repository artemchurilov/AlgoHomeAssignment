#include <gtest/gtest.h>
#include <Eigen/Dense>
#include "../include/gauss.h"
#include "../include/file_read.h"

#include <iostream>
TEST(CITest,Test1)
{
    EXPECT_TRUE(true);
}

TEST(GaussMethod,ConstMatrixAndFileRead)
{
    Eigen::MatrixXd A = fileRead("tests/test1.csv");
    A = gauss(A);
    Eigen::MatrixXd itog(3,4);
    itog << 1,0,0,3,
            0,1,0,3,
            0,0,1,3;
    EXPECT_TRUE(A==itog);
}

TEST(GaussMethod,ZeroMatrix)
{
    Eigen::MatrixXd A(2,3);
    A << 0,0,0,
         0,0,0;
    EXPECT_THROW(gauss(A),std::runtime_error);
}

TEST(GaussMethod,InvalidMatrix)
{
    Eigen::MatrixXd A(2,3);
    A << 1,1,0,
         0,0,3;
    EXPECT_THROW(gauss(A),std::runtime_error);
}

TEST(GaussMethod,InfiniteNumberOfSolution)
{
    Eigen::MatrixXd A(1,3);
    A << 1,0,2;
    EXPECT_THROW(gauss(A),std::runtime_error);
}

TEST(GaussMethod,SimpleSystem)
{
    Eigen::MatrixXd A(4,5);
    A << 1,0,1,0,3,
         1,0,0,4,13,
         4,3,3,3,1,
         0,-2,0,1,-8;
    Eigen::MatrixXd B(4,5);
    B << 1,0,0,0,277,
         0,1,0,0,-29,
         0,0,1,0,-274,
         0,0,0,1,-66;
    A=(gauss(A));
    EXPECT_NEAR(A(3,4),B(3,4),1e-10);
    EXPECT_NEAR(A(2,4),B(2,4),1e-10);
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}