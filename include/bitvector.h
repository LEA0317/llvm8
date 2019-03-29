#include <iostream>

#ifndef __HEADER_LOWBIT_VECTOR__
#define __HEADER_LOWBIT_VECTOR__

typedef bool v32i1 __attribute__((ext_vector_type(32)));

namespace bitvector {
  v32i1 build(bool *b) {
    v32i1 a;
    for (int i=0; i<32; i++) {
      a[i] = b[i];
    }
    return a;
  }

  v32i1 convert(uint32_t i) {
    union ret_t {
      v32i1    vec;
      uint32_t ret_i;
    } t;
    t.ret_i = i;
    return t.vec;
  }

  uint32_t get(v32i1 a) {
    union ret_t {
      v32i1    vec;
      uint32_t ret_i;
    } t;
    t.vec = a;
    return t.ret_i;
  }

  v32i1 mult(v32i1 a, v32i1 b) {
    return a * b;
  }

  v32i1 add(v32i1 a, v32i1 b) {
    return a + b;
  }

  v32i1 sub(v32i1 a, v32i1 b) {
    return a - b;
  }

  v32i1 neg(v32i1 a) {
    return ~a;
  }

  // clang optimize this code (so, simple implementation)
  v32i1 zeros(void) {
    v32i1 a;
    for (int i=0; i<32; i++) {
      a[i] = 0;
    }
    return a;
  }

  // clang optimize this code (so, simple implementation)
  v32i1 ones(void) {
    v32i1 a;
    for (int i=0; i<32; i++) {
      a[i] = 1;
    }
    return a;
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
}

#endif
