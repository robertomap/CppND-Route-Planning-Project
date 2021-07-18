#ifndef UTILITIES_H
#define UTILITIES_H

#include "route_planner.h"

// Helper Function to compare RouteModel class nodes 'a' and 'b' by their 'f_values'
bool Compare(const RouteModel::Node* node_a, RouteModel::Node* node_b);

#endif