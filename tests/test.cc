#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../raytra.h"
#include "../triangle.h"
#include "../BVHTree.h"

using namespace Raytra;

TEST_CASE ("detect blank strings correctly") {
    REQUIRE(!is_blank("asdad"));
    REQUIRE(is_blank("\n"));
    REQUIRE(is_blank("\t"));
    REQUIRE(is_blank("  "));
}

TEST_CASE("vector operations work correctly") {
    vec a = {.x = 3, .y = 1, .z = 2};
    vec b = {.x = 2, .y = 6, .z = 4};
    REQUIRE(dot(a, b) == 20);

    vec c = {.x = 0.8017, .y = 0.267, .z = .534};
    REQUIRE(norm(a).x == Approx(c.x).epsilon(0.01));
    REQUIRE(norm(a).y == Approx(c.y).epsilon(0.01));
    REQUIRE(norm(a).z == Approx(c.z).epsilon(0.01));

    vec d = a + b;
    REQUIRE(d.x == 5); REQUIRE(d.y == 7); REQUIRE(d.z == 6);

    vec e = 10 * a;
    REQUIRE(e.x == 30); REQUIRE(e.y == 10); REQUIRE(e.z == 20);
}

TEST_CASE("operations on points should give vectors") {
    point a = {.x = 1, .y = 2, .z = 3};
    point b = {.x = 9, .y = 4, .z = 2};
    vec c = a + b;
    REQUIRE(c.x == 10);
    REQUIRE(c.y == 6);
    REQUIRE(c.z == 5);
}

TEST_CASE("distance between two points is computed correctly") {
    point p = {.x = 1, .y = 0, .z = 0};
    point q = {.x = 0, .y = 0, .z = 0};
    point z = {.x = 1, .y = 1, .z = 1};

    REQUIRE(dist2(p, q) == 1);
    REQUIRE(dist2(p, z) == 2);
}

TEST_CASE("cross product between vectors is computed correctly") {
    vec a = {.x = 1, .y = 2, .z = 3};
    vec b = {.x = 4, .y = 1, .z = 62};
    vec c = cross(a, b);

    REQUIRE(c.x == 121);
    REQUIRE(c.y == -50);
    REQUIRE(c.z == -7);
}

TEST_CASE("triangles have correct normals") {
    const Triangle t(1, 0, 0, 0, 1, 0, 0, 0, 1);
    point p = {.x = 1, .y = 1, .z = 1};
    vec n = t.get_normal(p);

    REQUIRE(n.x == 1/sqrtf(3));
    REQUIRE(n.y == 1/sqrtf(3));
    REQUIRE(n.z == 1/sqrtf(3));
}

TEST_CASE("Sort Directions cycle correctly") {
    REQUIRE(next_axis(Axis::X) == Axis::Y);
    REQUIRE(next_axis(Axis::Y) == Axis::Z);
    REQUIRE(next_axis(Axis::Z) == Axis::X);
}

TEST_CASE("Bounding Boxes can be compared on axis correctly") {

    BoundingBox box1(1, 2, 13, 14, 5, 6);
    BoundingBox box2(10, 12, 3, 4, 50, 60);

    REQUIRE(!BoundingBox::compare_along_axis(
            &box1, &box2, Axis::X
    ));

    REQUIRE(BoundingBox::compare_along_axis(
            &box1, &box2, Axis::Y
    ));

    REQUIRE(!BoundingBox::compare_along_axis(
            &box1, &box2, Axis::Z
    ));
}

TEST_CASE("Bounding boxes correctly intersect with rays") {
    BoundingBox box1(0, 10, 0, 10, 0, 10);
    BoundingBox box2(-20, 20, -20, 20, -20, 20);
    Ray ray({-10, -10, -10}, {1, 0, 0});

    REQUIRE(box1.get_intersection_point(ray) < 0);
    REQUIRE(box2.get_intersection_point(ray) >= 0);
}

TEST_CASE("Bounding boxes have finite thickness") {
    BoundingBox box1{0, 0, 0, 0, 0, 0};
    Ray ray({-1, 0, 0}, {1, 0, 0});

    REQUIRE(box1.get_intersection_point(ray) >= 0);
}

TEST_CASE("BVH Trees are built correctly") {
    // two boxes lying on the x axis
    BoundingBox box1{-3, -1, 0, 2, 0, 2};
    BoundingBox box2{1, 3, 0, 2, 0, 2};

    std::vector<BoundingBox*> bboxes;
    bboxes.push_back(&box1);
    bboxes.push_back(&box2);

    BVHTree *tree = BVHTree::make_bvhtree (
            bboxes.begin(), bboxes.end(), Axis::X
    );

    REQUIRE(tree->get_depth() == 2);
}
