//
// Created by enjoy on 12/14/2019.
//

#include "Matrix.h"
#include <iostream>
#include <vector>


std::pair<int, int> Matrix::size() const{
    return std::make_pair(row, column);
}

Matrix Matrix::operator * (const Matrix & b){
    if(column != b.row){
        std::cerr << "A's Column number doesn't equal to B's row number. Can not multiply!" << std::endl;
        exit(-1);
    }
    else{
        Matrix a(row, b.column);
        for(int i = 0; i < row; i++){
            for(int j = 0; j < b.column; j++){
                 double sign = 0;
                 for(int k = 0; k < column; k++){
                     sign += data[i * column + k] * b.data[k * b.column + j];
                 }
                 a.data[i * a.column + j] = sign;
            }
        }
        return a;
    }
}

Matrix Matrix::operator + (const Matrix & b){
    if(row != b.row or column != b.column){
        std::cerr << "Can not add!" << std::endl;
        exit(-1);
    }
    else{
        Matrix a(row, column);
        for(int i = 0; i < row * column; i++){
            a.data[i] = data[i] + b.data[i];
        }
        return a;
    }
}

Matrix Matrix::operator - (const Matrix & b){
    if(row != b.row or column != b.column){
        std::cout << "Can not deduct!" << std::endl;
        exit(-1);
    }
    else{
        Matrix a(row, column);
        for(int i = 0; i < row * column; i++){
            a.data[i] = data[i] - b.data[i];
        }
        return a;
    }
}

Matrix operator * (double lem, const Matrix &b){
    Matrix a(b.row, b.column);
    for(int i = 0; i < b.row * b.column; i++){
        a.data[i] = lem * b.data[i];
    }
    return a;
}

Matrix Matrix::T()const{
    Matrix a(column, row);
    for(int i = 0; i < a.row; i++){
        for(int j = 0; j < a.column; j++){
            a.data[i * a.column + j] = data[j * column + i];
        }
    }
    return a;
}

std::ostream &operator<<(std::ostream &  os, const Matrix & b){
    for(int i = 0; i < b.row; i++){
        for(int j = 0; j < b.column; j++){
            std::cout << b.data[i * b.column + j] << " ";
        }
        std::cout << std::endl;
    }
    return os;
}

double* Matrix::operator[] (int i){
    if(i >= row){
        std::cerr << "Row " << i <<" is out of range!"<< std::endl;
        exit(-1);
    }

    return &data[i * column];
}

double* Matrix::operator[] (int i) const{
    if(i >= row){
        std::cerr << "Row " << i <<" is out of range!"<< std::endl;
        exit(-1);
    }

    return &data[i * column];
}

std::vector<double> Matrix::operator()(int i) const{
    std::vector<double> answer;
    answer.resize(column);
    for(int j = 0; j < column; j ++){
        answer[j] = data[i * column + j];
    }
    return answer;
}

std::vector<double> Matrix::operator * (const std::vector<double> & b){
    if(column != b.size()){
        std::cerr << "Column number doesn't equal to the size of the vector. Can not multiply!"<< std::endl;
        exit(-1);
    }
    std::vector<double> answer;
    answer.resize(row);
    for(int i = 0; i < row; i++){
        double sign = 0;
        for(int j = 0; j < column; j++){
            sign += data[i * column + j] * b[j];
        }
        answer[i] = sign;
    }
    return answer;
}

Matrix& Matrix::operator = (const Matrix &b){
    delete []data;
    row = b.row;
    column = b.column;
    data = new double[row * column];
    for(int i = 0; i < row * column; i++){
        data[i] = b.data[i];
    }
    return *this;
}
