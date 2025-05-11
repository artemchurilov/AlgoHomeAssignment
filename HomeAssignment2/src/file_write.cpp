#include "../include/file_write.h"

#include <fstream>
#include <iomanip>

void fileWrite(Eigen::MatrixXd& A, const std::string& filename, int precision, bool scientific)
{
    std::ofstream file(filename);
    file << std::setprecision(precision);
    file << (scientific ? std::scientific : std::fixed);

    for(int i = 0; i < A.rows(); ++i) {
        for(int j = 0; j < A.cols(); ++j) {
            file << A(i, j);
            if(j < A.cols()-1) file << ",";
        }
        file << "\n";
    }
}
