#include <iostream>
#include <tbb/tbb.h>
#include <algorithm>
#include <vector>
#include <random>
#include <math.h>

void saxpy_serial(
  float a, // scale factor
  const std::vector<int> x, // input
  std::vector<int> y // output vector
) {
  for (size_t i = 0; i < x.size(); i++) {
    y[i] = a * x[i];
  }
}

void saxpy_tbb(
  float a, // scale factor
  const std::vector<int> x, // input
  std::vector<int> y // output vector
) {
  tbb::parallel_for(
    tbb::blocked_range<int>(0, x.size()),
    [&](tbb::blocked_range<int> r) {
      for (size_t i = r.begin(); i != r.end(); i++) {
        y[i] = a * x[i];
      }
    }
  );
}

void fill_tbb(
  std::uniform_int_distribution<int> uid,
  std::default_random_engine dre,
  std::vector<int> *x
) {
  tbb::parallel_for(
    tbb::blocked_range<int>(0, x->size()),
    [&](tbb::blocked_range<int> r) {
      for (size_t i = r.begin(); i != r.end(); i++) {
        x->assign(i, uid(dre));
      }
    }
  );
}

int main () {
  const int size = pow(2, 10);
  auto x = std::vector<int>(size);
  auto y = std::vector<int>(size);

  std::random_device rd;
  std::default_random_engine dre(rd());
  std::uniform_int_distribution<int> uid(0, 99);

  // generate values
  auto a = uid(dre);
  fill_tbb(uid, dre, &x);

  const int sampleMax = 1000;

  std::cout << "Sample set:\n";
  for(auto iter = x.begin(); iter < x.begin() + sampleMax; iter++) {
    std::cout << *iter << ' ';
  }
  std::cout << '\n';
}