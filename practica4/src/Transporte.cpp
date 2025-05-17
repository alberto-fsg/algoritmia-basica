#include "Transporte.hpp"

#include <algorithm>
#include <limits>

static bool beneficGreaterThan(const Request &a, const Request &b) {
  return a.benefit > b.benefit;
}

// Comparator for sorting by density (descending) which can be passed to std::sort
/*static bool densityGreaterThan(const Request &a, const Request &b) {
  return a.density > b.density;
}*/

Node::Node(unsigned int segments) : depth(0), benefit_so_far(0), accepted_passangers(segments, 0) {}

Transporte::Transporte(unsigned int capacity, unsigned int segments, std::vector<Request> &reqs)
    : capacity(capacity), segments(segments), requests(reqs) {
  best_benefit = -std::numeric_limits<double>::infinity(); // Maximizing benefit

  for (auto &r : requests) {
    r.benefit = r.passengers * (r.arrival_station_index - r.departure_station_index);
    //r.density = r.benefit / ((r.arrival_station_index - r.departure_station_index) * r.passengers);
  }

  // Sort by density to improve pruning probabilities (search the most promising requests first)
  // std::sort(requests.begin(), requests.end(), densityGreaterThan);
  std::sort(requests.begin(), requests.end(), beneficGreaterThan);
}

// Estimated benefit function (x)
double Transporte::estimateBenefit(const Node &node) {
  std::vector<unsigned int> remaining(segments, capacity);
  for (unsigned int s = 0; s < segments; ++s) {
    remaining[s] -= node.accepted_passangers[s];
  }

  // 'bound_benefit' is the maximum possible benefit
  double bound_benefit = node.benefit_so_far;
  for (unsigned int k = node.depth; k < requests.size(); ++k) {
    const auto &r = requests[k];

    // Search tightest capacity of a station in the request's stations
    // (we can take fractions of the request, but the passengers)
    unsigned int capacity = *std::min_element(remaining.begin() + r.departure_station_index,
                                              remaining.begin() + r.arrival_station_index);
    if (capacity <= 0) {
      continue;
    }

    // Calculate the benefit acquired by accepting these passengers
    unsigned int use = std::min(capacity, r.passengers);
    bound_benefit += use * (r.arrival_station_index - r.departure_station_index);

    // Mark the used capacity by these passengers
    for (unsigned int s = r.departure_station_index; s < r.arrival_station_index; ++s) {
      remaining[s] -= use;
    }
  }
  return bound_benefit;
}

// Pruning function U(x)
bool Transporte::shouldPrune(const Node &node) {
  return estimateBenefit(node) <= best_benefit; // If the estimated benefit is lower or equal to current best, prune
}

void Transporte::search(Node &node) {
  if (shouldPrune(node))
    return;

  // Leaf case
  if (node.depth == requests.size()) {
    best_benefit = std::max(best_benefit, node.benefit_so_far);
    return;
  }

  // Explore the tree which generates as a result of declining this request
  Node left = node;
  left.depth++;
  search(left);

  // Can we accept this request? If not, we are done
  const auto &r = requests[node.depth];
  for (unsigned int s = r.departure_station_index; s < r.arrival_station_index; ++s) {
    if (node.accepted_passangers[s] + r.passengers > capacity) {
      return;
    }
  }

  // Explore the tree which generates as a result of accepting this request
  Node right = node;
  right.depth++;
  right.benefit_so_far += r.benefit; // Add the benefit of accepting this request
  for (unsigned int s = r.departure_station_index; s < r.arrival_station_index; ++s)
    right.accepted_passangers[s] += r.passengers;
  search(right);
}

// Entry point
double Transporte::solve() {
  Node root(segments);
  search(root);
  return best_benefit; // Return the best benefit found
}
