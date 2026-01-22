#include "Dataset.h"
#include "CGenerator.h"
#include "Noise.h"
#include <iostream>
#include <string>
#include <cmath>

Noise* ns = new Noise();
int t = 0;

int main() {
  
  CGenerator* A1 = new CGenerator(); // dx = dB_t
  A1->seed({0.0});
  A1->set_func([A1](){
      return (*A1)[-1] + ns->gaussian(0,2);
  });


  CGenerator* A2 = new CGenerator(); // 2 * A1_{t-1}
  A2->seed({0.0});
  A2->set_func([A1](){
      return (*A1)[-1] * 2;
  });


  CGenerator* B1 = new CGenerator(); // Random walk w/ 0,5 gaussian
  B1->seed({0.0});
  B1->set_func([B1](){
      return (*B1)[-1] + ns->gaussian(0, 5);
  });

  CGenerator* C1 = new CGenerator(); // Sine wave
  C1->seed({0.0});
  C1->set_func([](){
      t++;
      return sin(static_cast<double>(t) / 10.0);
  });


  // Generate 100 steps for all generators
  for (int i = 0; i < 100; ++i) {
      A1->step();
      A2->step();
      B1->step();
      C1->step();
  }

  // Create dataset with all generators
  Dataset ds = Dataset({
      {"A1", A1},
      {"A2", A2},
      {"B1", B1},
      {"C1", C1}
  });

  std::vector<std::string> cols = {"A1", "A2", "B1", "C1"};
  ds.print(std::cout, cols);






  
  

  return 0;
}
