#include <gtest/gtest.h>

#include <string>
#include "UpdateProcMap.h"

class TestProcMap : public ::testing::Test {

};

TEST_F(TestProcMap, CheckSize) {
    ProcMap map;
    ASSERT_EQ(0, map.size());
    map.insert_update({0, 1.0, 20.0});
    map.insert_update({1, 1.5, 20.0});
    map.insert_update({2, 2.0, 20.0});
    ASSERT_EQ(3, map.size());
    map.insert_update({3, 2.5, 30.0});
    ASSERT_EQ(4, map.size());
}

TEST_F(TestProcMap, UpdateANodeSize) {
    ProcMap map;
    map.insert_update({0, 1.0, 20.0});
    map.insert_update({1, 1.5, 20.0});
    map.insert_update({2, 2.0, 20.0});
    map.insert_update({3, 2.5, 30.0});
    map.insert_update({1, 1.5, 40.0});
    ASSERT_EQ(4, map.size());

    map.insert_update({4, 1.5, 40.0});
    ASSERT_EQ(5, map.size());
}

TEST_F(TestProcMap, UpdateANodeStatus) {
    ProcMap map;
    map.insert_update({0, 1.0, 20.0});
    map.insert_update({1, 1.5, 20.0});
    map.insert_update({2, 2.0, 20.0});
    map.insert_update({3, 2.5, 30.0});
    map.insert_update({1, 0.8, 40.0});
    auto node = map.last();
    auto other_node = map.first();

    ASSERT_EQ(3, node.first);
    ASSERT_EQ(2.5, node.second);
    ASSERT_EQ(1, other_node.first);
    ASSERT_EQ(0.8, other_node.second);
}

TEST_F(TestProcMap, VectorizeData) {
    ProcMap map;
    map.insert_update({0, 1.0, 20.0});
    map.insert_update({1, 1.5, 20.0});
    map.insert_update({2, 2.0, 20.0});
    map.insert_update({3, 2.5, 30.0});

    int idvec[] = {0,1,2,3};
    double dtvec[] = {1.0,1.5,2.0,2.5};
    double tsvec[] = {20.0, 20.0, 20.0, 30.0};

    int* ids;
    double* loads;
    double* timestamps;
    ids = new int[map.size()];
    loads = new double[map.size()];
    timestamps = new double[map.size()];
    map.vectorize_data(ids, loads, timestamps);

    for (int i = 0; i < map.size(); i++) {
        ASSERT_EQ(idvec[i], ids[i]);
        ASSERT_EQ(dtvec[i], loads[i]);
        ASSERT_EQ(tsvec[i], timestamps[i]);
    }

    delete [] ids;
    delete [] loads;
    delete [] timestamps;
}

TEST_F(TestProcMap, VectorizeDifficultData) {
    ProcMap map;
    int twoA = map.insert_update({0, 5.0, 20.0});
    ASSERT_EQ(2, twoA);
    int twoB = map.insert_update({1, 1.5, 20.0});
    ASSERT_EQ(2, twoB);
    int twoC = map.insert_update({2, 2.0, 20.0});
    ASSERT_EQ(2, twoC);
    int twoD = map.insert_update({3, 3.5, 30.0});
    ASSERT_EQ(2, twoD);
    int twoE = map.insert_update({4, 6.0, 20.0});
    ASSERT_EQ(2, twoE);
    int twoF = map.insert_update({5, 2.5, 30.0});
    ASSERT_EQ(2, twoF);

    int idvec[] = {1, 2, 5, 3, 0, 4};
    double dtvec[] = {1.5, 2.0 , 2.5, 3.5, 5.0, 6.0};
    double tsvec[] = {20.0, 20.0, 30.0, 30.0, 20.0, 20.0};

    int* ids;
    double* loads;
    double* timestamps;
    ids = new int[map.size()];
    loads = new double[map.size()];
    timestamps = new double[map.size()];
    map.vectorize_data(ids, loads, timestamps);

    for (int i = 0; i < map.size(); i++) {
        EXPECT_EQ(idvec[i], ids[i]);
        EXPECT_EQ(dtvec[i], loads[i]);
        ASSERT_EQ(tsvec[i], timestamps[i]);
    }

    delete [] ids;
    delete [] loads;
    delete [] timestamps;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
