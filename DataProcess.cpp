//
// Created by enjoy on 12/23/2019.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Matrix.h"
#include "DataProcess.h"
#include <set>


std::ostream &operator<<(std::ostream &  os, const std::vector<double> & b){
    for(int i = 0; i < b.size(); i++){
        std::cout << b[i] << " ";
    }
    std::cout << std::endl;
    return os;
}

Matrix operator * (const std::vector<double> &a, const std::vector<double> &b){
    Matrix answer(a.size(),b.size());
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b.size(); j++){
            answer[i][j] = a[i] * b[j];
        }
    }
    return answer;
}

void normalize(Matrix &dat){
    for(int i = 0; i < dat.size().first; i++){
        double square_average = 0;
        for(int j = 0; j < dat.size().second; j++){
            square_average += dat[i][j] * dat[i][j];
        }
        for(int j = 0; j < dat.size().second; j++){
            dat[i][j] = dat[i][j]  / sqrt(square_average);
        }
    }
}


double normalize(std::vector<double> &a){
    double num = 0;
    for(int i = 0; i < a.size(); i++){
        num += a[i] * a[i];
    }
    num = sqrt(num);
    for(int i = 0; i < a.size(); i++){
        a[i] = a[i] / num;
    }
    return num;
}



std::pair<std::pair<Matrix, Matrix>, std::pair<std::vector<double>, std::vector<double>>> train_test_set
        (const Matrix &a, const std::vector<double> & b, double split_proportion){
    std::set<unsigned> random_sample;
    const int training_set_size = int(b.size() * split_proportion);
    const int test_set_size = b.size() - training_set_size;
    while (random_sample.size() < test_set_size) {
        random_sample.insert(rand() % b.size());
    }
    Matrix training_set(training_set_size, a.size().second);
    Matrix test_set(test_set_size, a.size().second);
    std::vector<double> training_result;
    std::vector<double> test_result;
    training_result.resize(training_set_size);
    test_result.resize(test_set_size);

    int test_index = 0;
    int train_index = 0;

    for(int i = 0; i < b.size(); i++){
        if(random_sample.find(i) != random_sample.end()){
            for(int j = 0; j < a.size().second; j++){
                test_set[test_index][j] = a[i][j];
            }
            test_result[test_index] = b[i];
            test_index += 1;
        }
        else{
            for(int j = 0; j < a.size().second; j++){
                training_set[train_index][j] = a[i][j];
            }
            training_result[train_index] = b[i];
            train_index += 1;
        }
    }


    return std::make_pair(std::make_pair(training_set, test_set), std::make_pair(training_result, test_result));
}

void ReLU(Matrix & a){
    for(int i = 0; i < a.size().first; i++){
        for(int j = 0; j < a.size().second; j++){
            if(a[i][j] < 0){
                a[i][j] = 0;
            }
        }
    }
}

std::vector<double> star_multiply(const std::vector<double> &a, const std::vector<double> & sign){
    if(a.size() != sign.size()){
        std::cerr << "Can not star multiply!" << std::endl;
        exit(-1);
    }
    std::vector<double> answer;
    answer.resize(a.size());
    for(int i = 0; i < a.size(); i++){
        answer[i] = a[i] * sign[i];
    }
    return answer;
}