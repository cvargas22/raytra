#ifndef HW_BVHTREE_H
#define HW_BVHTREE_H

#include <vector>
#include "bounding_box.h"

class BVHTree {
public:
    static BVHTree* make_bvhtree (
        std::vector<BoundingBox*>::iterator begin,
        std::vector<BoundingBox*>::iterator end,
        Axis axis
    );

    int get_depth();
private:
    BoundingBox *bbox = nullptr;
    BVHTree *left = nullptr;
    BVHTree *right = nullptr;
};

#endif //HW_BVHTREE_H