#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

namespace TCB{
    class tetrahedron{
      public:
        ~tetrahedron();
        tetrahedron(
          const int& v1, const int& v2, const int& v3, const int& v4);
        const int& operator[](int i) const;

        /** Reverse the tetrahdron. */
        void reverse();

      private:
        int* vertices_;
    };
}

#endif //TETRAHEDRON_H
