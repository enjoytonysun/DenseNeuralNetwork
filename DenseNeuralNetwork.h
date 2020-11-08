//
// Created by enjoy on 12/14/2019.
//

#ifndef FINAL_PROJECT_DENSENEURALNETWORK_H
#define FINAL_PROJECT_DENSENEURALNETWORK_H

#include <iostream>
#include <vector>
#include "Matrix.h"


class DenseNeuralNetwork {
private:
    std::vector<Matrix> w;
    std::vector<std::vector<double>> layer;
    int layer_number;
    std::string loss_function;
    std::string activation_function;
    double learning_rate;
public:
    DenseNeuralNetwork() = delete;
    DenseNeuralNetwork(int layer_number_, const std::vector<int> & nodes, double learning_rate_ = 0.25, std::string loss_function_ = "square_loss",
           std::string activation_function_ = "ReLU"){
        if(nodes.size() != layer_number_){
            std::cerr << "Dense Neural Network Set up Error!" << std::endl;
            exit(-1);
        }
        layer_number = layer_number_;
        loss_function = loss_function_;
        activation_function = activation_function_;
        learning_rate = learning_rate_;
        w.reserve(layer_number - 1);
        layer.reserve(layer_number);
        for(int i = 0; i < layer_number - 1; i++){
            w.push_back(Matrix(nodes[i + 1], nodes[i]));
        }
        for(int i = 0; i < layer_number; i++){
            std::vector<double> lay;
            lay.resize(nodes[i]);
            layer.push_back(lay);
        }
    }

    std::vector<Matrix> get_w(){return w;}
    std::vector<double> predict(const Matrix &input);

    bool fit(const Matrix &input, const std::vector<double> &output, std::string train_mode = "Gradient Descent");
    std::vector<Matrix> Gradient(const std::vector<double> &input, double output);
    void back_propagation(const Matrix &input, const std::vector<double> output);
    void back_propagation_stochastic(const std::vector<double> &input, double output);
    bool fit_gradient_descent(const Matrix &input, const std::vector<double> &output);
    bool fit_stochastic_gradient_descent(const Matrix &input, const std::vector<double> &output);
    double loss(const Matrix &input, std::vector<double> true_value);


    void set_w(std::vector<Matrix> &r){
        for(int i = 0; i < r.size(); i ++){
            w[i] = r[i];
        }
    }
};


#endif //FINAL_PROJECT_DENSENEURALNETWORK_H
