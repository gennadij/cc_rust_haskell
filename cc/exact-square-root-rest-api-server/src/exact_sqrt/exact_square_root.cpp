#include "exact_square_root.h"
#include <iostream>
#include <chrono>

namespace exact_square_root {
std::vector<Res> ExactSquareRoot::GetExactSqrt(){
  auto start = std::chrono::high_resolution_clock::now();
  if(radicand_  == 0 || radicand_ == 1){
    return {{-1, radicand_}};
  }

  auto timepoint_1 = std::chrono::high_resolution_clock::now();
  auto duration_1 = std::chrono::duration_cast<std::chrono::milliseconds>(timepoint_1 - start).count();
  std::cout << "Timepoint 1: " << duration_1 << " Millisekunden\n";

  SetSqrtAndRadicand();
  
  auto const simple_sqrt{SearchSimpleSqrt()}; 

  // auto timepoint_4 = std::chrono::high_resolution_clock::now();
  // auto duration_4 = std::chrono::duration_cast<std::chrono::milliseconds>(timepoint_4 - timepoint_3).count();
  // std::cout << "Timepoint simple sqrt: " << duration_4 << " Millisekunden\n";

  if(simple_sqrt.has_value()){
    return {{-1, simple_sqrt.value()}};
  }
  auto const complex_sqrts{SearchComplexSqrt()};

  auto timepoint_2 = std::chrono::high_resolution_clock::now();
  auto duration_all = std::chrono::duration_cast<std::chrono::milliseconds>(timepoint_2 - start).count();
  std::cout << "Timepoint complex sqrt: " << duration_all << " Millisekunden\n";

  if(complex_sqrts.empty()){
    return {};
  }else{
    std::vector<Res> r;
    for(const auto& complex_sqrt : complex_sqrts){
      r.push_back({complex_sqrt.first, complex_sqrt.second});
    }
    return r;
  }
}

void ExactSquareRoot::SetSqrtAndRadicand(){
  int64_t odd_number{1};
  int64_t acc{1};
  int64_t sqrt{1};
  while(true){
    odd_number += 2;
    acc += odd_number;
    sqrt += 1;
    sqrt_and_radicand_.push_back({sqrt, acc});
    if(acc >= radicand_) break;
  }
}

std::optional<int64_t> ExactSquareRoot::SearchSimpleSqrt(){
  auto it = std::ranges::find_if(
    sqrt_and_radicand_, [this](const auto& r_and_s){return r_and_s.second == radicand_;});
  if(it != sqrt_and_radicand_.end()){
    return it->first;
  }else{
    return std::nullopt;
  }
}

std::vector<std::pair<int64_t, int64_t>> ExactSquareRoot::SearchComplexSqrt(){
  std::vector<std::pair<int64_t, int64_t>> result;
  for(const auto& r_and_s : sqrt_and_radicand_){
    int64_t divisible = radicand_ % r_and_s.second;
    if(divisible == 0){
      result.push_back({r_and_s.first, (radicand_ / r_and_s.second)});
    }
  }
  return result;
}
}