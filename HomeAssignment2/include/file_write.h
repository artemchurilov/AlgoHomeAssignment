#ifndef FILE_WRITE_H
#define FILE_WRITE_H
#include <Eigen/Dense>
#include <string>

void fileWrite(Eigen::MatrixXd& A, const std::string& filename, int precision = 15, bool scientific = false);

#endif