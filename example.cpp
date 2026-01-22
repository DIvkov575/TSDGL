#include "Dataset.h"
#include "CGenerator.h"
#include "Noise.h"
#include <iostream>
#include <string>

Noise* ns = new Noise();

int main() {
  

  CGenerator* cgen = new CGenerator();
  std::vector<double> seed = {0.0};
  cgen->seed(seed);
  cgen->set_func([cgen](){
      return cgen->get_last(cgen->size() - 1) + ns->gaussian();
  });
  for (int i = 0; i < 5; ++i) { cgen->step(); }

  Dataset ds = Dataset({ {"A1", cgen} });

  std::vector<std::string> cols = {"A1"};
  ds.print(std::cout, cols);






  
  

  return 0;
}
