#include "UpdateWorkMap.h"

double WorkGroup::sum_work() {

  return 0.0;
}

std::vector<WorkObj&> WorkGroup::get_some(double& load) {

  return {};
} // Modify load to actual value

/**
 *
 * End of WorkGroup definitions.
 * Start of WorkMap definitions.
 **/


WorkMap::WorkMap(int n_objs, int* objs) : all_objs({}), frontiers({}),
                                ordered_objs({}), recent({}),
                                my_total_load(0.0) {

  create_obj_naive_map(n_objs, objs);
}

void WorkMap::insert(WorkObj obj) {
  all_objs[obj.sys_index] = std::move(obj);
  ordered_objs.insert(obj);
  my_total_load += obj.load;
  if (neighbor >= 0) {
    // Frontier handling code here.
  }
}

// This should go to recent
void WorkMap::insert_new(WorkObj obj) {
  my_total_load += obj.load;
  recent.insert(std::move(obj));
}

bool WorkMap::exists(int index) {

}

// Throws exception if not found
const WorkObj& WorkMap::find(int index) {

}

std::vector<WorkObj> WorkMap::remove_batch(std::vector<int> indexes) {

}

std::vector<WorkObj> WorkMap::remove_batch_of_load(double& expected_load) {

}

std::vector<WorkObj> WorkMap::remove_batch_of_load_to_proc(double& expected_load, int target_proc) {

}

double WorkMap::calculate_total_load() {
  if (my_total_load < 0.001) {
    double tmp = 0.0;
    if (all_objs.size() > 0) {
      for (auto entry : all_objs) {
        tmp += entry.second.load;
      }
    }
    if (recent.size() > 0) {
      for (auto entry : recent) {
        tmp += entry.load;
      }
    }
    my_total_load = tmp;
  }
  return my_total_load;
}

// Throws exception if obj doesnt exist (from all_objs.at())
WorkObj WorkMap::remove(int index) {
  auto obj = all_objs.at(index);
  ordered_objs.erase(obj);
  all_objs.erase(index);
  return obj;
}

 // false if not removed, true otherwise
void WorkMap::create_obj_naive_map(int n_objs, int* objs, double* loads) {

}

void WorkMap::remove_from_all(const WorkObj& obj) {

}
 // Should be overrided by specialized classes
