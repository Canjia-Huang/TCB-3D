#ifndef TETIO_H
#define TETIO_H

#include <fstream>
#include <vector>
// Eigen
#include <Eigen/Dense>

namespace TCB {
    /** @brief Read tetgen .node file.
     * @param[in] infile: input file std::ifstream
     * @param[out] nodes: nodes, in the format of Eigen::Vector3d
     * @param[out] boundary_markers: (alternative) whether the point is a boundary point，0: no, 1: yes
     * @return success or not */
    int read_node(
        std::ifstream& infile,
        std::vector<Eigen::Vector3d>& nodes,
        std::vector<int>& boundary_markers);
    int read_node(
        std::ifstream& infile,
        std::vector<Eigen::Vector3d>& nodes);

    int write_mesh(
        std::ofstream& outfile,
        std::vector<Eigen::Vector3d>& vertices, std::vector<std::vector<int>>& faces,
        const std::string& file_format = "obj");
    int write_trimesh(
        std::ofstream& outfile,
        std::vector<Eigen::Vector3d>& vertices, std::vector<Eigen::Vector3i>& faces,
        const std::string& file_format = "obj");
    int write_points(
        std::ofstream& outfile,
        std::vector<Eigen::Vector3d>& vertices,
        const std::string& file_format = "obj");
}

#endif //TETIO_H
