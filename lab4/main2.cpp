#include <iostream>
#include <iomanip>
#include "src/AStar.h"

#define WORLD_X 30
#define WORLD_Y 30
#define POINT_Y 20
#define POINT_X 15

void printMap(std::vector<AStar::Point> & path, AStar::Generator &generator){
    int counter = WORLD_Y;

    std::cout << std::setw(4) << ' ';
    for (int l = 0; l < WORLD_X; ++l) {
        std::cout << std::setw(3) << l;
    }
    std::cout << '\n';

    char flag = 1;
    for (int y = WORLD_Y - 1; y >= 0; --y) {
        std::cout << std::setw(3) << y << ':';
        for (int x = 0; x < WORLD_X; ++x) {
            if (std::find(path.begin(), path.end(),AStar::Point{x,y}) != path.end()) {
                if(flag && path[0].x == x && path[0].y == y){
                    flag=0;
                    std::cout << std::setw(3) << "end";
                }
                else
                    std::cout << std::setw(3) << '1';
            }
            else if (generator.detectCollision({x, y})) {
                std::cout << std::setw(3) << '#';
//                std::cout << char(0xdb);
            }
            else std::cout << std::setw(3) << ' ';
        }
        std::cout << '\n';
    }
}

int main() {

    AStar::Generator generator;

    generator.setWorldSize({WORLD_X, WORLD_Y});

    generator.setHeuristic(AStar::Heuristic::manhattan);

    generator.setDiagonalMovement(false);

    generator.generateRandomWalls(WORLD_X,WORLD_Y,generator);
    std::cout << "Generate path ... \n";

    auto path = generator.findPath({0, 0}, {POINT_X, POINT_Y});

    printMap(path,generator);


//    for (auto &coordinate : path) {
//
//        printf("(%i,%i) ", coordinate.x,coordinate.y);
//
//    }
}