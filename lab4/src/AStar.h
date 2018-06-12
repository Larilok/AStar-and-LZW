//
// Created by Mikhail on 6/9/2018.
//

#ifndef LAB4_ASTAR_H
#define LAB4_ASTAR_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <ctime>
#include <set>


namespace AStar {

    struct Point {
        Point() {
            this->x = 0;
            this->y = 0;
        }

        Point(int x, int y) {
            this->x = x;
            this->y = y;
        }

        bool operator==(const Point &coordinates_) const;

        Point operator+(const AStar::Point &add_) const;

        int x, y;
    };

    //some shortcuts

    using uint = unsigned int;

    using HeuristicFunction = std::function<uint(Point, Point)>;

    using CoordinateList = std::vector<Point>;


    struct Node {
        uint G, H;   // our g(n) and h(n) that makes f(n)
        Point coordinates;  //Point on canvas
        Node *parent;       //prevElement

        explicit Node(Point coord_, Node *parent_ = nullptr);

        uint getScore();

    };

    //another shortcut
    using NodeSet = std::set<Node *>;

    class Generator {

        Node *findNodeOnList(NodeSet &nodes_, Point coordinates_);

        void releaseNodes(NodeSet &nodes_);

    public:

        void generateRandomWalls(int WORLD_X, int WORLD_Y, AStar::Generator &generator);

        bool detectCollision(Point coordinates_);

        Generator();

        void setWorldSize(Point worldSize_);

        void setDiagonalMovement(bool enable_);

        void setHeuristic(HeuristicFunction heuristic_);

        CoordinateList findPath(Point source_, Point target_);

        void addCollision(Point coordinates_);

        void removeCollision(Point coordinates_);

        void clearCollisions();


    private:

        HeuristicFunction heuristic;

        CoordinateList direction, walls;

        Point worldSize;

        uint directions;

    };


    class Heuristic {

        static Point getDelta(Point source_, Point target_);


    public:

        static uint manhattan(Point source_, Point target_);

        static uint euclidean(Point source_, Point target_);

    };

}

#endif //LAB4_ASTAR_H
