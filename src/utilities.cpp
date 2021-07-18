#include "utilities.h"


// Helper Function to compare RouteModel class nodes 'a' and 'b' by their 'f_values'
bool Compare(const RouteModel::Node* node_a, RouteModel::Node* node_b) {
    float f_node_a = node_a->g_value + node_a->h_value; // fa = ga + ha
    float f_node_b = node_b->g_value + node_b->h_value; // fb = gb + hb
    return f_node_a > f_node_b; 
}

