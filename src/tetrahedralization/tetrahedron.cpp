#include "tetrahedron.h"

namespace TCB {
    tetrahedron::~tetrahedron() {
      delete[] vertices_;
    }

    tetrahedron::tetrahedron(
        const int& v1, const int& v2, const int& v3, const int& v4
        ){
        vertices_ = new int[4];
        vertices_[0] = v1; vertices_[1] = v2; vertices_[2] = v3; vertices_[3] = v4;
    }

    const int& tetrahedron::operator[](int i) const {
      return vertices_[i];
    }

    void tetrahedron::reverse() {
        int temp = vertices_[0];
        vertices_[0] = vertices_[1]; vertices_[1] = temp;
    }
}