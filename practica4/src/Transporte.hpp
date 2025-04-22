#pragma once

#include <vector>

struct Request {
  unsigned int departure_station_index;
  unsigned int arrival_station_index;
  unsigned int passengers;
  double benefit; // Passengers * (arrival_station_index - departure_station_index)
  double density; // Benefit / ((arrival_station_index - departure_station_index) * passengers)
};

struct Node {
  unsigned int depth; // How many requests have been decided (current decision = depth)
  double cost_so_far;
  std::vector<unsigned int> accepted_passangers; // Representation of the current accepted passangers for each segment

  Node(unsigned int segments); // To initialize 'accepted_passangers' with 'segments' number of 0s
};

/**
 * Implements Branch and Bound algorithm to solve Práctica 4: Ramificación y poda, programación lineal,
 * an assignment of Algoritmia Básica, Universidad de Zaragoza
 */
class Transporte {
public:
  Transporte(unsigned int capacity, unsigned int segments, std::vector<Request> &requests);
  double solve();

private:
  unsigned int capacity, segments;
  std::vector<Request> requests;
  double best_cost; // Solution to the problem

  double estimateCost(const Node &node); // ĉ(x)
  bool shouldPrune(const Node &node);    // U(x)
  void search(Node &node);
};
