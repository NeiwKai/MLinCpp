#include <iostream>
#include <typeinfo>
#include <random>
#include <vector>
#include <algorithm>
#include <xtensor.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <cmath>

#include "../metrics/accuracy_score.hpp"
#include "../selection/train_val_split.hpp"
#include "LogisticRegression.hpp"

int main() {
  xt::random::seed(42);
  xt::xarray<double> X = xt::random::randn<double>({100, 5}, 0.0, 1.0);
  xt::xarray<double> Y = xt::random::randint<int>({100}, 0, 2);
  
  //xt::xarray<double> X_train, X_val, Y_train, Y_val;
  auto [X_train, X_val, Y_train, Y_val] = train_val_split(X, Y, 0.2, 42);
  //std::cout << typeid(X_train).name();
  LogisticRegression lr(0.01, 1000);
  lr.fit(X_train, Y_train);
  xt::xarray<double> Y_pred = lr.predict(X_val);
  //std::cout << Y_pred << "\n";
  std::cout << "Accuracy: " << accuracy_score(Y_val, Y_pred) << "\n";

  return 0;
}
