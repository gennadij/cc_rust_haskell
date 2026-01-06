#include "exact_square_root.h"
#include <ranges>
#include <numeric>
#include <iostream>

namespace exact_square_root {
std::vector<Res> ExactSquareRoot::GetExactSqrt(){
  if(radicand_  == 0 || radicand_ == 1){
    return {{-1, radicand_}};
  }

  const auto odd_numbers = GetOddNumbers();
  const auto default_sqrts = CalcDefaultSqrts(odd_numbers);
  
  // TODO
  //std::vector<int>&&
  //std::vector<int>&
  ZipRadicandsAndDefaultSqrts(default_sqrts);
  auto const simple_sqrt{SearchSimpleSqrt()}; 
  if(simple_sqrt.has_value()){
    return {{-1, simple_sqrt.value()}};
  }
  auto const complex_sqrts{SearchComplexSqrt()};
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

std::vector<int> ExactSquareRoot::CalcDefaultSqrts(std::vector<int> odd_numbers){
  if(odd_numbers.size() < 2){
    return {};
  }

  // TODO: im rust auch aenliche Methode wie partial sum finden. 
  std::vector<int> result;
  result.reserve(odd_numbers.size());
  std::partial_sum(odd_numbers.begin(), odd_numbers.end(), std::back_inserter(result));
  result.erase(result.begin());
  
  return result;
}

std::vector<int> ExactSquareRoot::GetOddNumbers(){
  if(radicand_ < 1){
    return {};
  }
  std::vector<int> odds;
  for (int x : std::views::iota(1, radicand_) | std::views::filter([](int x){ return x & 1; })){
    odds.push_back(x);
  }
  return odds;
}

void ExactSquareRoot::ZipRadicandsAndDefaultSqrts(std::vector<int> default_sqrts){
  std::vector<int> radicands(default_sqrts.size());
  std::iota(radicands.begin(), radicands.end(), 2);
  for(int i = 0; i < radicands.size(); ++i){
    radicand_and_sqrt_.push_back({radicands.at(i), default_sqrts.at(i)});
  }
}

std::optional<int> ExactSquareRoot::SearchSimpleSqrt(){
  auto it = std::ranges::find_if(
    radicand_and_sqrt_, [this](const auto& r_and_s){return r_and_s.second == radicand_;});
  if(it != radicand_and_sqrt_.end()){
    return it->first;
  }else{
    return std::nullopt;
  }
}

std::vector<std::pair<int, int>> ExactSquareRoot::SearchComplexSqrt(){
  std::vector<std::pair<int, int>> result;
  for(const auto& r_and_s : radicand_and_sqrt_){
    int divisible = radicand_ % r_and_s.second;
    if(divisible == 0){
      result.push_back({r_and_s.first, (radicand_ / r_and_s.second)});
    }
  }
  return result;
}
}