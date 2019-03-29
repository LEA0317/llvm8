#include <iostream>

// not good codegen
typedef bool v64i1 __attribute__((ext_vector_type(64)));

namespace bitvector {
  v64i1 build(bool *b) {
    v64i1 a;
    for (int i=0; i<64; i++) {
      a[i] = b[i];
    }
    return a;
  }

  v64i1 convert(uint64_t i) {
    union ret_t {
      v64i1    vec;
      uint64_t ret_i;
    } t;
    t.ret_i = i;
    return t.vec;
  }

  uint64_t get(v64i1 a) {
    union ret_t {
      v64i1    vec;
      uint64_t ret_i;
    } t;
    t.vec = a;
    return t.ret_i;
  }

  void dump(v64i1 a) {
    int count=0;
    for (int i=0; i<8; i++) {
      for (int j=0; j<8; j++) {
	std::cout << a[count] << " ";
	count++;
      }
      std::cout << std::endl;
    }
  }

  v64i1 mult(v64i1 a, v64i1 b) {
    return a * b;
  }

  v64i1 add(v64i1 a, v64i1 b) {
    return a + b;
  }

  v64i1 sub(v64i1 a, v64i1 b) {
    return a - b;
  }

  v64i1 neg(v64i1 a) {
    return ~a;
  }

  v64i1 zeros(void) {
    v64i1 a;
    for (int i=0; i<64; i++) {
      a[i] = 0;
    }
    return a;
  }

  v64i1 ones(void) {
    v64i1 a;
    for (int i=0; i<64; i++) {
      a[i] = 1;
    }
    return a;
  }
}

int main(void) {
  bool array1[] = {0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,1,1,0,1};
  bool array2[] = {0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,1,1};
  v64i1 a = bitvector::build(array1);
  v64i1 b = bitvector::build(array2);
  std::cout << "b" << std::endl;
  bitvector::dump(b);
  std::cout << "inverse of b" << std::endl;
  bitvector::dump(bitvector::neg(b));

  std::cout << "converted vector" << std::endl;
  v64i1 c = bitvector::convert(11);
  bitvector::dump(c);

  v64i1 ret = bitvector::mult(a, b);

  std::cout << "result vector" << std::endl;
  bitvector::dump(ret);
  //std::cout << "scalar: " << bitvector::get(ret) << std::endl;

  return 0; //bitvector::get(ret);
}
