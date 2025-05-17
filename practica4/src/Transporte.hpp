#pragma once

#include <vector>

struct Request {
  unsigned int departure_station_index;
  unsigned int arrival_station_index;
  unsigned int passengers;
  double benefit; // Passengers * (arrival_station_index - departure_station_index)
  //double density; // Benefit / ((arrival_station_index - departure_station_index) * passengers)
};

struct Node {
  unsigned int depth; // How many requests have been decided (current decision = depth)
  double benefit_so_far;
  std::vector<unsigned int> accepted_passangers; // Representation of the current accepted passengers for each segment

  Node(unsigned int segments); // To initialize 'accepted_passangers' with 'segments' number of 0s
};

/**
 * Implements Branch and Bound algorithm to solve Prctica 4: Ramificacin y poda, programacin lineal,
 * an assignment of Algoritmia Bsica, Universidad de Zaragoza
 */
class Transporte {
public:
  Transporte(unsigned int capacity, unsigned int segments, std::vector<Request> &requests);
  double solve();

private:
  unsigned int capacity, segments;
  std::vector<Request> requests;
  double best_benefit; // Solution to the problem (maximized benefit)

  double estimateBenefit(const Node &node); // (x)
  bool shouldPrune(const Node &node);       // U(x)
  void search(Node &node);
};
