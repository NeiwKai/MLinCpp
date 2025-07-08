double accuracy_score(xt::xarray<double> Y_true, xt::xarray<double> Y_pred) {
  auto correct = xt::sum(xt::equal(Y_true, Y_pred))();
  return static_cast<double>(correct) / Y_true.size();
}
