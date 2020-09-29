#include "octree.h"

Octree::Octree(const Coordinate &farBottomLeft, const Coordinate &nearTopRight)
:
    farBottomLeft {farBottomLeft},
    nearTopRight {nearTopRight},
    center {middleCoord(farBottomLeft, nearTopRight)},
    centerOfMass {center},
    totalMass {0.0}
{}

void Octree::insert(const Star &star)
{
    if (stars.empty() && isLeaf())
    {
        stars.emplace_back(std::move(star));
        return;
    }

    const bool left = star.getCoord().x < center.x;
    const bool down = star.getCoord().y < center.y;
    const bool far = star.getCoord().z < center.z;

    auto &child = children[4 * left + 2 * down + far];

    if (!child)
    {
        Coordinate fbl = farBottomLeft; // calculate FBL and NTR for subtree
        Coordinate ntr = nearTopRight;
        (left ? ntr : fbl).x = center.x;
        (down ? ntr : fbl).y = center.y;
        (far ? ntr : fbl).z = center.z;
        child = std::make_unique<Octree>(fbl, ntr); // create subtree
        auto toMove = std::move(stars);
        stars.clear();
        for (auto &star : toMove)
            insert(std::move(star));
    }

    updateCenterOfMass(star);
    totalMass += star.getMass();
    child->insert(std::move(star));
}

Coordinate gravitationalForce(const Star& s1, const Star& s2)
{
    const Coordinate c1 = s1.getCoord();
    const Coordinate c2 = s2.getCoord();
    double m1 = s1.getMass();
    double m2 = s2.getMass();

    Coordinate dc = c2 - c1;
    double dist = distance(c1, c2);
    if (dist < STARS_MIN_DIST)
    {   
        dc = {copysign(1.0, dc.x), copysign(1.0, dc.y), copysign(1.0, dc.z)};
//        dc = 1;
        dist = STARS_MIN_DIST;
    }

    double force = G * m1 * m2 * SIM_ACC / pow(dist, 3);
    Coordinate forces = {dc * force};

    return forces;
}

Coordinate gravitationalForce(const Star& s1, const Octree& node)
{
    const Coordinate c1 = s1.getCoord();
    const Coordinate c2 = node.getCenterOfMass();
    double m1 = s1.getMass();
    double m2 = node.getTotalMass();

    Coordinate dc = c2 - c1;
    double dist = distance(c1, c2);
    if (dist < STARS_MIN_DIST)
    {   
        dc = {copysign(1.0, dc.x), copysign(1.0, dc.y), copysign(1.0, dc.z)};
//        dc = 1;
        dist = STARS_MIN_DIST;
    }

    double force = G * m1 * m2 * SIM_ACC / pow(dist, 3);
    Coordinate forces {dc * force};

    return forces;
}

Coordinate Octree::calculateForce(const Star& star)
{
    if (isLeaf())
    {
        if (stars.front().getId() == star.getId())
            return Coordinate(); // return 0, star doesn't exert force on itself
        return gravitationalForce(star, stars.front());
    }

    double s = nearTopRight.x - farBottomLeft.x;
    double d = distance(star.getCoord(), centerOfMass);

    if (s / d < THETA) // Far enough away to consider node a star
        return gravitationalForce(star, *this);

    // node is too close, recurse
    Coordinate force = Coordinate();
    for (auto& child : children)
        if (child)
            force += child->calculateForce(star);

    return force;
}

// check if all children are null
bool Octree::isLeaf() const
{
    for (auto& x : children)
        if (x) return 0;
    return 1;
}

void Octree::updateCenterOfMass(const Star &star)
{
    double m = totalMass + star.getMass();
    Coordinate starCoord = star.getCoord();
    double starMass = star.getMass();

    double newX = (centerOfMass.x * totalMass + starCoord.x * starMass) / m;
    double newY = (centerOfMass.y * totalMass + starCoord.y * starMass) / m;
    double newZ = (centerOfMass.z * totalMass + starCoord.z * starMass) / m;

    centerOfMass = Coordinate { newX, newY, newZ };
}

std::ostream& operator<<(std::ostream& os, const Coordinate pos)
{
    return os << '(' << pos.x
              << ',' << pos.y
              << ',' << pos.z
              << ')';
}

std::ostream& operator<<(std::ostream& os, const Star& star)
{
    return os << star.getCoord();
}

std::ostream& Octree::print(std::ostream& os, const std::string& indentStep, const std::string& currentIndent) const
{
    os << currentIndent
       << "Octree " << farBottomLeft
       << " to " << nearTopRight << " MASS: " << totalMass << '\n';
    os << currentIndent << "Center of mass: " << centerOfMass << '\n';
    if (!os) { return os; }
    for (auto const& star : stars) {
        os << currentIndent << "- " << star << " MASS: " << star.getMass() << '\n';
    }
    if (!os) { return os; }
    for (auto i = 0u; i < std::size(children); ++i) {
        if (children[i]) {
            os << currentIndent
               << (i & 1 ? "far" : "near") << ' '
               << (i & 2 ? "bottom" : "top") << ' '
               << (i & 4 ? "left" : "right") << ": \n";
            children[i]->print(os, indentStep, currentIndent+indentStep);
            if (!os) { return os; }
        }
    }
    return os;
}

void Octree::showTree(std::string indentation)
{
    print(std::cout, indentation, "");
}

void Octree::showTree()
{
    showTree("  ");
}