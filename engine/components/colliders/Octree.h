#include <iostream>
#include <vector>
#include <glm/glm.hpp>

class Octree {
public:
    Octree(const glm::vec3& min, const glm::vec3& max, int max_depth) : depth_(max_depth) {
        // Create root node
        nodes_.resize(1);
        nodes_[0].min = min;
        nodes_[0].max = max;
    }

    Octree(const std::vector<glm::vec3> &points, const glm::vec3 &min, const glm::vec3 &max, int max_depth);

    void insert(const std::vector<glm::vec3>& points, int node_index=0, int depth=8);
    [[nodiscard]] bool node_exists(int node_index) const;
    [[nodiscard]] bool is_leaf(int node_index) const;
    [[nodiscard]] int get_child_node_index(int node_index, int child_index) const;
    [[nodiscard]] int get_octant_index(int node_index) const;

    bool has_child_node(int i);

private:
    struct Node {
        glm::vec3 min;
        glm::vec3 max;
        std::vector<int> point_indices;
        int child_node_indices[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
    };

    int depth_;
    std::vector<Node> nodes_;

    int create_node(const glm::vec3& min, const glm::vec3& max);
    [[nodiscard]] bool node_contains_point(int node_index, const glm::vec3& point) const;
    [[nodiscard]] int find_child_node_index(int node_index, const glm::vec3& point) const;
};