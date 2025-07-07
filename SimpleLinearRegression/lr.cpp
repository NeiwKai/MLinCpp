#include<bits/stdc++.h> // header file for all c++ libraries
//#include <iostream>
//#include <vector>

bool custom_sort(double a, double b) /* this custom sort function is defined to 
                                     sort on basis of min absolute value or error*/
{
    double  a1=abs(a-0);
    double  b1=abs(b-0);
    return a1<b1;
}
int main() {
  /*Intialization Phase*/
  double x[] = {1, 2, 4, 3, 5};    // defining x values
  double y[] = {1, 3, 3, 2, 5};    // defining y values
  std::vector<double>error;             // array to store all error values
  double err;
  double b0 = 0;                   //initializing b0
  double b1 = 0;                   //initializing b1
  double learningRate = 0.01;             //intializing error rate
   
  /*Training Phase*/
  for (int i = 0; i < 20; i ++) {   // since there are 5 values and we want 4 epochs so run for loop for 20 times
      int idx = i % 5;              //for accessing index after every epoch
      double p = b0 + b1 * x[idx];  //calculating prediction ( Y = B0 - B1 * X )
      err = p - y[idx];              // calculating error ( e = p - y [of ith] ) y is actual value
      b0 = b0 - learningRate * err;         // updating b0
      b1 = b1 - learningRate * err * x[idx];// updating b1
      std::cout << "B0=" << b0 << " " << "B1=" << b1 << " " << "error=" << err << std::endl;// printing values after every updation
      error.push_back(err);
  }
  sort(error.begin(),error.end(),custom_sort); // sorting based on error values
  std::cout << "Final Values are: " << "B0=" << b0 << " " << "B1=" << b1 << " " << "error=" << error[0] << std::endl;

  /*Testing Phase*/
  std::cout << "Enter a test x value: ";
  double test;
  std::cin >> test;
  double pred=b0+b1*test;
  std::cout << std::endl;
  std::cout << "The value predicted by the model= " << pred;
}
