double r2_score(xt::xarray<double> &Y_true, xt::xarray<double> &Y_pred) {
  double ss_res = xt::sum(xt::square(Y_true - Y_pred))();
  double ss_tot = xt::sum(xt::square(Y_true - xt::mean(Y_true)))();
  return 1.0 - (ss_res / ss_tot);
}
