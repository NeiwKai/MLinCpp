double mean_absolute_error(xt::xarray<double> &Y_true, xt::xarray<double> &Y_pred) {
  return xt::mean(xt::abs(Y_pred - Y_true))();
}
