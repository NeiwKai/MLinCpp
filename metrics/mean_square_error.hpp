double mean_square_error(xt::xarray<double> &Y_true, xt::xarray<double> &Y_pred) {
  return xt::mean(xt::square(Y_pred - Y_true))();
}
