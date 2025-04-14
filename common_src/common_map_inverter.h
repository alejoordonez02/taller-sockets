#ifndef MAP_INVERTER_H
#define MAP_INVERTER_H

#include <map>

class MapInverter {
public:
    template <typename K, typename V>
    static std::map<V, K> get_inverse_map(const std::map<K, V>& map) {
        std::map<V, K> inverse_map;
        for (const auto& [key, value]: map) {
            inverse_map[value] = key;
        }
        return inverse_map;
    }
};

#endif
