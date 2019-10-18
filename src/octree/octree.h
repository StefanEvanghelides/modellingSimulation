#ifndef OCTREE_H
#define OCTREE_H

#include "../models/star.h"
#include "../utils/coordinate.h"
#include "../utils/constants.h"
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

    double getTotalMass() const {return totalMass;}
    Coordinate getCenterOfMass() const {return centerOfMass;}
    Coordinate calculateForce(const Star& star);

private:
    bool isLeaf() const;
    void updateCenterOfMass(const Star &star);

private:
    const Coordinate farBottomLeft;
    const Coordinate nearTopRight;
    const Coordinate center;

    Coordinate centerOfMass;
    double totalMass;

    std::unique_ptr<Octree> children[8] = {}; // subtrees
    std::vector<Star> stars = {}; // elements; empty unless we are at a leaf node
};

#endif