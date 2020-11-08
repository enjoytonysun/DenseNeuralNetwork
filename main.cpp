#include <iostream>
#include "Matrix.h"
#include "DataReader.h"
#include "DataProcess.h"
#include "DenseNeuralNetwork.h"
#include <vector>
#include <math.h>
#include <stdlib.h>
#include <fstream>



int main() {

    DataReader a("_TickersCorr3.csv", 466);
    a.get_data();
    std::vector<double> b = a.get_total_volume();

    Matrix c = a.get_adj();

    /*
    normalize(c);
    double info = normalize(b);
     */


    std::pair<std::pair<Matrix, Matrix>, std::pair<std::vector<double>, std::vector<double>>>
            split_result = train_test_set(c, b, 0.5);


    Matrix training = split_result.first.first;
    Matrix test = split_result.first.second;
    std::vector<double> training_result = split_result.second.first;
    std::vector<double> test_result = split_result.second.second;

    normalize(training);
    normalize(test);
    double info = normalize(training_result);
    normalize(test_result);

    std::vector<int> nodes = {483,50,5,1};
    DenseNeuralNetwork work(4, nodes);
    work.fit(training, training_result, "Stochastic Gradient Descent");

    std::vector<double> predict = work.predict(training);
    std::cout << work.loss(test, test_result) << std::endl;
    /*
    for(int i = 0; i < predict.size(); i++){
        std::cout << predict[i] * info << " " << test_result[i] <<std::endl;
    }
*/
    return 0;
}