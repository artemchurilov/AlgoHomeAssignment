#include "../include/gauss.h"
#include <cmath>


Eigen::MatrixXd gauss(Eigen::MatrixXd A)
{
    const double eps = 1e-10;
    const int rowcount = A.rows();
    const int colcount = A.cols();
    int rank = 0;

    for (int j=0;j < colcount-1&&rank<rowcount; ++j)
    {
        Eigen::Index max_row;
        A.col(j).tail(rowcount-rank).cwiseAbs().maxCoeff(&max_row);
        max_row+=rank;

        if(std::abs(A(max_row,j))<eps)
        {
            continue;
        }

        A.row(max_row).swap(A.row(rank));

        const auto general_row = A.row(rank);
        const double val = A(rank,j);

        A.row(rank).noalias() = general_row/val;
        A.bottomRows(rowcount-rank-1).middleCols(j,colcount-j) -= 
            A.col(j).tail(rowcount-rank-1) * general_row.middleCols(j,colcount-j);
        rank++;
    }

    if ((A.bottomRows(rowcount-rank).rightCols(1).array().abs()>eps).any())
    {
        throw std::runtime_error("System's not compitable");
    }
    for (int i=rank-1; i>=0;--i)
    {
        Eigen::Index lead;
        if (A.row(i).head(colcount-1).cwiseAbs().maxCoeff(&lead) < eps)
        {
            continue;
        }
        A.topRows(i).middleCols(lead, colcount-lead) -=
            A.col(lead).head(i) * A.row(i).middleCols(lead,colcount-lead);
    }
    
    if (rank<colcount-1)
    {
        throw std::runtime_error("System has an infinite number of solution");
    }

    A = (A.array().abs()<eps).select(0,A);


    return A;
};
