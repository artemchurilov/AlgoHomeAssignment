#include "../include/gauss.h"
#include <cmath>


Eigen::MatrixXd gauss(Eigen::MatrixXd A)
{
    const double eps = 1e-10;

    int rowcount = A.rows();
    int colcount = A.cols();
    int rank = 0;

    for (int j=0;j < colcount-1&&rank<rowcount; ++j)
    {
        int general = rank;
        for (int k=rank; k<rowcount; ++k)
        {
            if(std::abs(A(k,j))>std::abs(A(general,j)))
            {
                general = k;
            }
        }

        if(std::abs(A(general,j))<eps)
        {
            continue;
        }
        A.row(general).swap(A.row(rank));  
        A.row(rank)/=A(rank,j);
        for (int i = rank+1; i <rowcount; ++i)
        {
            A.row(i)-=A.row(rank)*A(i,j);
        }
        rank++;
    }
    for (int i=rank;i<rowcount;++i)
    {
        if (std::abs(A(i,colcount-1))>eps)
        {
            throw std::runtime_error("System's not compitable");
        }
    }
    for (int i=rank-1; i>=0;--i)
    {
        int lead = -1;
        for (int j=0;j<colcount-1; ++j)
        {
            if (std::abs(A(i,j))>eps)
            {
                lead=j;
                break;
            }
        }
        if (lead==-1)
        {
            continue;
        }
        for (int k=i-1;k>=0;--k)
        {
            A.row(k)-=A.row(i)*A(k,lead);
        }
    }

    if (rank<colcount-1)
    {
        throw std::runtime_error("System has an infinite number of solution");
    }

    for (int i=0; i<A.rows();++i)
    {
        for (int j=0;j<A.cols();++j)
        {
            if (std::abs(A(i,j))<eps) 
            {
                A(i,j) = 0.0;
            }
        }
    }

    return A;
};
