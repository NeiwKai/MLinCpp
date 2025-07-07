#include <iostream>
#include <stdio.h>
#include <vector>

class regression {
  std::vector<float> x;
  std::vector<float> y;

  float coeff;
  float constTerm;
  float sum_xy;
  float sum_x;
  float sum_y;
  float sum_x_square;
  float sum_y_square;
public:
  regression() {
    this->coeff = 0;
    this->constTerm = 0;
    this->sum_xy = 0;
    this->sum_x = 0;
    this->sum_y = 0;
    this->sum_x_square = 0;
    this->sum_y_square = 0;
  }
  void calculateCoefficient() {
    float N = x.size();
    float numerator = (N * this->sum_xy - this->sum_x * this->sum_y);
    float denominator = (N * this->sum_x_square - this->sum_x * this->sum_x);
    this->coeff = numerator / denominator;
  }
  void calculateConstantTerm() {
    float N = this->x.size();
    float numerator = (this->sum_y * this->sum_x_square - this->sum_x * this->sum_xy);
    float denominator = (N * this->sum_x_square - this->sum_x * this->sum_x);
    this->constTerm = numerator / denominator;
  }
  int sizeOfData() {
    return this->x.size();
  }
  float coefficient() {
    if (this->coeff == 0) {
      this->calculateCoefficient();
    }
    return this->coeff;
  }
  float constant() {
    if (this->constTerm == 0) {
      this->calculateConstantTerm();
    }
    return this->constTerm;
  }
  void PrintBestFittingLine() {
    if (this->coeff == 0 && this->constTerm == 0) {
      this->calculateCoefficient();
      this->calculateConstantTerm();
    }
    std::cout << "The best fitting line is y = " << this->coeff << "x + " << this->constTerm << std::endl;
  }
  void takeInput(int n) {
    for (int i=0; i<n; i++) {
      char comma;
      float xi;
      float yi;
      std::cin >> xi >> comma >> yi;
      this->sum_xy += xi * yi;
      this->sum_x += xi;
      this->sum_y += yi;
      this->sum_x_square += xi * xi;
      this->sum_y_square += yi * yi;
      this->x.push_back(xi);
      this->y.push_back(yi);
    }
  }
  void showData() {
    for (int i=0; i<62; i++) {
      printf("_");
    }
    printf("\n\n");
    printf("|%15s%5s %15s%5s%20s\n", "X", "", "Y", "", "|");
    for (int i=0; i<this->x.size(); i++) {
      printf("|%20f %20f%20s\n", this->x[i], this->y[i], "|");
    }
    for (int i=0; i<62; i++) {
      printf("_");
    }
    printf("\n");
  }
  float predict(float x) {
    return this->coeff * x + this->constTerm;
  }
  float errorSquare() {
    float ans = 0;
    for (int i=0; i<this->x.size(); i++) {
      ans += ((this->predict(this->x[i] - this->y[i]) * (this->predict(this->x[i]) - this->y[i])));
    }
    return ans;
  }
  float errorIn(float num) {
    for (int i=0; i<this->x.size(); i++) {
      if (num == this->x[i]) {
        return (this->y[i] - this->predict(this->x[i]));
      }
    }
    return 0;
  }
};

int main() {
  std::freopen("input.txt", "r", stdin);
  regression reg;

  int n;
  std::cin >> n;

  reg.takeInput(n);
  reg.PrintBestFittingLine();
  std::cout << "Predicted value at 2600 = " << reg.predict(2060) << std::endl;
  std::cout << "The errorSquared = " << reg.errorSquare() << std::endl;
  std::cout << "Error in 2050 = " << reg.errorIn(2050) << std::endl;
  return 0;
}
















