#include <iostream>
#include <vector>
#include <cmath>
#include "LinearRegression.hpp"

std::tuple<double, double> linearRegression(std::vector<double> &X_train, std::vector<double> &Y_train, double learningRate, int epochs) {
  // init a and b
  double a = 0;
  double b = 0;

  for (int i=0; i<epochs; i++) {
    int idx = i % X_train.size();
    double Y_pred = a*X_train[idx] + b;
    double err = Y_pred - Y_train[idx];
    std::cout << "Epoch #" << i+1 << " X_train: " << X_train[idx] << " Y_train: " << Y_train[idx] << " Y_pred: " << Y_pred << " err: " << err << std::endl;
    // adjusting a and b
    a = a - learningRate * err;
    b = b - learningRate * err;
  }
  return {a, b};
}

int main() {
  // Training Process
  std::vector<double> X_train;
  std::vector<double> Y_train;
  X_train = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  Y_train = {1, 3, 5, 7, 8, 10, 11, 13, 15, 17};
  LinearRegression lr(0.01);
  lr.set_X_train(X_train);
  lr.set_Y_train(Y_train);
  lr.train();

  double X;
  std::cout << "Enter the X value: ";
  std::cin >> X;
  double Y_pred = lr.predict(X);
  std::cout << "Predicted value (epoch approach): " << Y_pred << std::endl;
  lr.cal_Coeff();
  lr.cal_Constant();
  Y_pred = lr.predict(X);
  std::cout << "Predicted value (best fit approach): " << Y_pred << std::endl;
  return 0;
}
