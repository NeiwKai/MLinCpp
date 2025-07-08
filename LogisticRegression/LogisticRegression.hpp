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
        this->bias = 0.0;
    }

    // Element-wise sigmoid for arrays
    xt::xarray<double> sigmoid(const xt::xarray<double>& z) {
        return 1.0 / (1.0 + xt::exp(-z));
    }

    void fit(const xt::xarray<double>& X, const xt::xarray<double>& y) {
        std::size_t n_samples = X.shape(0);
        std::size_t n_features = X.shape(1);

        weights = xt::zeros<double>({n_features});
        bias = 0.0;

        for (int i = 0; i < n_iters; i++) {
            // Linear model: shape (n_samples,)
            xt::xarray<double> linear_model = xt::linalg::dot(X, weights) + bias;

            // Apply sigmoid
            xt::xarray<double> y_pred = sigmoid(linear_model);

            // Compute gradients
            xt::xarray<double> dw = xt::linalg::dot(xt::transpose(X), (y_pred - y)) / n_samples;
            double db = xt::sum(y_pred - y)() / n_samples;  // () to extract scalar

            // Update parameters
            weights -= learningRate * dw;
            bias -= learningRate * db;
        }
    }

    xt::xarray<double> predict_prob(const xt::xarray<double>& X) {
        xt::xarray<double> linear_model = xt::linalg::dot(X, weights) + bias;
        return sigmoid(linear_model);
    }

    xt::xarray<int> predict(const xt::xarray<double>& X) {
        xt::xarray<double> y_prob = predict_prob(X);
        // Threshold at 0.5
      return xt::cast<int>(y_prob >= 0.5);
    }
};

