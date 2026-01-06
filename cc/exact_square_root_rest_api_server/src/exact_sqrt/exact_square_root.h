#ifndef EXACT_SQUARE_ROOT_H
#define EXACT_SQUARE_ROOT_H

#include <vector>
#include <optional>
#include <utility>

namespace exact_square_root {

struct Res{
  int multiplicator{0};
  int square_root{0};
};

class ExactSquareRoot {

  public:

  ExactSquareRoot(int radicand) : radicand_(radicand){};

  std::vector<Res> GetExactSqrt();
  // Only for debug purpose
  std::vector<int> GetOddNumbers();
  std::vector<int> CalcDefaultSqrts(std::vector<int> odd_numbers);
  void ZipRadicandsAndDefaultSqrts(std::vector<int> default_sqrts);
  std::optional<int> SearchSimpleSqrt();
  std::vector<std::pair<int, int>> SearchComplexSqrt();
  std::vector<std::pair<int, int>> GetRadicandAndSqrts() {return radicand_and_sqrt_;}


  private:


  int radicand_{0};
  std::vector<std::pair<int, int>> radicand_and_sqrt_;
};
}
#endif // EXACT_SQUARE_ROOT_H