#include <algorithm>
#include "UpdateProcMap.h"


int ProcMap::insert_update(const MapNode& node) {
    bool found = false;
    auto it = map.begin();
    int i = 0;
    while (!found && it != map.end()) {
        found = node._index == map[i]._index;
        ++it;
        ++i;
    }

    if (found) {
        // printf("node: %d, %lf, %lf\n", node._index, node._data, node._timestamp);
        // printf("map[i]: %d, %lf, %lf\n", map[i]._index, map[i]._data, map[i]._timestamp);
        auto replace = most_recent(node, map[i]);
        // printf("replace: %d,% lf, %lf\n", replace._index, replace._data, replace._timestamp);
        map[i] = replace;
        if (node._timestamp > replace._timestamp) { //The value was not replaced
            return 0;
        } else { // The value was replaced
            std::make_heap(map.begin(), map.end(), [](MapNode lhs, MapNode rhs) {
                return lhs._data < rhs._data;
            } ) ; // Use greater in order to create a min_heap)
            return 1;
        }
    } else {
        // Create new node;
        map.push_back(node);
        std::push_heap(map.begin(), map.end(), [](MapNode lhs, MapNode rhs) {
            return lhs._data < rhs._data;
        } ) ; // Use greater in order to create a min_heap
        return 2;
    }
    return 0;
}

const MapNode& ProcMap::most_recent(const MapNode& a, const MapNode& b) {
    return (a._timestamp > b._timestamp ? a : b);
}

int ProcMap::size() {
    return map.size();
}

std::pair<int,double> ProcMap::first() const {
    if (map.size() < 1) {
        return std::move(std::make_pair(-1,-1.0));
    }

    std::vector<MapNode> map_cpy = map; // Create a local cpy
    std::sort_heap(map_cpy.begin(), map_cpy.end(), [](MapNode lhs, MapNode rhs) {
        return lhs._data < rhs._data;
    });

    auto node = map_cpy.front();
    return std::make_pair(node._index, node._data);
}

std::pair<int, double> ProcMap::last() const {
    if (map.size() < 1) {
        return std::make_pair(-1,-1.0);
    }

    std::vector<MapNode> map_cpy = map; // Create a local cpy
    std::sort_heap(map_cpy.begin(), map_cpy.end(), [](MapNode lhs, MapNode rhs) {
        return lhs._data < rhs._data;
    });

    auto node = map_cpy.back();
    return std::make_pair(node._index, node._data);
}

void ProcMap::vectorize_data(int *indexes, double *loads, double *timestamps) {
    std::vector<MapNode> map_cpy = map; // Create a local cpy
    std::sort_heap(map_cpy.begin(), map_cpy.end(), [](MapNode lhs, MapNode rhs) {
        return lhs._data < rhs._data;
    });
    int i = 0;
    for (auto node : map_cpy) {
        indexes[i] = node._index;
        loads[i] = node._data;
        timestamps[i] = node._timestamp;
        i++;
    }
}
