#pragma once

#include <cstdint>
#include <vector>

// Common definitions for packedbits

using BitSet = std::vector<uint64_t>;

// Fast ceiling of positive numbers
#define UNSIGNED_CEILING(a, b)  ((a) + (b) - 1) / (b)
