#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <typeinfo>

#include <Eigen/Dense>
#include "../include/lazycsv.hpp"
#include "../include/gauss.h"
#include "../include/file_read.h"
#include "../include/file_write.h"


int main()
{
    Eigen::MatrixXd A = fileRead("AB.csv");
    Eigen::MatrixXd Itog = gauss(A);
    fileWrite(Itog,"output.csv",15,false);
    return 0;
}
