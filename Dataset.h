#include "AGenerator.h"
#include <unordered_map>
#include <string>
#include <ostream>
#include <vector>
#include <iomanip>

class Dataset {
  public:
    Dataset(std::unordered_map<std::string, AGenerator*> mapping) : mapping(mapping) {
      auto it = mapping.begin();
      len = it->second->size();
    }

    // Requires: each column in columns is also in the mapping
    void print(std::ostream& out, std::vector<std::string>& columns) {
      for (std::string& col : columns) {
        out << col << ",";
      }
      out << "\n";

      for (int i = 0; i < len; ++i) {
        for (std::string& col : columns) {
          out << std::fixed << std::setprecision(3) << mapping[col]->get(i) << ",";
        }
        out << "\n";
      }
    }

    // Requires: run after initialization ... duh
    void warmup_step(int steps) {
        for (int i = 0; i < steps; ++i) {
            for (auto it = mapping.begin(); it != mapping.end(); ++it) {
                it->second->step();
            }
        }
    }

  private:
    std::unordered_map<std::string, AGenerator*> mapping;
    int len;
};
