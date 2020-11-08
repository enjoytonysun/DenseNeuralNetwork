cmake_minimum_required(VERSION 3.14)
project(Final_Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Final_Project main.cpp Matrix.cpp Matrix.h DenseNeuralNetwork.cpp DenseNeuralNetwork.h
        DataReader.cpp DataReader.h DataProcess.h DataProcess.cpp)