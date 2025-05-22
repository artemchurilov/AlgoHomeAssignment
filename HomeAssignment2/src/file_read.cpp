#include <vector>
#include <algorithm>
#include <iostream>

#include <Eigen/Dense>
#include "../../externals/lazycsv/include/lazycsv.hpp"
#include "../include/file_read.h"

Eigen::MatrixXd fileRead(const std::string& filename)
{
    lazycsv::parser parser{ filename };
    std::vector<std::vector<double>> rcsv{};
    {
        for (const auto row : parser)
        {
            std::vector<double> r{};
            for (const auto cell : row)
            {
                r.push_back(std::stod(std::string(cell.raw())));
            }
            rcsv.push_back(r);
        }
    }

    Eigen::Matrix<double, -1, -1, Eigen::RowMajor> A(rcsv.size(), rcsv.begin()->size());
    int ir = 0;
    for(auto r : rcsv)
    {
        int ic = 0;
        for(double e: r)
        {
            A(ir, ic++) = e;
        }
        ir++;
    }
    return A;
}