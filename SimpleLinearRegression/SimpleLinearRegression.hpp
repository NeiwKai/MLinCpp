class SimpleLinearRegression {
  protected:
    double learningRate;
    double a; // Coefficient
    double b; // Constant
    double sum_xy;
    double sum_x;
    double sum_y;
    double sum_x_square;

  public:
    SimpleLinearRegression(double learningRate) {
      this->learningRate = learningRate;
      this->a = 0;
      this->b = 0;
      this->sum_xy = 0;
      this->sum_x = 0;
      this->sum_y = 0;
      this->sum_x_square = 0;
    }
    void fit(xt::xarray<double> &X_train, xt::xarray<double> &Y_train) {
      for (int i=0; i<X_train.size(); i++) {
        double Y_pred = this->a*X_train[i] + this->b;
        double err = Y_pred - Y_train[i];
        this->a = this->a - this->learningRate * err;
        this->b = this->b - this->learningRate * err;
        this->sum_xy += X_train[i] * Y_train[i];
        this->sum_x += X_train[i];
        this->sum_y += Y_train[i];
        this->sum_x_square += pow(X_train[i], 2);
      }
      this->cal_Coeff(X_train.size());
      this->cal_Constant(X_train.size());
    }
    xt::xarray<double> predict(xt::xarray<double> X) {
      return this->a*X + this->b;
    }
    void cal_Coeff(int N) {
      double numerator = N*this->sum_xy - this->sum_x*this->sum_y;
      double denominator = N*this->sum_x_square - this->sum_x*this->sum_x;
      this->a = numerator / denominator;
      //std::cout << "Best Fitting Line for Coefficient(a) is " << this->a << "\n";
    }
    void cal_Constant(int N) {
      double numerator = this->sum_y*this->sum_x_square - this->sum_x*this->sum_xy;
      double denominator = N*this->sum_x_square - this->sum_x*this->sum_x;
      this->b = numerator / denominator;
      //std::cout << "Best Fitting Line for Constant(b) is " << this->b << "\n";
    }
};
