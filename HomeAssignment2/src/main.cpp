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
    Eigen::MatrixXd temp(A.rows(), A.cols()); 
    Eigen::MatrixXd result(A.rows(), A.cols());

    int rowcount = A.rows();

    for (int j=0;j < rowcount; ++j)
    {
        result.row(j)=A.row(j)/A(j,j);
        for (int i=0; i<rowcount;++i)
        {   
            if (i==j)
            {
                temp.row(i)=A.row(i)/result(j,j);
            }
            else
            {
                temp.row(i)=A.row(i)-result.row(j)*(A(i,j)/result(j,j));
            }
        }   
        A=temp;
    }
    A=result;
    for (int i=rowcount-1;i>=0;--i)
    {
        temp = A;
        for (int j=rowcount-1; j>=0;--j)
        {        
            if (j==i)
            {

            }
            else
            {
                A.row(i)-=temp(i,j)*temp.row(j);
            }
            
        }
    }
    std::cout << A <<std::endl<<std::endl<<temp<<std::endl<<std::endl<<result<<std::endl;

    return 0;
}
