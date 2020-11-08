//
// Created by enjoy on 12/14/2019.
//

#ifndef FINAL_PROJECT_MATRIX_H
#define FINAL_PROJECT_MATRIX_H

#include <iostream>
#include <vector>


class Matrix {
private:
    int row;
    int column;
    double * data;
public:
    Matrix(int row_, int column_){
        row = row_;
        column = column_;
        data = new double[row * column];
        for(int i = 0; i < row * column; i++){
            data[i] = (rand() % 100 + 1) / 100;
        }
    }

    Matrix(int row_, int column_, const std::vector<double> & a){
        if(a.size() != row_ * column_){
            std::cerr << "Can not initialize correctly!" << std::endl;
        }
        row = row_;
        column = column_;
        data = new double[row * column];
        for(int i = 0; i < row * column; i++){
            data[i] = a[i];
        }
    }

    Matrix(const Matrix & a){
        row = a.row;
        column = a.column;
        data = new double[row * column];
        for(int i = 0; i < row * column; i++){
            data[i] = a.data[i];
        }
    }

    Matrix() = delete;

    ~Matrix(){
        delete []data;
    }

    std::pair<int, int> size() const;
    Matrix T()const;
    Matrix operator * (const Matrix & b);
    std::vector<double> operator * (const std::vector<double> & b);
    Matrix operator + (const Matrix & b);
    Matrix operator - (const Matrix & b);
    Matrix& operator = (const Matrix & b);
    double* operator[] (int i);
    double* operator[] (int i) const;
    std::vector<double> operator()(int i) const;
    friend Matrix operator * (double lem, const Matrix &b);
    friend std::ostream &operator<<(std::ostream &  os, const Matrix & b);
};



#endif //FINAL_PROJECT_MATRIX_H
