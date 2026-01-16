#ifndef EXACT_SQUARE_ROOT_H
#define EXACT_SQUARE_ROOT_H

#include <vector>
#include <optional>
#include <stdint.h>

namespace exact_square_root {

struct Res{
  int64_t multiplicator{0};
  int64_t square_root{0};
};

class ExactSquareRoot {
  public:
  ExactSquareRoot(int64_t radicand) : radicand_(radicand){};
  std::vector<Res> GetExactSqrt();

  // new imperative Implementation
  std::optional<int64_t> SearchSimpleSqrt();
  std::vector<std::pair<int64_t, int64_t>> SearchComplexSqrt();
  
  private:
  void SetSqrtAndRadicand();
  
  int64_t radicand_{0};
  std::vector<std::pair<int64_t, int64_t>> sqrt_and_radicand_;
};
}
#endif // EXACT_SQUARE_ROOT_H