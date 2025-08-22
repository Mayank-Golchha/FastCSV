# FastCSV

It is a very fast CSV parser written in C++ with support for random row access due to which it can read any row in almost constant time

## Features
- Read and write CSV rows efficiently
- Handles large files with chunked reading
- Supports Random Row Access
- Easy integration with existing projects

## Example Usage
```cpp
#include <iostream>
#include "csv.h"

int main() {
    CSV csv("hello_world.csv");

    // Read a specific row
    std::vector<std::string> row = csv.read_row(1000000);
    for (const auto& col : row) {
        std::cout << col << " ";
    }
    std::cout << "\n";

    // Write a row
    std::vector<std::string> data = {"hello", "world", "0"};
    csv.write_row(data);

    return 0;
}
