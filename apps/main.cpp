#include <benchmark/benchmark.h>
#include "common.h"
#include "PackedBitChain.h"
#include <boost/dynamic_bitset.hpp>



template <size_t CH1, size_t CH2>
class PackedBitChainFixture : public benchmark::Fixture {
public:
    PackedBitChain set1;
    PackedBitChain set2;
    uint64_t result = 0;

    void SetUp(::benchmark::State& state)
    {
        size_t totalSize = CH1 * CH2;
        std::vector<bool> vec1;
        std::vector<bool> vec2;

        for (size_t j = 0; j < CH1 / 2; j++) {
            for (size_t i = 0; i < CH2; i++) {
                vec1.push_back(false);
            }
            for (size_t i = 0; i < CH2; i++) {
                vec1.push_back(true);
            }
        }

        for (size_t j = 0; j < CH2 / 2; j++) {
            for (size_t i = 0; i < CH1; i++) {
                vec2.push_back(false);
            }
            for (size_t i = 0; i < CH1; i++) {
                vec2.push_back(true);
            }
        }


        set1 = PackedBitChain(vec1);
        set2 = PackedBitChain(vec2);
        // std::cout << "set1 size: " << set1.size() << "  rawsize: " << set1.raw().size() << std::endl; 
        // std::cout << "set2 size: " << set2.size() << "  rawsize: " << set2.raw().size() << std::endl; 
        // std::cout << "set1: " << set1.toString() << std::endl;
        // std::cout << "set2: " << set2.toString() << std::endl;
    }

    void TearDown(::benchmark::State& state)
    { }
};
            

#define BENCHMARK_PACKED_BITCHAIN(name, ch1, ch2) BENCHMARK_TEMPLATE_F(PackedBitChainFixture, name, ch1, ch2)(benchmark::State& st) \
    {                                           \
        for (auto _ : st) {                     \
            PackedBitChain result(set1, set2);  \
            benchmark::DoNotOptimize(result);   \
        }                                       \
    }


template <size_t BOOST_BITSET_SIZE>
class BoostBitChainFixture : public benchmark::Fixture {
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

#define BENCHMARK_BOOST_BITCHAIN(name, ch) BENCHMARK_TEMPLATE_F(BoostBitChainFixture, name, ch)(benchmark::State& st) \
    {                                           \
        for (auto _ : st) {                     \
            result = set1 & set2;               \
            size_t cc = result.count();         \
            benchmark::DoNotOptimize(cc);       \
        }                                       \
    }

BENCHMARK_PACKED_BITCHAIN(packed2_2, 2, 2)
BENCHMARK_PACKED_BITCHAIN(packed2_4, 2, 4)
BENCHMARK_PACKED_BITCHAIN(packed2_8, 2, 8)
BENCHMARK_PACKED_BITCHAIN(packed2_16, 2, 16)
BENCHMARK_PACKED_BITCHAIN(packed2_32, 2, 32)
BENCHMARK_PACKED_BITCHAIN(packed2_64, 2, 64)
BENCHMARK_PACKED_BITCHAIN(packed2_128, 2, 128)

BENCHMARK_PACKED_BITCHAIN(packed4_4, 4, 4)
BENCHMARK_PACKED_BITCHAIN(packed4_8, 4, 8)
BENCHMARK_PACKED_BITCHAIN(packed4_16, 4, 16)
BENCHMARK_PACKED_BITCHAIN(packed4_32, 4, 32)
BENCHMARK_PACKED_BITCHAIN(packed4_64, 4, 64)
BENCHMARK_PACKED_BITCHAIN(packed4_128, 4, 128)

BENCHMARK_PACKED_BITCHAIN(packed8_8, 8, 8)
BENCHMARK_PACKED_BITCHAIN(packed8_16, 8, 16)
BENCHMARK_PACKED_BITCHAIN(packed8_32, 8, 32)
BENCHMARK_PACKED_BITCHAIN(packed8_64, 8, 64)
BENCHMARK_PACKED_BITCHAIN(packed8_128, 8, 128)

BENCHMARK_PACKED_BITCHAIN(packed16_16, 16, 16)
BENCHMARK_PACKED_BITCHAIN(packed16_32, 16, 32)
BENCHMARK_PACKED_BITCHAIN(packed16_64, 16, 64)
BENCHMARK_PACKED_BITCHAIN(packed16_128, 16, 128)

BENCHMARK_PACKED_BITCHAIN(packed32_32, 32, 32)
BENCHMARK_PACKED_BITCHAIN(packed32_64, 32, 64)
BENCHMARK_PACKED_BITCHAIN(packed32_128, 32, 128)

BENCHMARK_PACKED_BITCHAIN(packed64_64, 64, 64)
BENCHMARK_PACKED_BITCHAIN(packed64_128, 64, 128)

BENCHMARK_PACKED_BITCHAIN(packed128_128, 128, 128)

BENCHMARK_BOOST_BITCHAIN(boost_1, 64 * 1)
BENCHMARK_BOOST_BITCHAIN(boost_2, 64 * 1 << 1)
BENCHMARK_BOOST_BITCHAIN(boost_3, 64 * 1 << 2)
BENCHMARK_BOOST_BITCHAIN(boost_4, 64 * 1 << 3)
BENCHMARK_BOOST_BITCHAIN(boost_5, 64 * 1 << 4)
BENCHMARK_BOOST_BITCHAIN(boost_6, 64 * 1 << 5)
BENCHMARK_BOOST_BITCHAIN(boost_7, 64 * 1 << 6)
BENCHMARK_BOOST_BITCHAIN(boost_8, 64 * 1 << 7)
BENCHMARK_BOOST_BITCHAIN(boost_9, 64 * 1 << 8)
BENCHMARK_BOOST_BITCHAIN(boost_10, 64 * 1 << 9)
BENCHMARK_BOOST_BITCHAIN(boost_11, 64 * 1 << 10)




BENCHMARK_MAIN();
