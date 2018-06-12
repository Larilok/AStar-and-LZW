//
// Created by Mikhail on 6/9/2018.
//

#include "AStar.h"

using namespace std::placeholders;


bool AStar::Point::operator==(const Point &coordinates_) const {

    return (x == coordinates_.x && y == coordinates_.y);

}


AStar::Point AStar::Point::operator+(const AStar::Point &add_) const {
    AStar::Point newP;
    newP.x = this->x + add_.x;
    newP.y = this->y + add_.y;
    return newP;

}


AStar::Node::Node(Point coordinates_, Node *parent_) {

    parent = parent_;

    coordinates = coordinates_;

    G = H = 0;

}


AStar::uint AStar::Node::getScore() {

    return G + H;

}


AStar::Generator::Generator() {

    setDiagonalMovement(false);

    setHeuristic(&Heuristic::manhattan);

    direction = {

            {0,  1},
            {1,  0},
            {0,  -1},
            {-1, 0},

            {-1, -1},
            {1,  1},
            {-1, 1},
            {1,  -1}

    };

}


void AStar::Generator::setWorldSize(Point worldSize_) {

    worldSize = worldSize_;

}


void AStar::Generator::setDiagonalMovement(bool enable_) {

    directions = (enable_ ? 8 : 4);

}


void AStar::Generator::setHeuristic(HeuristicFunction heuristic_) {
    heuristic = std::bind(heuristic_, _1, _2);
}


void AStar::Generator::addCollision(Point coordinates_) {
    walls.push_back(coordinates_);
}


void AStar::Generator::removeCollision(Point coordinates_) {
    auto it = std::find(walls.begin(), walls.end(), coordinates_);
    if (it != walls.end()) {
        walls.erase(it);
    }
}


void AStar::Generator::clearCollisions() {

    walls.clear();

}


AStar::CoordinateList AStar::Generator::findPath(Point source_, Point target_) {
    if (detectCollision({source_.x, source_.y}) || detectCollision({target_.x, target_.y})) {
        CoordinateList path;
        return path;
    }
    Node *current = nullptr;
    NodeSet openSet, closedSet;
    openSet.insert(new Node(source_));

    while (!openSet.empty()) {
        current = *openSet.begin();

        for (auto node : openSet) {     //search for the cheapest one
            if (node->getScore() <= current->getScore()) {
                current = node;
            }
        }

        if (current->coordinates == target_) {
            break;
        }
        closedSet.insert(current);
        openSet.erase(std::find(openSet.begin(), openSet.end(), current));

        for (uint i = 0; i < directions; ++i) {
            Point newCoordinates(current->coordinates + direction[i]);

            if (detectCollision(newCoordinates) ||
                findNodeOnList(closedSet, newCoordinates)) {
                continue;
            }

            uint totalCost = current->G + ((i < 4) ? 10 : 14);
            Node *successor = findNodeOnList(openSet, newCoordinates);
            if (successor == nullptr) {
                successor = new Node(newCoordinates, current);
                successor->G = totalCost;
                successor->H = heuristic(successor->coordinates, target_);
                openSet.insert(successor);
            } else if (totalCost < successor->G) {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }
    CoordinateList path;
    while (current != nullptr) {
        path.push_back(current->coordinates);
        current = current->parent;
    }
    releaseNodes(openSet);
    releaseNodes(closedSet);
    return path;
}


AStar::Node *AStar::Generator::findNodeOnList(NodeSet &nodes_, Point coordinates_) {
    for (auto node : nodes_) {
        if (node->coordinates == coordinates_) {
            return node;
        }
    }
    return nullptr;
}


void AStar::Generator::releaseNodes(NodeSet &nodes_) {
    for (auto it = nodes_.begin(); it != nodes_.end();) {
        delete *it;
        it = nodes_.erase(it);
    }
}


bool AStar::Generator::detectCollision(Point coordinates_) {
    return coordinates_.x < 0 || coordinates_.x >= worldSize.x ||

           coordinates_.y < 0 || coordinates_.y >= worldSize.y ||

           std::find(walls.begin(), walls.end(), coordinates_) != walls.end();

}

void AStar::Generator::generateRandomWalls(int WORLD_X, int WORLD_Y, AStar::Generator &generator) {
    srand((unsigned int) time(NULL));
    for (int i = WORLD_Y - 1; i >= 0; --i) {
        for (int j = 0; j < WORLD_X; ++j) {
            if (rand() % 100 > 70) {
                generator.addCollision({i, j});
                printf("(%i,%i)", i, j);
            }
        }
    }
}


AStar::Point AStar::Heuristic::getDelta(Point source_, Point target_) {

    return {abs(source_.x - target_.x), abs(source_.y - target_.y)};

}


AStar::uint AStar::Heuristic::manhattan(Point source_, Point target_) {

    auto delta = getDelta(source_, target_);

    return static_cast<uint>(10 * (delta.x + delta.y));

}


AStar::uint AStar::Heuristic::euclidean(Point source_, Point target_) {

    auto delta = getDelta(source_, target_);

    return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));

}



