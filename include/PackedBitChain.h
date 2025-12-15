#pragma once

#include "common.h"


/**
 * Implementation of packed chain of bits.
 */
class PackedBitChain {
public:
    PackedBitChain()
    { }

    PackedBitChain(std::vector<bool>& vec)
        : sum(0),
          n(vec.size()),
          data()
    {
        // Reserve space to avoid reallocations
        // Heuristic: assume average run length of 4, plus 2 for edge cases
        data.reserve(vec.size() / 4 + 2);
        
        size_t i = 0;

        while (i < vec.size()) {
            bool cur = data.size() % 2;
            size_t count = 0;
            while (i < vec.size() && vec[i] == cur) {
                ++count;
                ++i;
            }
            if (cur) {
                this->sum += count;
            }
            data.push_back(count);
        }
    }

    PackedBitChain(const PackedBitChain& a, const PackedBitChain& b)
        : sum(0),
          n(a.n),
          data()
    {
        if (a.n > 0) {
            // Reserve space to avoid reallocations
            data.reserve(a.data.size() + b.data.size());
            data.push_back(0);
            Iter iter1(&a);
            Iter iter2(&b);
            bool current_bit = false;  // Track current bit to avoid data.size() % 2

            while (iter1.hasData() && iter2.hasData()) {
                // iter1 is always the chain with greater number in current data
                if (iter1.remainingCount() < iter2.remainingCount()) {
                    std::swap(iter1, iter2);
                }

                bool res = iter1.currentValue() && iter2.currentValue();
                size_t take = iter2.remainingCount();

                if (res == current_bit) {
                    // no match (because data already contains current count)
                    data.push_back(take);
                    current_bit = !current_bit;
                } else {
                    // match - extend current count
                    data.back() += take;
                }

                if (res) {
                    this->sum += take;
                }

                iter1.increment(take);
                iter2.increment(take);
            }
        }
    }

    // Disable copy
    PackedBitChain(const PackedBitChain& other) = delete;
    PackedBitChain& operator=(const PackedBitChain& other) = delete;

    // Allow move
    PackedBitChain(PackedBitChain&& other) = default;
    PackedBitChain& operator=(PackedBitChain&& other) = default;

    inline bool operator[](size_t index) const
    {  return getValue(index); }

    inline bool at(size_t index) const
    {
        if (index >= n) {
            throw std::out_of_range("PackedBitChain::at");
        }

        return getValue(index);
    }

    inline size_t size() const
    { return n; }

    inline bool empty() const
    { return data.empty(); }

    const std::vector<size_t>& raw() const
    { return data; }

    std::string toString() const
    {
        Iter iter(this);
        std::stringstream res;
        res << "[n=" << n << "]";
        while (iter.hasData()) {
            bool cur = iter.currentValue();
            size_t count = iter.remainingCount();
            for (size_t i = 0; i < count; ++i) {
                res << cur;
            }
            iter.increment(count);
        }

        return res.str();
    }

private:
    class Iter {
    public:
        const PackedBitChain* chain;
        size_t index;
        size_t offset;

        Iter(const PackedBitChain* theChain)
            : chain(theChain), index(0), offset(0)
        { }

        inline bool hasData() const
        { return index < chain->data.size(); }

        inline bool currentValue() const
        { return index & 1; }  // Use bitwise AND instead of modulo

        inline size_t remainingCount() const
        { return chain->data[index] - offset; }

        inline void increment(size_t count)
        {
            offset += count;
            if (offset >= chain->data[index]) {
                offset -= chain->data[index];
                index++;
            }
        }
    };

    size_t sum;
    size_t n;
    std::vector<size_t> data;

    inline bool getValue(const size_t index) const
    {
        size_t i = 0;
        size_t pos = 0;
        for (; i < data.size(); ++i) {
            size_t next_pos = pos + data[i];
            if (index < next_pos) {
                break;
            }
            pos = next_pos;
        }

        return i & 1;  // Use bitwise AND instead of modulo
    }
};
