#pragma once
#include <vector>
#include <functional>

class AGenerator {
public:
    // virtual ~AGenerator() = default;

    virtual double get(int) = 0;

    virtual double get_last(int) = 0;

    virtual void set_func(std::function<double()>) = 0;

    virtual double run_func() = 0;
     
    virtual void step() = 0;

    virtual int size() = 0;


private:
    std::vector<double> data;
    std::function<double()> function;
};
