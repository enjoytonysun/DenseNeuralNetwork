//
// Created by enjoy on 12/15/2019.
//

#include "DataReader.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <random>
#include <set>

bool DataReader::get_data(){
    for(int i = 0; i < stock_list.size(); i++){
        std::string stock_name = stock_list[i];
        std::ifstream file(stock_name);
        if (!file)
        {
            std::cerr << "File" << stock_name <<"could not be opened!" << std::endl;
            exit(-1);
        }
        std::cout << "Begins to retrieve data from "<< stock_name << std::endl;
        std::string line = "";
        bool is_header_handled = false;
        int k = 0;
        while (getline(file, line) && k < observation_num){
            if(!is_header_handled)
            {
                is_header_handled = true;
                continue;
            }
            int position_1 = line.find(',' ,0);
            int position_2 = line.find(',',position_1 + 1);
            int position_3 = line.find(',',position_2 + 1);
            int position_4 = line.find(',',position_3 + 1);
            int position_5 = line.find(',',position_4 + 1);
            int position_6 = line.find(',',position_5 + 1);


            stock_data[0][k][i] = stof(line.substr(position_1 + 1, position_2 - position_1 - 1));
            stock_data[1][k][i] = stof(line.substr(position_2 + 1, position_3 - position_2 - 1));
            stock_data[2][k][i] = stof(line.substr(position_3 + 1, position_4 - position_3 - 1));
            stock_data[3][k][i] = stof(line.substr(position_4 + 1, position_5 - position_4 - 1));
            stock_data[4][k][i] = stof(line.substr(position_5 + 1, position_6 - position_5 - 1));
            stock_data[5][k][i] = stof(line.substr(position_6 + 1));

            k += 1;
        }
        std::cout << "Ends to retrieve data from "<< stock_name << std::endl;
        file.close();
    }
    return true;
}

Matrix DataReader::get_high(){
    return stock_data[0];
}

Matrix DataReader::get_low(){
    return stock_data[1];
}

Matrix DataReader::get_open(){
    return stock_data[2];
}

Matrix DataReader::get_close(){
    return stock_data[3];
}

Matrix DataReader::get_volume(){
    return stock_data[4];
}

Matrix DataReader::get_adj(){
    Matrix b(observation_num - 1, stock_list.size());
    for(int i = 0; i < observation_num - 1; i++){
        for(int j = 0; j < stock_list.size(); j++){
            b[i][j] = stock_data[5][i][j];
        }
    }
    return b;
}

std::pair<Matrix, Matrix> DataReader::train_test_set(double split_proportion, std::string s){
    int data_index;
    if(s == "high"){data_index = 0;}
    else if(s == "low"){data_index = 1;}
    else if(s == "open"){data_index = 2;}
    else if(s == "close"){data_index = 3;}
    else if(s == "volume"){data_index = 4;}
    else if(s == "adj"){data_index = 5;}
    else{
        std::cerr << "Do not have column named " << s << std::endl;
        exit(-1);
    }

    std::set<unsigned> random_sample;
    const int training_set_size = int(observation_num * split_proportion);
    const int test_set_size = observation_num - training_set_size;
    while (random_sample.size() < test_set_size) {
        random_sample.insert(rand() % observation_num);
    }
    Matrix training_set(training_set_size, stock_list.size());
    Matrix test_set(test_set_size, stock_list.size());
    int test_index = 0;
    int train_index = 0;
    for(int i = 0; i < observation_num; i++){
        if(random_sample.find(i) != random_sample.end()){
            for(int j = 0; j < stock_list.size(); j++){
                test_set[test_index][j] = stock_data[data_index][i][j];
            }
            test_index += 1;
        }
        else{
            for(int j = 0; j < stock_list.size(); j++){
                training_set[train_index][j] = stock_data[data_index][i][j];
            }
            train_index += 1;
        }
    }
    return std::make_pair(training_set, test_set);
}

std::vector<double> DataReader::get_total_volume() {
    Matrix volume = stock_data[4];
    std::vector<double> answer;
    answer.resize(observation_num - 1);
    for(int i = 0; i < observation_num - 1; i++){
        answer[i] = 0;
        for(int j = 0; j < stock_list.size(); j++){
            answer[i] += volume[i + 1][j];
        }
    }
    return answer;
}


Matrix DataReader::normalize_adj(){
    Matrix dat = stock_data[5];
    for(int i = 0; i < dat.size().first; i++){
        double square_average = 0;
        for(int j = 0; j < dat.size().second; j++){
            square_average += dat[i][j] * dat[i][j];
        }
        for(int j = 0; j < dat.size().second; j++){
            dat[i][j] = dat[i][j]  / sqrt(square_average);
        }
    }
    return dat;
}