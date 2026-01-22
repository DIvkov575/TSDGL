#include "AGenerator.h"
#include <functional>

class CGenerator : public AGenerator {
  public:
    CGenerator();

    double get(int idx) override;

    double get_last(int idx) override;

    void set_func(std::function<double()> func) override;

    double run_func() override;

    void step() override;
    
    void seed(std::vector<double>);

    int size() override;

    double operator[](int);

  private:
    std::vector<double> data;
    std::function<double()> function;
};

