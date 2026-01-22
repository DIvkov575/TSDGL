#include <csv.hpp>
#include <gnuplot-iostream.h>
#include <vector>
#include <string>

int main() {
    csv::CSVReader reader("data.csv");

    std::vector<double> x;
    std::vector<std::vector<double>> ys;
    std::vector<std::string> colnames;

    bool initialized = false;

    for (auto& row : reader) {
        if (!initialized) {
            // first column is x, rest are y's
            colnames = row.get_col_names();
            ys.resize(colnames.size() - 1);
            initialized = true;
        }

        x.push_back(row[0].get<double>());
        for (size_t j = 1; j < colnames.size(); ++j) {
            ys[j - 1].push_back(row[j].get<double>());
        }
    }

    Gnuplot gp;
    gp << "set key outside\n";
    gp << "plot ";

    for (size_t j = 0; j < ys.size(); ++j) {
        gp << gp.file1d(std::make_pair(x, ys[j]))
           << "with lines title '" << colnames[j + 1] << "'";
        if (j + 1 < ys.size()) gp << ", ";
    }
    gp << "\n";
}

