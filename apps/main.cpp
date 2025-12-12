#include <benchmark/benchmark.h>
#include "common.h"

#define LENGTH 16777216  // 2^24

class BitSetFixture : public benchmark::Fixture {
public:
    BitSet set1;
    BitSet set2;
    uint64_t result = 0;

    void SetUp(::benchmark::State& state)
    {
        srand(1234);
        for (size_t i = 0; i < LENGTH / 64; i++) {
            set1.push_back(rand());
            set2.push_back(rand());
        }
    }

    void TearDown(::benchmark::State& state)
    {
        set1.clear();
        set2.clear();
    }
};

BENCHMARK_F(BitSetFixture, BitwiseAND)(benchmark::State& st)
{
    for (auto _ : st) {
        for (size_t i = 0; i < set1.size(); i++) {
            result += set1[i] & set2[i];
        }
    }
}

BENCHMARK_MAIN();
