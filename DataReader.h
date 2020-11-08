//
// Created by enjoy on 12/15/2019.
//

#ifndef FINAL_PROJECT_DATAREADER_H
#define FINAL_PROJECT_DATAREADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Matrix.h"

class DataReader {
private:
    const std::string filename;
    std::vector<std::string> stock_list;
    int observation_num;
    std::vector<Matrix> stock_data;
public:
    DataReader(const std::string filename_, int observation_num_):filename(filename_),observation_num(observation_num_) {
        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "File" << filename <<"could not be opened!" << std::endl;
            exit(-1);
        }
        bool is_header_handled = false;
        std::string line = "";
        while (getline(file, line)){
            if(!is_header_handled)
            {
                is_header_handled = true;
                continue;
            }
            int position = line.find(',');
            std::string a = line.substr(position + 1);
            a += ".csv";
            stock_list.push_back(a);
        }
        file.close();
        stock_data.reserve(6);
        for(int i = 0; i < 6; i++){
            stock_data.push_back(Matrix(observation_num, stock_list.size()));
        }

    }

    bool get_data();
    Matrix normalize_adj();
    Matrix get_high();
    Matrix get_low();
    Matrix get_open();
    Matrix get_close();
    Matrix get_volume();
    Matrix get_adj();
    std::pair<Matrix, Matrix> train_test_set(double split_proportion, std::string s);
    std::vector<double> get_total_volume();
};


#endif //FINAL_PROJECT_DATAREADER_H
