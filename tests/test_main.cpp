#include <gtest/gtest.h>
#include <geom/point.h> // Replace with your actual header path

// A basic test to ensure GTest is working
TEST(SanityCheck, GTestSetup) {
    EXPECT_EQ(1 + 1, 2);
    ASSERT_TRUE(true);
}

// Example test for a Geometric Point
TEST(PointTest, CoordinateAssignment) {
    // Assuming you have a Point class from your src/ logic
    // which you've mentioned working on in previous iterations
    geom::Point p(10.0, 20.0);

    EXPECT_DOUBLE_EQ(p.x, 10.0);
    EXPECT_DOUBLE_EQ(p.y, 20.0);
}

// Example test for a common geometry operation
TEST(PointTest, DistanceCalculation) {
    geom::Point p1(0.0, 0.0);
    geom::Point p2(3.0, 4.0);

    // Testing a distance function you might have implemented
    // for algorithms like Voronoi or convex hull construction
    double dist = geom::euclidean_dist(p1,p2);
    EXPECT_DOUBLE_EQ(dist, 5.0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}