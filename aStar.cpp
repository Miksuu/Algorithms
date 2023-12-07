#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <vector>
#include <random>
#include <list>

struct Node {
    bool isObstacle = false;
    bool isVisited = false;
    bool isPath = false;
    float globalGoal;
    float localGoal;
    int x;
    int y;
    std::vector<Node*> neighbours;
    Node* parent;
};

float heuristic(Node* a, Node* b) {
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    return std::sqrt(dx * dx + dy * dy);
}

float distance(Node* a, Node* b) {
    int dx = a->x - b->x;
    int dy = a->y - b->y;
    return std::sqrt(dx * dx + dy * dy);
}

void initializeGrid(std::vector<std::vector<Node>>& _grid) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    for(int x = 0; x < 20; ++x) {
        for(int y = 0; y < 20; ++y) {
            _grid[x][y].x = x;
            _grid[x][y].y = y;
            _grid[x][y].globalGoal = std::numeric_limits<float>::infinity();
            if(dis(gen) <= 10) { // 10% chance
                _grid[x][y].isObstacle = true;
            }
        }
    }
}

void setNeighbours(std::vector<std::vector<Node>>& _grid) {
    for(int x = 0; x < 20; ++x) {
        for(int y = 0; y < 20; ++y) {
            if(y>0)
                _grid[x][y].neighbours.push_back(&_grid[x][y - 1]);
            if(y<19)
                _grid[x][y].neighbours.push_back(&_grid[x][y + 1]);
            if(x>0)
                _grid[x][y].neighbours.push_back(&_grid[x - 1][y]);
            if(x<19)
                _grid[x][y].neighbours.push_back(&_grid[x + 1][y]);
        }
    }
}

void aStarAlgorithm(Node* _startNode, Node* _endNode, std::list<Node*>& _notTestedNodes) {
    Node* currentNode = nullptr;
    while (!_notTestedNodes.empty()) {
        _notTestedNodes.sort([](const Node* lhs, const Node* rhs) { return lhs->globalGoal < rhs->globalGoal; });

        while (!_notTestedNodes.empty() && _notTestedNodes.front()->isVisited)
            _notTestedNodes.pop_front();

        if (_notTestedNodes.empty())
            break;

        currentNode = _notTestedNodes.front();
        currentNode->isVisited = true;

        for (auto neighbour : currentNode->neighbours) {
            if (!neighbour->isVisited && !neighbour->isObstacle)
                _notTestedNodes.push_back(neighbour);

            float possiblyLowerGoal = currentNode->globalGoal + distance(currentNode, neighbour);

            if (possiblyLowerGoal < neighbour->globalGoal) {
                neighbour->parent = currentNode;
                neighbour->globalGoal = possiblyLowerGoal;
                neighbour->localGoal = neighbour->globalGoal + heuristic(neighbour, _endNode);
            }
        }

        if (currentNode == _endNode)
            break;
    }
}

void printPath(Node* _startNode, Node* _endNode) {
    std::cout << "Start Node: (" << _startNode->x << ", " << _startNode->y << ")" << std::endl;
    std::cout << "End Node: (" << _endNode->x << ", " << _endNode->y << ")" << std::endl;
    std::cout << "Path: ";
    Node* currentNode = _endNode;
    while (currentNode != nullptr) {
        std::cout << "(" << currentNode->x << ", " << currentNode->y << ") ";
        currentNode->isPath = true;
        currentNode = currentNode->parent;
    }
    std::cout << std::endl;
}

void printGrid(const std::vector<std::vector<Node>>& _grid, Node* _startNode, Node* _endNode) {
    for (const auto& row : _grid) {
        for (const auto& node : row) {
            if (&node == _startNode)
                std::cout << "S ";
            else if (&node == _endNode)
                std::cout << "E ";
            else if (node.isObstacle)
                std::cout << "O ";
            else if (node.isPath)
                std::cout << "P ";
            else if (node.isVisited)
                std::cout << "* ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

void aStarMain() {
    std::cout << "A* Algorithm" << std::endl;
    std::vector<std::vector<Node>> grid(20, std::vector<Node>(20));
    initializeGrid(grid);
    setNeighbours(grid);

    Node* startNode = &grid[0][0];
    Node* endNode = &grid[19][19];
    startNode->localGoal = 0.0f;
    startNode->globalGoal = heuristic(startNode, endNode);

    std::list<Node*> notTestedNodes;
    notTestedNodes.push_back(startNode);

    aStarAlgorithm(startNode, endNode, notTestedNodes);
    printPath(startNode, endNode);
    printGrid(grid, startNode, endNode);
}

int main() {
    aStarMain();
}