class LogisticRegression {
protected:
    double learningRate;
    int n_iters;
    xt::xarray<double> weights;
    double bias;

public:
    LogisticRegression(double learningRate=0.01, int n_iters=1000) {
      this->learningRate = learningRate;
      this->n_iters = n_iters;
    }

    // Element-wise sigmoid for arrays
    xt::xarray<double> sigmoid(const xt::xarray<double> &z) {
      return 1.0 / (1.0 + xt::exp(-z));
    }

    void fit(const xt::xarray<double> &X, const xt::xarray<double> &Y) {
      std::size_t n_samples = X.shape(0);
      std::size_t n_features = X.shape(1);

      this->weights = xt::zeros<double>({n_features});
      this->bias = 0.0;

      for (int i = 0; i < this->n_iters; i++) {
        // Linear model: shape (n_samples,)
        xt::xarray<double> linear_model = xt::linalg::dot(X, this->weights) + this->bias;

        // Apply sigmoid
        xt::xarray<double> Y_pred = sigmoid(linear_model);

        // Compute gradients
        xt::xarray<double> dw = xt::linalg::dot(xt::transpose(X), (Y_pred - Y)) / n_samples;
        double db = xt::sum(Y_pred - Y)() / n_samples;  // () to extract scalar

        // Update parameters
        this->weights -= this->learningRate * dw;
        this->bias -= this->learningRate * db;
      }
    }

    xt::xarray<double> predict_prob(const xt::xarray<double> &X) {
      xt::xarray<double> linear_model = xt::linalg::dot(X, this->weights) + this->bias;
      return sigmoid(linear_model);
    }

    xt::xarray<int> predict(const xt::xarray<double> &X) {
      xt::xarray<double> Y_prob = predict_prob(X);
      return xt::cast<int>(Y_prob >= 0.5);
    }
};

