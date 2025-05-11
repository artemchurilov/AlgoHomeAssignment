#include <iostream>
#include <string>
#include <istream>
#include <vector>
#include <typeinfo>

#include <Eigen/Dense>
#include "../include/lazycsv.hpp"
#include "../include/gauss.h"
#include "../include/file_read.h"

int main() {
    Eigen::MatrixXd A = fileRead("AB.csv");
    Eigen::MatrixXd Itog = gauss(A); 
    
    std::cout << A <<std::endl<<std::endl<<Itog<<std::endl;
    return 0;
}
