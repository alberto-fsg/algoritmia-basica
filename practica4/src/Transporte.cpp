#include "Transporte.hpp"

#include <algorithm>
#include <limits>

// Comparator for sorting by density (descending) which can be passed to std::sort
static bool densityGreaterThan(const Request &a, const Request &b) {
  return a.density > b.density;
}

Node::Node(unsigned int segments) : depth(0), cost_so_far(0), accepted_passangers(segments, 0) {}

Transporte::Transporte(unsigned int capacity, unsigned int segments, std::vector<Request> &reqs)
    : capacity(capacity), segments(segments), requests(reqs) {
  best_cost = std::numeric_limits<double>::infinity();

  for (auto &r : requests) {
    r.benefit = r.passengers * (r.arrival_station_index - r.departure_station_index);
    r.density = r.benefit / ((r.arrival_station_index - r.departure_station_index) * r.passengers);
  }

  // Sort by density to improve pruning probabilities (search the most promising requests first)
  std::sort(requests.begin(), requests.end(), densityGreaterThan);
}

// Estimated cost function ĉ(x)
double Transporte::estimateCost(const Node &node) {
  std::vector<unsigned int> rem(segments, capacity);
  for (unsigned int s = 0; s < segments; ++s)
    rem[s] -= node.accepted_passangers[s];

  // 'bound_benefit' is the maximum possible profit
  double bound_benefit = -node.cost_so_far;
  for (unsigned int k = node.depth; k < requests.size(); ++k) {
    const auto &r = requests[k];

    // Search tightest capacity of a station in the request's stations
    // (we can take fractions of the request, but the passangers
    unsigned int capacity = *std::min_element(rem.begin() + r.departure_station_index,
                                              rem.begin() + r.arrival_station_index);
    if (capacity <= 0)
      continue;

    // Calculate the benefit adquired by accepting this passangers
    unsigned int use = std::min(capacity, r.passengers);
    bound_benefit += use * (r.arrival_station_index - r.departure_station_index);

    // Mark the used capacity by this passangers
    for (unsigned int s = r.departure_station_index; s < r.arrival_station_index; ++s)
      rem[s] -= use;
  }
  return node.cost_so_far - bound_benefit;
}

// Pruning function U(x)
bool Transporte::shouldPrune(const Node &node) {
  return estimateCost(node) >= best_cost;
}

void Transporte::search(Node &node) {
  if (shouldPrune(node))
    return;

  // Leaf case
  if (node.depth == requests.size()) {
    best_cost = std::min(best_cost, node.cost_so_far);
    return;
  }

  // Explore the tree which generates as a result of declining this
  Node left = node;
  left.depth++;
  search(left);

  // ¿Can we accept this request? If not, we are done
  const auto &r = requests[node.depth];
  for (unsigned int s = r.departure_station_index; s < r.arrival_station_index; ++s) {
    if (node.accepted_passangers[s] + r.passengers > capacity) {
      return;
    }
  }

  // Explore the tree which generates as a result of accepting this
  Node right = node;
  right.depth++;
  right.cost_so_far -= r.benefit;
  for (unsigned int s = r.departure_station_index; s < r.arrival_station_index; ++s)
    right.accepted_passangers[s] += r.passengers;
  search(right);
}

// Entry point
double Transporte::solve() {
  Node root(segments);
  search(root);
  return -best_cost;
}