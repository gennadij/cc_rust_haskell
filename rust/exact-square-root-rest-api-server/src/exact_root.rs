#[derive(Debug, PartialEq)]
pub struct Res{
  pub multiplicator : i64,
  pub sqrt :i64
}

pub fn get_exact_sqrt(radicand : i64) -> Vec<Res> {
  if radicand == 0 || radicand == 1 {
    vec![Res{multiplicator : -1, sqrt : radicand}]
  }else{
    let mut exact_sqrt = ExactSqrt::new(radicand);
    exact_sqrt.set_sqrt_and_radicand();
    let simple_sqrt = exact_sqrt.search_simple_sqrt();
    match simple_sqrt {
      Some(res) => {
          vec![Res{multiplicator : -1, sqrt : res}]
      },
      None => {
        let complex_sqrt = exact_sqrt.search_complex_sqrt();
        if !complex_sqrt.is_empty() {
          let mut result : Vec<Res> = vec![];
          for res_ in complex_sqrt{
            result.push(Res{multiplicator : res_.0, sqrt : res_.1})
          }
          result
        }else{ 
          vec![]
        } 
      }
    }
  }
}

struct ExactSqrt {
  sqrt_and_radicand_: Vec<(i64, i64)>,
  radicand_: i64
}

impl ExactSqrt {
  fn new(radicand: i64) -> Self {
    ExactSqrt {sqrt_and_radicand_: vec![], radicand_: radicand}
  }

  fn set_sqrt_and_radicand(&mut self) {
    let mut odd_number: i64 = 1;
    let mut acc :i64 = 1;
    let mut sqrt: i64 = 1;
    loop {
      odd_number += 2;
      acc += odd_number;
      sqrt += 1;
      self.sqrt_and_radicand_.push((sqrt, acc));
      if acc >= self.radicand_ {
        break;
      }
    }
  }

  fn search_simple_sqrt(&mut self) -> Option<i64>{
    let found = self.sqrt_and_radicand_.iter().find(|r_and_s| r_and_s.1 == self.radicand_);

    match found {
      Some(x) => Some(x.0), 
      None => None,
    }


  }
  
  fn search_complex_sqrt(&mut self) -> Vec<(i64, i64)> {
    let mut result: Vec<(i64, i64)> = Vec::new();

    for x  in self.sqrt_and_radicand_.iter() {
      let divisible = self.radicand_ % x.1;
      if divisible == 0 {
        result.push((x.0, (self.radicand_ / x.1)));
      }
    }
    result
  }
}

#[cfg(test)]
mod tests {
  use crate::exact_root::get_exact_sqrt;
  use crate::exact_root::Res;

  #[test]
  fn test_get_exact_sqrt() {
      assert_eq!(get_exact_sqrt(0), vec![Res{multiplicator : -1, sqrt : 0}]);
      assert_eq!(get_exact_sqrt(1), vec![Res{multiplicator : -1, sqrt : 1}]);
      assert_eq!(get_exact_sqrt(2), vec![]);
      assert_eq!(get_exact_sqrt(3), vec![]);
      assert_eq!(get_exact_sqrt(4), vec![Res{multiplicator : -1, sqrt : 2}]);
      assert_eq!(get_exact_sqrt(5), vec![]);
      assert_eq!(get_exact_sqrt(6), vec![]);
      assert_eq!(get_exact_sqrt(7), vec![]);
      assert_eq!(get_exact_sqrt(8), vec![Res{multiplicator : 2, sqrt : 2}]);
      assert_eq!(get_exact_sqrt(9), vec![Res{multiplicator : -1, sqrt : 3}]);
      assert_eq!(get_exact_sqrt(10), vec![]);
      assert_eq!(get_exact_sqrt(100), vec![Res{multiplicator : -1, sqrt : 10}]);
      assert_eq!(get_exact_sqrt(1000), vec![Res { multiplicator: 2, sqrt: 250 }, 
                                                    Res { multiplicator: 5, sqrt: 40 }, 
                                                    Res { multiplicator: 10, sqrt: 10 }]);
      assert_eq!(get_exact_sqrt(123956844), vec![Res{multiplicator : 2, sqrt : 30989211}]);
  }
}