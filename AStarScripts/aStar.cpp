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

float heuristic(Node* _a, Node* _b) {
    int dx = _a->x - _b->x;
    int dy = _a->y - _b->y;
    return std::sqrt(dx * dx + dy * dy);
}

float distance(Node* _a, Node* _b) {
    int dx = _a->x - _b->x;
    int dy = _a->y - _b->y;
    return std::sqrt(dx * dx + dy * dy);
}

void initializeGrid(std::vector<std::vector<Node>>& _grid, int _gridWidth, int _gridHeight, int _obstaclePercentantage) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    for(int x = 0; x < _gridWidth; ++x) {
        for(int y = 0; y < _gridHeight; ++y) {
            _grid[y][x].x = x;
            _grid[y][x].y = y;
            _grid[y][x].globalGoal = std::numeric_limits<float>::infinity();
            if(dis(gen) <= _obstaclePercentantage) {
                _grid[y][x].isObstacle = true;
            }
        }
    }
}

void setNeighbours(std::vector<std::vector<Node>>& _grid, int _gridWidth, int _gridHeight) {
    for(int x = 0; x < _gridWidth; ++x) {
        for(int y = 0; y < _gridHeight; ++y) {
            if(y>0)
                _grid[y][x].neighbours.push_back(&_grid[y - 1][x]);
            if(y<_gridHeight-1)
                _grid[y][x].neighbours.push_back(&_grid[y + 1][x]);
            if(x>0)
                _grid[y][x].neighbours.push_back(&_grid[y][x - 1]);
            if(x<_gridWidth-1)
                _grid[y][x].neighbours.push_back(&_grid[y][x + 1]);
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

class AStar {
public:
    int gridWidth;
    int gridHeight;
    int obstaclePercentantage;
    std::vector<std::vector<Node>> grid;
    Node* startNode;
    Node* endNode;
    std::list<Node*> notTestedNodes;

    AStar(int width, int height, int obstaclePercent) : gridWidth(width), gridHeight(height), obstaclePercentantage(obstaclePercent) {
        grid.resize(gridHeight, std::vector<Node>(gridWidth));
        initializeGrid(grid, gridWidth, gridHeight, obstaclePercentantage);
        setNeighbours(grid, gridWidth, gridHeight);

        startNode = &grid[0][0];
        endNode = &grid[gridHeight-1][gridWidth-1];
        startNode->localGoal = 0.0f;
        startNode->globalGoal = heuristic(startNode, endNode);

        notTestedNodes.push_back(startNode);
    }

    void run() {
        aStarAlgorithm(startNode, endNode, notTestedNodes);
        printPath(startNode, endNode);
        printGrid(grid, startNode, endNode);
    }
};

class GameWorld {
public:
    static int gridWidth;
    static int gridHeight;
    static int obstaclePercentantage;

    static void initialize(int _width, int _height, int _obstaclePercent) {
        gridWidth = _width;
        gridHeight = _height;
        obstaclePercentantage = _obstaclePercent;
    }
};

int GameWorld::gridWidth;
int GameWorld::gridHeight;
int GameWorld::obstaclePercentantage;

int main() {
    std::cout << "A* Algorithm" << std::endl;
    int gridWidth = 50;
    int gridHeight = 20;
    int obstaclePercentantage = 5;

    GameWorld::initialize(gridWidth, gridHeight, obstaclePercentantage);
    AStar aStar(GameWorld::gridWidth, GameWorld::gridHeight, GameWorld::obstaclePercentantage);
    aStar.run();

    return 0;
}
