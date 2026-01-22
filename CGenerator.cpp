#include "CGenerator.h"

CGenerator::CGenerator() {}

// Requires: idx within range
// Modifies: None
// Effects: Returns element at index idx
double CGenerator::get(int idx) {
    return data[idx];
}

// Requires: contains data, idx within range
// Modifies: None
// Effects: Returns element at index idx (for compatibility with base class)
double CGenerator::get_last(int idx) {
    return data[idx];
}

void CGenerator::set_func(std::function<double()> func) {
    function = func;
}

double CGenerator::run_func() {
    return function();
}

void CGenerator::step() {
    data.push_back(run_func());
}

// Requires: valid seed (probably non empty)
// Modifies: data - replaced with seed
void CGenerator::seed(std::vector<double> seed_vec) {
    data = seed_vec;
}


int CGenerator::size() {
  return data.size();
}

double CGenerator::operator[](int idx) {
    if (idx < 0) {
        return data[size() + idx];
    } else {
        return data[idx];
    }
}
