typedef struct Node {
  auto feature;
  auto value;
  auto results;
  auto true_branch;
  auto false_branch;
} Node;

class IterativeDichotomiser3 {
  protected:
    Node *ptr;
  public:
  InteractiveDichotomiser3() {
    
  }
  double entropy(xt::xarray<double> data) {
    xt::xarray<double> counts = xt::bincount(data);
    xt::xarray<double> probabilities = counts / len(data);
    auto mask = probabilities > 0;
    xt::xarray<double> entropy = xt::sum(xt::where(mask, probabilities * xt::log2(probabilities), 0.0));
    return xt::abs(entropy);
  }
  xt::xarray<std::size_t> flatten_idices(const xt::xarray<bool> &mask) {
    std::vector<std::size_t> indices;
    for (std::size_t i =0; i<mask.size(); i++) {
      if (mask(i)) {
        indices.push_back(i);
      }    
    }
    return xt::adapt(indices);
  }
  std::tuple<xt::xarray<double>, xt::xarray<double>,
  xt::xarray<double>, xt::xarray<double>> split_data(xt::xarray X, xt::xarray Y, double feature, double threshold) {
    auto true_mask = xt::view(X, all(), feature) <= threshold;
    auto false_mask = xt::view(X, all(), feature) > threshold;

    auto true_indices = flatten_indices(true_mask);
    auto false_indices = flatten_indices(false_mask);

    xt::xarray<double> true_X = xt::view(X, true_indices, all());
    xt::xarray<double> true_Y = xt::view(Y, true_indices, all());

    xt::xarray<double> false_X = xt::view(X, false_indices, all());
    xt::xarray<double> true_Y = xt::view(Y, flase_indices, all());

    return {true_X, true_Y, false_X, false_Y};
  }
  Node build_tree(X, Y) {
    
  }




















};
