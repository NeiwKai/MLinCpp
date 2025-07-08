std::tuple<xt::xarray<double>,xt::xarray<double>,xt::xarray<double>,xt::xarray<double>> train_val_split(
  const xt::xarray<double> &X,
  const xt::xarray<double> &Y,
  double test_size,
  unsigned int seed
) 
{
  std::size_t n_samples = X.shape()[0];
  std::size_t n_val = static_cast<std::size_t>(n_samples * test_size);
  std::size_t n_train = n_samples - n_val;

  std::vector<std::size_t> indices(n_samples);
  std::iota(indices.begin(), indices.end(), 0);

  if (seed == -1) {
    std::random_device rd;
    seed = rd();
  }
  std::mt19937 rng(seed);
  std::shuffle(indices.begin(), indices.end(), rng);

  std::vector<std::size_t> train_idx(indices.begin(), indices.begin() + n_train);
  std::vector<std::size_t> val_idx(indices.begin() + n_train, indices.end());

  return {
    xt::view(X, xt::keep(train_idx)),
    xt::view(X, xt::keep(val_idx)),
    xt::view(Y, xt::keep(train_idx)),
    xt::view(Y, xt::keep(val_idx))
  };
}
