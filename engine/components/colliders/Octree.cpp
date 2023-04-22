#pragma once

#include "Octree.h"

Octree::Octree(const std::vector<glm::vec3>& points, const glm::vec3& min, const glm::vec3& max, int max_depth)
        : depth_(max_depth) {
    // Create root node
    nodes_.resize(1);
    nodes_[0].min = min;
    nodes_[0].max = max;

    // Insert points into the octree
    insert(points, 0, depth_);
}

bool Octree::is_leaf(int node_index) const {
    const Node& node = nodes_[node_index];
    return node.child_node_indices[0] == -1;
}

int Octree::get_child_node_index(int node_index, int child_index) const {
    const Node& node = nodes_[node_index];
    return node.child_node_indices[child_index];
}

int Octree::get_octant_index(int node_index) const {
    const Node& node = nodes_[node_index];
    glm::vec3 center = (node.min + node.max) / 2.f;
    int x = center.x > 0 ? 1 : 0;
    int y = center.y > 0 ? 2 : 0;
    int z = center.z > 0 ? 4 : 0;
    return x + y + z;
}

bool Octree::node_exists(int node_index) const {
    return node_index >= 0 && node_index < nodes_.size();
}

int Octree::create_node(const glm::vec3& min, const glm::vec3& max) {
    int node_index = nodes_.size();
    nodes_.push_back(Node{min, max});
    return node_index;
}

bool Octree::node_contains_point(int node_index, const glm::vec3& point) const {
    const Node& node = nodes_[node_index];
    return (point.x >= node.min.x && point.x <= node.max.x &&
            point.y >= node.min.y && point.y <= node.max.y &&
            point.z >= node.min.z && point.z <= node.max.z);
}

int Octree::find_child_node_index(int node_index, const glm::vec3& point) const {
    const Node& node = nodes_[node_index];
    glm::vec3 center = (node.min + node.max) / 2.f;
    int child_index = (point.x > center.x) + 2 * (point.y > center.y) + 4 * (point.z > center.z);
    return node.child_node_indices[child_index];
}

void Octree::insert(const std::vector<glm::vec3>& points, int node_index, int depth) {
    if (points.empty()) {
        return;
    }

    // Insert each point into the octree
    for (int i = 0; i < points.size(); ++i) {
        const auto& point = points[i];

        // Traverse the octree to find the leaf node that contains the point
        while (!is_leaf(node_index)) {
            int child_index = find_child_node_index(node_index, point);
            int child_node_index = get_child_node_index(node_index, child_index);
            if (node_exists(child_node_index) && node_contains_point(child_node_index, point)) {
                node_index = child_node_index;
            } else {
                break;
            }
        }

        // Add the point to the leaf node
        nodes_[node_index].point_indices.push_back(i);

        // Subdivide the leaf node if necessary
        while (nodes_[node_index].point_indices.size() > 1 && depth > 0) {
            // Create child nodes
            const Node& node = nodes_[node_index];
            glm::vec3 center = (node.min + node.max) / 2.f;
            for (int child_index = 0; child_index < 8; ++child_index) {
                glm::vec3 child_min, child_max;
                int x = child_index & 1;
                int y = (child_index >> 1) & 1;
                int z = (child_index >> 2) & 1;
                child_min.x = x ? center.x : node.min.x;
                child_min.y = y ? center.y : node.min.y;
                child_min.z = z ? center.z : node.min.z;
                child_max.x = x ? node.max.x : center.x;
                child_max.y = y ? node.max.y : center.y;
                child_max.z = z ? node.max.z : center.z;
                int child_node_index = create_node(child_min, child_max);
                nodes_[node_index].child_node_indices[child_index] = child_node_index;
            }

            // Move points to child nodes
            for (int point_index : nodes_[node_index].point_indices) {
                const auto& point = points[point_index];
                int child_index = find_child_node_index(node_index, point);
                int child_node_index = get_child_node_index(node_index, child_index);
                nodes_[child_node_index].point_indices.push_back(point_index);
            }
            nodes_[node_index].point_indices.clear();

            // Traverse to child nodes and repeat
            for (int child_index = 0; child_index < 8; ++child_index) {
                int child_node_index = get_child_node_index(node_index, child_index);
                if (node_exists(child_node_index)) {
                    insert(points, child_node_index, depth - 1);
                }
            }
        }
    }
}

bool Octree::has_child_node(int i) {
    return false;
}

