#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

enum class Direction {NORTH, SOUTH, WEST, EAST};
enum class Turn {LEFT = -2, RIGHT = -1};

// https://leetcode-cn.com/problems/walking-robot-simulation/
int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
    Direction cur = Direction::NORTH;
    int x = 0;
    int y = 0;
    int distance = 0;
    set<pair<int, int>> unreach;
    for (auto& obstacle : obstacles) {
        unreach.insert({obstacle[0], obstacle[1]});
    }

    for (auto& cmd : commands) {
        if (cmd == static_cast<int>(Turn::LEFT)) {
            if (cur == Direction::NORTH) {
                cur = Direction::WEST;
            } else if (cur == Direction::SOUTH) {
                cur = Direction::EAST;
            } else if (cur == Direction::WEST) {
                cur = Direction::SOUTH;
            } else if (cur == Direction::EAST) {
                cur = Direction::NORTH;
            }
        } else if (cmd == static_cast<int>(Turn::RIGHT)) {
            if (cur == Direction::NORTH) {
                cur = Direction::EAST;
            } else if (cur == Direction::SOUTH) {
                cur = Direction::WEST;
            } else if (cur == Direction::WEST) {
                cur = Direction::NORTH;
            } else if (cur == Direction::EAST) {
                cur = Direction::SOUTH;
            }
        } else {
            int nextX = x;
            int nextY = y;

            for (int i = 0; i < cmd; i++) {
                if (cur == Direction::NORTH) {
                    ++nextY;
                } else if (cur == Direction::SOUTH) {
                    --nextY;
                } else if (cur == Direction::WEST) {
                    --nextX;
                } else if (cur == Direction::EAST) {
                    ++nextX;
                }

                if (unreach.find({nextX, nextY}) != unreach.end()) break;
                x = nextX;
                y = nextY;
                distance = max(distance, x * x + y * y);
            }

        }
    }

    return distance;
}

int main(int argc, char* argv[]) {
    vector<int> command;
    vector<vector<int>> obstacles;

    command = {4, -1, 3};
    obstacles = {};
    assert(25 == robotSim(command, obstacles));

    command = {4, -1, 4, -2, 4};
    obstacles = {{2, 4}};
    assert(65 == robotSim(command, obstacles));

    return 0;
}