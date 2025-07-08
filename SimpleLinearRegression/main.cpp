#include <iostream>
#include <vector>
#include <xtensor.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <cmath>

#include "../metrics/mean_square_error.hpp"
#include "../metrics/root_mean_square_error.hpp"
#include "../metrics/mean_absolute_error.hpp"
#include "../metrics/r2_score.hpp"
#include "../selection/train_val_split.hpp"
#include "SimpleLinearRegression.hpp"

int main() {
  xt::random::seed(42);
  xt::xarray<double> X = xt::random::randn<double>({100}, 0.0, 1.0);
  xt::xarray<double> Y = xt::random::randint<int>({100}, 0, 2);

  auto [X_train, X_val, Y_train, Y_val] = train_val_split(X, Y, 0.2, 42);

  SimpleLinearRegression slr(0.01);
  slr.fit(X_train, Y_train);

  xt::xarray<double> Y_pred = slr.predict(X_val);
  double mse = mean_square_error(Y_val, Y_pred);
  double rmse = root_mean_square_error(Y_val, Y_pred);
  double mae = mean_absolute_error(Y_val, Y_pred);
  double r2 = r2_score(Y_val, Y_pred);

  std::cout << "MSE:  " << mse << "\n";
  std::cout << "RMSE: " << rmse << "\n";
  std::cout << "MAE:  " << mae << "\n";
  std::cout << "R²:   " << r2 << "\n";
  return 0;
}
