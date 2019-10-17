#include "octree.h"

Octree::Octree(const Coordinate &farBottomLeft, const Coordinate &nearTopRight)
:
	farBottomLeft {farBottomLeft},
	nearTopRight {nearTopRight},
	center {middleCoord(farBottomLeft, nearTopRight)},
    totalMass {0.0f}
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
        
        child = std::make_unique<Octree>(fbl, ntr);
        auto toMove = std::move(stars);
        stars.clear();
        for (auto &star : toMove)
            insert(std::move(star));
	}

    totalMass += star.getMass();
	child->insert(std::move(star));
}

// check if all children are null
bool Octree::isLeaf() const
{
	for (auto& x : children)
		if (x) return 0;
	return 1;
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
    if (!os) { return os; }
    for (auto const& star : stars) {
        os << currentIndent << "- " << star << '\n';
    }
    if (!os) { return os; }
    for (auto i = 0u;  i < std::size(children);  ++i) {
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