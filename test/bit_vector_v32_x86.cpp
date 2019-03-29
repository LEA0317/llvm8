#include <iostream>

typedef bool v32i1 __attribute__((ext_vector_type(32)));

namespace bitvector {
  v32i1 build(bool *b) {
    v32i1 a;
    for (int i=0; i<32; i++) {
      a[i] = b[i];
    }
    return a;
  }

  uint32_t get(v32i1 a) {
    union ret_t {
      v32i1    vec;
      uint32_t ret_i;
    } t;
    t.vec = a;
    return t.ret_i;
  }

  void dump(v32i1 a) {
    int count=0;
    for (int i=0; i<4; i++) {
      for (int j=0; j<8; j++) {
	std::cout << a[count] << " ";
	count++;
      }
      std::cout << std::endl;
    }
  }

  v32i1 mult(v32i1 a, v32i1 b) {
    return a * b;
  }
}

int main(void) {
  bool array1[] = {0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,1,1,0,1};
  bool array2[] = {0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,1,1};
  v32i1 a = bitvector::build(array1);
  v32i1 b = bitvector::build(array2);

  v32i1 ret = bitvector::mult(a, b);

  std::cout << "vector" << std::endl;
  bitvector::dump(ret);
  std::cout << "scalar: " << bitvector::get(ret) << std::endl;

  return bitvector::get(ret);
}
