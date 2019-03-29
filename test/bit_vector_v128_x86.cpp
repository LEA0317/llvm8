#include <iostream>

// too long vector length
typedef bool v128i1 __attribute__((ext_vector_type(128)));

namespace bitvector {
  v128i1 build(bool *b) {
    v128i1 a;
    for (int i=0; i<128; i++) {
      a[i] = b[i];
    }
    return a;
  }

  v128i1 convert(unsigned long long int i) {
    union ret_t {
      v128i1                 vec;
      unsigned long long int ret_i;
    } t;
    t.ret_i = i;
    return t.vec;
  }

  /*
  unsigned long long int get(v128i1 a) {
    union ret_t {
      v128i1                 vec;
      unsigned long long int ret_i;
    } t;
    for (int i=0; i<128; i++) {
      t.vec[i] = a[i];
    }
    return t.ret_i;
  }
  */

  void dump(v128i1 a) {
    int count=0;
    for (int i=0; i<16; i++) {
      for (int j=0; j<8; j++) {
	std::cout << a[count] << " ";
	count++;
      }
      std::cout << std::endl;
    }
  }

  v128i1 mult(v128i1 a, v128i1 b) {
    return a * b;
  }

  v128i1 add(v128i1 a, v128i1 b) {
    return a + b;
  }

  v128i1 sub(v128i1 a, v128i1 b) {
    return a - b;
  }

  v128i1 neg(v128i1 a) {
    return ~a;
  }

  v128i1 zeros(void) {
    v128i1 a;
    for (int i=0; i<128; i++) {
      a[i] = 0;
    }
    return a;
  }

  v128i1 ones(void) {
    v128i1 a;
    for (int i=0; i<128; i++) {
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
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
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
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,0,0,
		   0,0,0,0,0,0,1,1};
  v128i1 a = bitvector::build(array1);
  v128i1 b = bitvector::build(array2);
  std::cout << "b" << std::endl;
  bitvector::dump(b);
  std::cout << "inverse of b" << std::endl;
  bitvector::dump(bitvector::neg(b));

  std::cout << "converted vector" << std::endl;
  v128i1 c = bitvector::convert(11);
  bitvector::dump(c);

  v128i1 ret = bitvector::mult(a, b);

  std::cout << "result vector" << std::endl;
  bitvector::dump(ret);
  //std::cout << "scalar: " << bitvector::get(ret) << std::endl;

  return 0; //bitvector::get(ret);
}
