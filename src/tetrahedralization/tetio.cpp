#include "tetio.h"
#include "../macro.h"

#include <iostream>
#include <unordered_set>
#include <string>

struct pair_hash {
    template <class T1, class T2>
    size_t operator () (std::pair<T1, T2> const& pair) const {
        size_t h1 = std::hash<T1>()(pair.first);
        size_t h2 = std::hash<T2>()(pair.second);
        return h1 ^ h2;
    }
};

namespace TCB{
    int read_node(
        std::ifstream& infile,
        std::vector<Eigen::Vector3d>& nodes,
        std::vector<int>& boundary_markers
    ){
        if (!infile.good()){
            WARNING("Error reading file!");
            return 0;
        }

        bool first_info = true;
        int vertices_nb, dim, attribute, boundary_marker;

        std::string sline, s;
        while (std::getline(infile, sline)){
            std::istringstream ins(sline);
            ins >> s;

            if (s == "#") continue; // remarks

            if (first_info){
                vertices_nb = std::atoi(s.c_str());
                ins >> dim >> attribute >> boundary_marker;

                VERBOSE("vertices_nb = " << vertices_nb << ", dim = " << dim << ", attribute = " << attribute << ", boundary_marker = " << boundary_marker);

                std::vector<Eigen::Vector3d>(vertices_nb, Eigen::Vector3d(0, 0, 0)).swap(nodes);
                if (boundary_marker == 1){
                  std::vector<int>(vertices_nb, 0).swap(boundary_markers);
                }
                first_info = false;
            }
            else{
                int vi = std::atoi(s.c_str()) - 1;

                Eigen::Vector3d v;
                ins >> v.x() >> v.y() >> v.z();
                nodes[vi] = v;

                if (boundary_marker == 1){
                    int bm;
                    ins >> bm;
                    boundary_markers[vi] = bm;
                }
            }
        }

          return 1;
    }
    int read_node(
    std::ifstream& infile,
    std::vector<Eigen::Vector3d>& nodes
    ) {
        std::vector<int> boundary_markers;
        return read_node(infile, nodes, boundary_markers);
    }

    int write_mesh(
    std::ofstream& outfile,
    std::vector<Eigen::Vector3d>& vertices, std::vector<std::vector<int>>& faces,
    const std::string& file_format
    ) {
        if (!outfile.good()) {
            WARNING("Error writing file!");
            return 0;
        }

        if (file_format == "obj") {
            for (auto & v : vertices) {
                outfile << "v" << " " << v.transpose() << std::endl;
            }
            for (auto & pv : faces) {
                outfile << "f";
                for (auto & p : pv) {
                    outfile << " " << p + 1;
                }
                outfile << std::endl;
            }
        }
        else if (file_format == "off") {
            // count the number of edges
            std::unordered_set<std::pair<int, int>, pair_hash> edge_set;
            for (auto & pv : faces) {
                int prev_p = pv.back();
                for (auto & p : pv) {
                    edge_set.insert(std::pair<int, int>(prev_p, p));
                    prev_p = p;
                }
            }

            outfile << "OFF" << std::endl;
            outfile << vertices.size() << " " << faces.size() << " " << edge_set.size() << std::endl;
            for (auto & v : vertices) {
                outfile << v.transpose() << std::endl;
            }
            for (auto & pv : faces) {
                outfile << pv.size();
                for (auto & p : pv) {
                    outfile << " " << p + 1;
                }
                outfile << std::endl;
            }
        }
        else {
            WARNING("The output format is not supported!");
            return 0;
        }

        return 1;
    }
    int write_trimesh(
        std::ofstream& outfile,
        std::vector<Eigen::Vector3d>& vertices, std::vector<Eigen::Vector3i>& faces,
        const std::string& file_format
    ) {
        // convert Eigen::Vector3i to std::vector<int>
        std::vector<std::vector<int>> i_faces;
        i_faces.reserve(faces.size());
        for (auto & f : faces) {
            std::vector<int> i_f = {f.x(), f.y(), f.z()};
            i_faces.push_back(i_f);
        }

        return write_mesh(outfile, vertices, i_faces, file_format);
    }
    int write_points(
        std::ofstream& outfile,
        std::vector<Eigen::Vector3d>& vertices,
        const std::string& file_format
    ) {
        std::vector<std::vector<int>> faces;

        return write_mesh(outfile, vertices, faces, file_format);
    }
}