class LinearRegression {
  protected:
    std::vector<double> X_train;
    std::vector<double> Y_train;
    double learningRate;
    double a; // Coefficient
    double b; // Constant
    double sum_xy;
    double sum_x;
    double sum_y;
    double sum_x_square;

  public:
    LinearRegression(double learningRate) {
      this->learningRate = learningRate;
      this->a = 0;
      this->b = 0;
      this->sum_xy = 0;
      this->sum_x = 0;
      this->sum_y = 0;
      this->sum_x_square = 0;
    }
    void set_X_train(const std::vector<double> &input) {
      this->X_train = input;
    }
    void set_Y_train(const std::vector<double> &input) {
      this->Y_train = input;
    }
    void train() {
      int N = this->X_train.size();
      int epochs = 5 * N;
      int counter = 0;
      for (int i=0; i<epochs; i++) {
        int idx = i % N;
        double Y_pred = this->a*this->X_train[idx] + this->b;
        double err = Y_pred - this->Y_train[idx];
        std::cout << "Epoch #" << i+1 << " X_train: " << this->X_train[idx] << " Y_train: " << this->Y_train[idx] << " Y_pred: " << Y_pred << " err: " << err << std::endl;
        this->a = this->a - this->learningRate * err;
        this->b = this->b - this->learningRate * err;

        if (counter < N) {
          this->sum_xy += this->X_train[idx] * this->Y_train[idx];
          this->sum_x += this->X_train[idx];
          this->sum_y += this->Y_train[idx];
          this->sum_x_square += pow(this->X_train[idx], 2);
        }
        counter++;
      }
      std::cout << std::endl;
      /*
      this->cal_Coeff();
      this->cal_Constant();
      */
    }
    double predict(double X) {
      return this->a*X + this->b;
    }
    void cal_Coeff() {
      int N = this->X_train.size();
      double numerator = N*this->sum_xy - this->sum_x*this->sum_y;
      double denominator = N*this->sum_x_square - this->sum_x*this->sum_x;
      this->a = numerator / denominator;
      //std::cout << "Best Fitting Line for Coefficient(a) is " << this->a << std::endl;
    }
    void cal_Constant() {
      int N = this->X_train.size();
      double numerator = this->sum_y*this->sum_x_square - this->sum_x*this->sum_xy;
      double denominator = N*this->sum_x_square - this->sum_x*this->sum_x;
      this->b = numerator / denominator;
      //std::cout << "Best Fitting Line for Constant(b) is " << this->b << std::endl;
    }
};
