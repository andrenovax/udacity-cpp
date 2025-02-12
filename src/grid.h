#ifndef GRID_H
#define GRID_H

#include <ranges>
#include <vector>

#include "SDL.h"

using std::vector;

class Grid {
 public:
  struct Node {
    enum class State { kEmpty, kObstacle, kPath };

    int x, y, g = 0, h = std::numeric_limits<int>::max();

    State state = State::kEmpty;
    Node* parent = nullptr;

    Node() {}
    Node(int x, int y, State state = State::kEmpty)
        : x{x}, y{y}, state{state} {}

    bool operator>(Node const& node) const;
    bool operator<(Node const& node) const;

    bool IsEmpty() const;
    int Distance(Node* node) const;
    int FValue() const;
  };

  Grid(int width, int height);
  Grid(vector<vector<Node>> nodes);

  Grid(const Grid& source);
  Grid& operator=(const Grid& source);

  // Getters
  bool IsEmpty(int x, int y);

  Node* GetNode(int x, int y);
  Node* GetNode(SDL_Point& point);
  Node* GetNeighbourNode(Node& node, int neighbour);
  vector<Grid::Node*> GetNeighbourNodes(Grid::Node& node);

 private:
  vector<vector<Node>> _nodes;

  static constexpr int NODE_NEIGHBOUR_DELTA[4][2]{
      {-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  // Getters
  int Width() const;
  int Height() const;
};

#endif