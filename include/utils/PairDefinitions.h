
#ifndef PAIRDEFINITIONS_H
#define PAIRDEFINITIONS_H

#include <utility>
#include <functional>

namespace Utilities {

    struct PairHash {
        template<typename T>
        std::size_t operator()(const std::pair<T*, T*>& p) const noexcept {
            auto hash1 = std::hash<T*>{}(p.first);
            auto hash2 = std::hash<T*>{}(p.second);
            return hash1 ^ (hash2 << 1);
        }
    };

    struct PairEqual {
        template<typename T>
        bool operator()(const std::pair<T*, T*>& lhs, const std::pair<T*, T*>& rhs) const noexcept {
            return lhs.first == rhs.first && lhs.second == rhs.second;
        }
    };
}

#endif 

