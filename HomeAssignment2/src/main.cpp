#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <typeinfo>

#include <Eigen/Dense>
#include "../include/lazycsv.hpp"
#include "../include/file_read.h"

int main() {
    Eigen::MatrixXd A = fileRead("AB.csv");
    Eigen::MatrixXd B(3, 2); 
    B << 2, 8,
         1, 10,
         4, 12;
    Eigen::MatrixXd C(3, 2);
    
    C.row(0)=B.row(0)/B(0,0);
    C.row(1)=B.row(1)-B.row(0)*(B(1,0)/B(0,0));
    C.row(2)=B.row(2)-B.row(0)*(B(2,0)/B(0,0));

    std::cout << A <<std::endl<<std::endl<<B<<std::endl<<std::endl<<C<<std::endl;

    return 0;
}
