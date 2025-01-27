#include "tetrahedralization/tetio.h"
#include "macro.h"

#include <fstream>
#include <string>
// Eigen
#include <Eigen/Dense>


int main(int argc, char *argv[])
{
  std::vector<Eigen::Vector3d> nodes;
  std::vector<std::vector<int>> tets;

  {
    std::ifstream infile;
    infile.open(std::string(OUTPUT_PATH) + "test.1.node");
    TCB::read_nodes(infile, nodes);
  }
  {
    std::ifstream infile;
    infile.open(std::string(OUTPUT_PATH) + "test.1.ele");
    TCB::read_tets(infile, tets);
  }

  {
    std::ofstream outfile;
    outfile.open(std::string(OUTPUT_PATH) + "output.obj");
    TCB::write_tets(outfile, nodes, tets, 0.5);
  }



  return 0;
}