// Description for an updatable proc map, a vector-based hash-ordered structure
// for storing PE information

#ifndef UPDATABLE_PE_MAP_H
#define UPDATABLE_PE_MAP_H

#include <vector>
#include <map>

class PackStealLB;

struct MapNode {
    int _index;
    double _data;
    double _timestamp;
};

class ProcMap {
 public:
    int insert_update(const MapNode&); // returns 1 if node was updated, 0 otherwise
    int size();
    std::pair<int, double> first() const;
    std::pair<int, double> last() const;
    void vectorize_data(int*,double*,double*);

 private:
    const MapNode& most_recent(const MapNode& a, const MapNode& b);
    std::vector< MapNode > map; // Heapfied
};

#endif // UPDATABLE_PE_MAP_H
