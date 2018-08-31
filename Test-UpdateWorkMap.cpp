#include <gtest/gtest.h>

#include <numeric>
#include <string>
#include <cstdlib>
#include "UpdateWorkMap.h"

class TestWorkMap : public ::testing::Test {
 public:
    WorkMap* wm;
    int n_objs = 16;
    int objs[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    double loads[16];
    double total_load;

    void init_loads(int n, double* loads) {
        std::srand(3);
        for (int i = 0; i < n; i++) {
            loads[i] = (rand()%100/5.0)/((float)(rand()%100/5.0));
        }
    }

    void SetUp() {
        init_loads(n_objs, loads);
        wm = new WorkMap(n_objs, objs, loads);
    }

    void TearDown() {
    }
};

TEST_F(TestWorkMap, Initialization) {
    for (int i = 0; i < 16; i++) {
        ASSERT_TRUE(wm->exists(i));
    }
}

TEST_F(TestWorkMap, InitializationInexists) {
    for (int i = 16; i < 32; i++) {
        ASSERT_FALSE(wm->exists(i));
    }
    // Check again for possible creation on verification
    for (int i = 16; i < 32; i++) {
        ASSERT_FALSE(wm->exists(i));
    }
}

TEST_F(TestWorkMap, VerifyObjId) {
    for (int i = 0; i < 16; i++) {
        auto obj = wm->find(i);
        ASSERT_EQ(i, obj.sys_index);
    }
}

TEST_F(TestWorkMap, VerifyObjLoadNumElements) {
    total_load = 0.0;
    for (int i = 0; i < 16; i++) {
        total_load += loads[i];
    }
    ASSERT_EQ(total_load, wm->calculate_total_load());
}

TEST_F(TestWorkMap, RemoveSomeObjs) {
    total_load = 0.0;
    for (int i = 0; i < 16; i++) {
        total_load += loads[i];
    }
    ASSERT_TRUE(total_load > 0.0);
    double some_load = total_load/10;
    double tmp = some_load;
    auto load_vec = wm->remove_batch_of_load(some_load);
    double load_after_remove = wm->calculate_total_load();
    EXPECT_TRUE(total_load > some_load);
    EXPECT_TRUE(total_load > load_after_remove);
    EXPECT_DOUBLE_EQ(total_load, some_load + load_after_remove);
    EXPECT_NE(some_load, tmp);
    EXPECT_DOUBLE_EQ(some_load, std::accumulate(load_vec.begin(), load_vec.end(), 0.0));
    EXPECT_TRUE(load_vec.size() > 0);
    EXPECT_TRUE(load_vec.size() < 17);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
