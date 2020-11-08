//
// Created by enjoy on 12/20/2019.
//

#ifndef FINAL_PROJECT_DATAPROCESS_H
#define FINAL_PROJECT_DATAPROCESS_H


#include <iostream>
#include <fstream>
#include <vector>
#include "Matrix.h"


Matrix operator * (const std::vector<double> &a, const std::vector<double> &b);
void normalize(Matrix &dat);
double normalize(std::vector<double> &a);
std::pair<std::pair<Matrix, Matrix>, std::pair<std::vector<double>, std::vector<double>>> train_test_set
    (const Matrix &a, const std::vector<double> & b, double split_proportion);
void ReLU(Matrix & a);
std::vector<double> star_multiply(const std::vector<double> &a, const std::vector<double> & sign);
std::ostream &operator<<(std::ostream &  os, const std::vector<double> & b);


#endif //FINAL_PROJECT_DATAPROCESS_H
