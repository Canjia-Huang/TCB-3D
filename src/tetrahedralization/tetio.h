#ifndef TETIO_H
#define TETIO_H

#include <fstream>
#include <vector>
// Eigen
#include <Eigen/Dense>

namespace TCB {
    /** @brief Read tetgen .node file.
     * @param[in] infile: input .node file std::ifstream
     * @param[out] nodes: nodes, in the format of Eigen::Vector3d
     * @param[out] boundary_markers: (alternative) whether the point is a boundary point，0: no, 1: yes
     * @return success or not */
    int read_nodes(
        std::ifstream& infile,
        std::vector<Eigen::Vector3d>& nodes,
        std::vector<int>& boundary_markers);
    int read_nodes(
        std::ifstream& infile,
        std::vector<Eigen::Vector3d>& nodes);

    /** @brief Read tetgen .ele file
     * @param[in] infile: input .ele file std::ifstream
     * @param[out] tets: tetrahedra, in the format of std::vector<int>
     *                  indices of the vertices that make up the tetrahedron (start from 1),
     *                  the size of std::vector is 4 or 10
     * @return success or not */
    int read_tets(
        std::ifstream& infile,
        std::vector<std::vector<int>>& tets);

    /** @brief Write surface mesh to some formats.
     * @details currently supported output formats: obj (default), off
     * @param[in] outfile: output file std::ofstream
     * @param[in] vertices: vertices that need to output
     * @param[in] faces: faces that need to output
     * @param[in] file_format: output formats, default to "obj"
     * @return success or not */
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

    /** @brief Write tetrahedral mesh to some formats.
     * @details currently supported output formats is same as write_mesh()
     * @param[in] outfile: output file std::ofstream
     * @param[in] nodes: the nodes of the tetrahedral mesh
     * @param[in] tets: the array of tetrahedra
     * @param[in] scaling: scaling ratio, default to 1
     * @param[in] file_format: output formats, default to "obj"
     * @return success or not */
    int write_tets(
        std::ofstream& outfile,
        std::vector<Eigen::Vector3d>& nodes, std::vector<std::vector<int>>& tets,
        const double& scaling = 1.,
        const std::string& file_format = "obj");
}

#endif //TETIO_H
