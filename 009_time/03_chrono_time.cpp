#include <chrono>
using namespace std::chrono;

auto cul_start = std::chrono::steady_clock::now();
auto cul_t1 = std::chrono::steady_clock::now();
printf("remap use time %d ms\n",duration_cast<milliseconds>(cul_t1-cul_start).count());