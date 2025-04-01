#include <iostream>
#include <vector>
#include "algorithms/QuickSort.h"
#include "config/ConfigParser.h"
#include "data_generation/DataGenerator.h"
#include "utils/Helpers.h"
#include "utils/Timer.h"

int main(int argc, char* argv[]) {
    try {
        Config config = Config::parse("../config/config.txt");
        std::vector<int> data(config.array_size);

        if (!config.input_file.empty()) {
            data = Helpers::loadVectorFromFile<int>(config.input_file);
        } else {
            generateData(data, config.array_type);
        }

        Timer timer;
        timer.startTimer();
        QuickSort::sort(data.data(), data.size());
        std::cout << "Time: " << timer.getElapsedMillis() << " ms\n";

        if (!Helpers::isSorted(data.data(), data.size())) {
            throw std::runtime_error("Sorting failed");
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}