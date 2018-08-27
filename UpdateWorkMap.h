/***
 *
 * Interface for an updatable Work Information.
 *
 *
 **/


#ifndef UPDATABLE_WORK_MAP_H
#define UPDATABLE_WORK_MAP_H

#include <vector>
#include <unordered_map>
#include <set>
#include <list>
#include <map>

struct WorkObj {
    int sys_index;
    int refereced_at;
    double load;

    bool operator<(const WorkObj& rhs) {
        return load < rhs.load;
    }

    bool operator>(const WorkObj& rhs) {
        return load > rhs.load;
    }

    bool operator==(const WorkObj& rhs) {
        return sys_index == rhs.sys_index;
    }

    double operator+(const WorkObj& rhs) {
        return load + rhs.load;
    }
};

class WorkGroup {
 public:
    double sum_work();
    std::vector<WorkObj&> get_some(double&); // Modify load to actual value

 protected:
    std::list<WorkObj&> my_work; // Use iterators for easy
    double summed_work; // -1 before first call of sum_work. Should be redefined to -1 everytime some load is removed.
};

class WorkMap {
 public:
    WorkMap(int n_objs, int* objs);
    void insert(WorkObj);
    bool exists(int index);
    const WorkObj& find(int index); // Throws exception if not found
    std::vector<WorkObj> remove_batch(std::vector<int> indexes);
    std::vector<WorkObj> remove_batch_of_load(double& expected_load);
    std::vector<WorkObj> remove_batch_of_load_to_proc(double& expected_load, int target_proc);
    double calculate_total_load();

 private:
    std::unordered_map<int, WorkObj> all_objs;
    std::vector<WorkObj&> ordered_objs;
    std::vector<WorkGroup> frontiers;
    std::set<WorkObj> recent;
    double my_total_load; // should be updated on remove

    void sort_objs();
    bool remove(int index); // false if not removed, true otherwise
    void create_obj_naive_map(int n_objs, int* objs);
    void remove_from_all(const WorkObj& obj); // Should be overrided by specialized classes

};

#endif // UPDATABLE_WORK_MAP_H
