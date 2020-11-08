//
// Created by enjoy on 12/14/2019.
//

#include "DenseNeuralNetwork.h"
#include <iostream>
#include <vector>
#include <math.h>
#include "Matrix.h"
#include "DataProcess.h"
#include <random>



std::vector<double> DenseNeuralNetwork::predict(const Matrix &input){
    if(input.size().second != layer[0].size()){
        std::cerr << "Input data size error!" << std::endl;
        exit(-1);
    }
    Matrix current = input.T();
    for(int i = 0; i < layer_number - 1; i++){
        current = w[i] * current;
        ReLU(current);
    }
    return current(0);
}

double DenseNeuralNetwork::loss(const Matrix &input, const std::vector<double> true_value){
    if(input.size().first != true_value.size()){
        std::cerr << "Input data size doesn't match the output data size!" << std::endl;
        exit(-1);
    }
    std::vector<double> prediction = predict(input);
    double answer = 0;
    for(int i = 0; i < true_value.size(); i++){
        answer += (prediction[i] - true_value[i]) * (prediction[i] - true_value[i]);
    }
    answer = answer / true_value.size();
    return answer;
}

std::vector<Matrix> DenseNeuralNetwork::Gradient(const std::vector<double> &input, const double output){
    if(input.size() != layer[0].size()){
        std::cerr << "Input data size error!"<< "Input size is "<< input.size()<< ",which ought to be "<< layer[0].size() << std::endl;
        exit(-1);
    }
    std::vector<std::vector<double>> h;
    h.resize(layer_number);
    layer[0] = input;
    for(int i = 0; i < layer_number - 1; i++){
        layer[i + 1] = w[i] * layer[i];
        if(i != layer_number - 2){
            h[i + 1].resize(layer[i + 1].size());
            for(int j = 0; j < layer[i + 1].size(); j++){
                if(layer[i + 1][j] < 0){
                    layer[i + 1][j] = 0;
                    h[i + 1][j] = 0;
                }
                else if(layer[i + 1][j] == 0){
                    h[i + 1][j] = 0.5;
                }
                else{
                    h[i + 1][j] = 1;
                }
            }
        }
    }

    std::vector<std::vector<double>> delta;
    delta.resize(layer_number);
    delta[layer_number - 1].push_back(2 * (layer[layer_number - 1][0] - output));
    for(int i = layer_number - 1; i > 1; i--){
        delta[i - 1] = star_multiply(w[i - 1].T() * delta[i], h[i - 1]);
    }

    std::vector<Matrix> gradient;
    gradient.reserve(layer_number - 1);
    for(int i = 0; i < layer_number - 1; i++){
        gradient.push_back(delta[i + 1] * layer[i]);
    }

    return gradient;
}

void DenseNeuralNetwork::back_propagation_stochastic(const std::vector<double> &input, const double output){
    std::vector<Matrix> gradient = Gradient(input, output);
    for(int i = 0; i < w.size(); i++){
        w[i] = w[i] - learning_rate * gradient[i];
    }

}

void DenseNeuralNetwork::back_propagation(const Matrix &input, const std::vector<double> output){
    if(input.size().first != output.size()){
        std::cerr << "Input data size doesn't match the output data size!" << std::endl;
        exit(-1);
    }
    int size = output.size();
    std::vector<Matrix> gradient;
    gradient.reserve(layer_number - 1);
    for(int i = 0; i < output.size(); i++){
        std::vector<Matrix> this_gradient = Gradient(input(i), output[i]);
        if(i >= 1){
            for(int j = 0; j < gradient.size(); j++){
                gradient[j] = gradient[j] + double(1)/size * this_gradient[j];
            }
        }
        else{
            for(int j = 0; j < layer_number - 1; j++){
                gradient.push_back( double(1) / size * this_gradient[j]);
            }
        }
    }


    for(int i = 0; i < w.size(); i++){
        w[i] = w[i] - learning_rate * gradient[i];
    }

}



bool DenseNeuralNetwork::fit(const Matrix &input, const std::vector<double> &output, std::string train_mode){
    if(train_mode == "Gradient Descent"){return fit_gradient_descent(input, output);}
    else if(train_mode == "Stochastic Gradient Descent"){return fit_stochastic_gradient_descent(input, output);}
    else{
        std::cerr << "Training mode error. No such training method!" << std::endl;
        exit(-1);
    }
}

bool DenseNeuralNetwork::fit_gradient_descent(const Matrix &input, const std::vector<double> &output){
    double loss_start = loss(input, output);
    back_propagation(input, output);
    double loss_end = loss(input, output);
    std::cout << "lose_start: " << loss_start << " loss_end: "<< loss_end << std::endl;
    while(abs(loss_end - loss_start) > 0.00001){
        loss_start = loss_end;
        back_propagation(input, output);
        loss_end = loss(input, output);
        std::cout << "lose_start: "<<loss_start << " loss_end: "<< loss_end << std::endl;
    }
    return true;
}

bool DenseNeuralNetwork::fit_stochastic_gradient_descent(const Matrix &input, const std::vector<double> &output){

    double loss_start = loss(input, output);
    int random_seed = rand() % output.size();
    back_propagation_stochastic(input(random_seed),output[random_seed]);
    double loss_end = loss(input, output);
    while(abs(loss_end - loss_start) > 0.0000001) {
        loss_start = loss_end;
        random_seed = rand() % output.size();
        back_propagation_stochastic(input(random_seed),output[random_seed]);
        loss_end = loss(input, output);
        std::cout << "lose_start: "<<loss_start << " loss_end: "<< loss_end << std::endl;
    }
    return true;
}