#include "tetrahedralization/tetio.h"
#include "macro.h"

#include <fstream>
#include <string>
// Eigen
#include <Eigen/Dense>


int main(int argc, char *argv[])
{
  std::ifstream infile;
  infile.open(std::string(OUTPUT_PATH) + "test.1.node");

  std::vector<Eigen::Vector3d> nodes;

  TCB::read_node(infile, nodes);

  std::ofstream outfile;
  outfile.open(std::string(OUTPUT_PATH) + "output.obj");
  TCB::write_points(outfile, nodes);


  return 0;
}