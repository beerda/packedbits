#include <benchmark/benchmark.h>
#include "common.h"
#include <boost/dynamic_bitset.hpp>

#define LENGTH 16777216  // 2^24
#define BOOST_BITSET_SIZE 64000  // Size for boost::dynamic_bitset benchmark

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

class BoostBitSetFixture : public benchmark::Fixture {
public:
    boost::dynamic_bitset<> set1;
    boost::dynamic_bitset<> set2;
    boost::dynamic_bitset<> result;

    void SetUp(::benchmark::State& state)
    {
        set1.resize(BOOST_BITSET_SIZE);
        set2.resize(BOOST_BITSET_SIZE);
        result.resize(BOOST_BITSET_SIZE);
        
        srand(1234);
        for (size_t i = 0; i < BOOST_BITSET_SIZE; i++) {
            set1[i] = rand() % 2;
            set2[i] = rand() % 2;
        }
    }

    void TearDown(::benchmark::State& state)
    {
        set1.clear();
        set2.clear();
        result.clear();
    }
};

BENCHMARK_F(BoostBitSetFixture, BitwiseAND)(benchmark::State& st)
{
    for (auto _ : st) {
        result = set1 & set2;
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK_MAIN();
