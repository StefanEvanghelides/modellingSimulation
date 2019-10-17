#ifndef OCTREE_H
#define OCTREE_H

#include "../models/star.h"
#include "../utils/coordinate.h"
#include <memory>
#include <vector>

class Octree
{
public:
    explicit Octree(const Coordinate &farBottomLeft, const Coordinate &nearTopRight);

    void insert(const Star &star);
    std::ostream& print(std::ostream& os, const std::string& indentStep, const std::string& currentIndent) const;
    friend std::ostream& operator<<(std::ostream& out, const Octree& o) {
        return o.print(out, {}, {});
    }
    void showTree(std::string indentation);
    void showTree();

private:
    bool isLeaf() const;

private:
    const Coordinate farBottomLeft;
    const Coordinate nearTopRight;
    const Coordinate center;

    Coordinate centerOfMass;

    std::unique_ptr<Octree> children[8] = {}; // subtrees
    std::vector<Star> stars = {}; // elements; empty unless we are at a leaf node
};

#endif