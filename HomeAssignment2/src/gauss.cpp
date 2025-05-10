#include "../include/gauss.h"
#include <cmath>


Eigen::MatrixXd gauss(Eigen::MatrixXd A)
{
    const double eps = 1e-10;

    int rowcount = A.rows();
    int colcount = A.cols();
    for (int j=0;j < rowcount; ++j)
    {
        for (int k=j; k<rowcount; ++k)
        {
            if(std::abs(A(k,j))>eps)
            {
                A.row(j).swap(A.row(k));  
                break;       
            }
        }
        if (std::abs(A(j,j))<eps){
            bool all_zero = true;
            for (int l = 0; l < colcount - 1; ++l)
            {    
                if (std::abs(A(j,l))>eps)
                {
                    all_zero = false;
                    break;
                }
            }
            if (all_zero && std::abs(A(j,colcount-1))>eps)
            {
                throw std::runtime_error("System doesn't have any solutions");
            }
            continue;
        }

        A.row(j)=A.row(j).array()/A(j,j);
        for (int i=j+1; i<rowcount;++i)
        {   
            A.row(i)-= A.row(j)*(A(i,j));
        }   
    }
    for (int j=rowcount-1;j>=0;--j)
    {
        for (int i=j-1; i>=0;--i)
        {        
            A.row(i)-=A.row(j)*A(i,j);
            
        }
    }
    return A;
};
