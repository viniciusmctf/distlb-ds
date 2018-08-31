#ifndef COMM_AWARE_WORK_MAP
#define COMM_AWARE_WORK_MAP

#include "UpdateWorkMap.h"

struct CommWorkObj : public WorkObj {
    CommWorkObj(int id, int from, int to, double load) : id(id), from(from),
            to(to), load(load) {}
    CommWorkObj(int id, double load) : id(id),  from(-1), to(-1), load(load) {}

    int id, from, to;
    double load;
};

class CommWorkGroup : public WorkGroup {

};

class CommAwareWorkMap : public WorkMap {
 public:
    CommAwareWorkMap(int n_objs, int id_list[], int from_list[],
        int to_list[], double load_list[]);

    void emplace(int id, int from, int to, double load);
    void insert(CommWorkObj);
    std::vector<WorkObj> remove_batch_of_load_to_proc(double&, int dest);

 protected:
    void create_comm_aware_map(int n_objs, int id_list[], int from_list[],
        int to_list[], double load_list[]);

};


#endif //COMM_AWARE_WORK_MAP
