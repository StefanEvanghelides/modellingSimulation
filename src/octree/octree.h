#ifndef OCTREE_H
#define OCTREE_H

#include "../models/star.h"
#include "../utils/coordinate.h"
#include <memory>
#include <vector>

class Octree
{
    const Coordinate farBottomLeft;
    const Coordinate nearTopRight;
    const Coordinate center;

    Coordinate centerOfMass;

    std::unique_ptr<Octree> children[8] = {}; // subtrees
    std::vector<Star> stars = {}; // elements; empty unless we are at a leaf node


public:
    explicit Octree(const Coordinate &farBottomLeft, const Coordinate &nearTopRight);

	// Indexing operators
    // Star operator() (size_t x, size_t y, size_t z);
    // const Star operator() (size_t x, size_t y, size_t z) const;

    void insert(const Star &star);
    std::ostream& print(std::ostream& os, const std::string& indent) const;
    friend std::ostream& operator<<(std::ostream& out, const Octree& o) {
        return o.print(out, {});
    }

private:
    bool isLeaf() const;
};

#endif