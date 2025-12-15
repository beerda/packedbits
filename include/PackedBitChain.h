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
        : n(a.n),
          data()
    {
        if (a.n > 0) {
            data.push_back(0);
            Iter iter1(&a);
            Iter iter2(&b);

            while (iter1.hasData() && iter2.hasData()) {
                // iter1 is always the chain with greater number in current data
                if (iter1.remainingCount() < iter2.remainingCount()) {
                    std::swap(iter1, iter2);
                }

                bool value1 = iter1.currentValue();
                bool value2 = iter2.currentValue();
                bool res = value1 && value2;
                size_t take = iter2.remainingCount();

                if (res == (data.size() % 2)) {
                    // no match (because data already contains current count)
                    data.push_back(take);
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

    bool operator[](size_t index) const
    {  return getValue(index); }

    bool at(size_t index) const
    {
        if (index >= n) {
            throw std::out_of_range("PackedBitChain::at");
        }

        return getValue(index);
    }

    size_t size() const
    { return n; }

    bool empty() const
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

        bool hasData() const
        { return index < chain->data.size(); }

        bool currentValue() const
        { return index % 2; }

        size_t remainingCount() const
        { return chain->data[index] - offset; }

        void increment(size_t count)
        {
            offset += count;
            if (offset >= chain->data[index]) {
                offset -= chain->data[index];
                index++;
            }
        }
    };

    float sum;
    size_t n;
    std::vector<size_t> data;

    bool getValue(const size_t index) const
    {
        size_t i = 0;
        size_t pos = 0;
        for (; i < data.size(); ++i) {
            if (index < pos + data[i]) {
                break;
            }
            pos += data[i];
        }

        return i % 2;
    }
};
