#include "route_planner.h"
#include <algorithm>

using std::sort;


RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    start_node = &m_Model.FindClosestNode(start_x, start_y);
    end_node = &m_Model.FindClosestNode(end_x, end_y);

}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*end_node);
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    // Populate neighbors 
    current_node->FindNeighbors();

    for (RouteModel::Node * neighbor : current_node->neighbors){
        // Set neighbors params
        neighbor->parent = current_node;
        neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
        neighbor->h_value = RoutePlanner::CalculateHValue(neighbor);
        
        // Add to open
        open_list.emplace_back(neighbor);
        neighbor->visited = true;
    }

}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

// Helper Function - Compares nodes a and b f_value
bool Compare(const RouteModel::Node* node_a, RouteModel::Node* node_b) {
    int f_node_a = node_a->g_value + node_a->h_value; // fa = ga + ha
    int f_node_b = node_b->g_value + node_b->h_value; // fb = gb + hb
    return f_node_a > f_node_b; 
}

RouteModel::Node *RoutePlanner::NextNode() {
 
    // Sorting open nodes
    sort(RoutePlanner::open_list.begin(), RoutePlanner::open_list.end(), Compare);
    
    // Removes the lower value node and returns it
    RouteModel::Node* lowest_fval_node = RoutePlanner::open_list.back();
    RoutePlanner::open_list.pop_back();
    return lowest_fval_node;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.
    RouteModel::Node curr_node = *current_node;
    path_found.push_back(curr_node);

    while (curr_node.parent != nullptr){

        // Distance update
        distance += curr_node.parent->distance(curr_node);

        // Move to the next one
        curr_node = *curr_node.parent;
        path_found.push_back(curr_node);
    }

    // Reorder
    std::vector<RouteModel::Node> path_found_correct_order;
    for(int i = path_found.size() - 1; i >= 0; i--){
        path_found_correct_order.push_back(path_found[i]);
    }

    // Correct distance and return path
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found_correct_order;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

}