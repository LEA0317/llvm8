#include <iostream>

int main(int argc, char** argv) {
  for (int i=0; i<argc;i++) {
    std::cout << "hello, world1" << std::endl;
    for (int j=10; j>i; j--) {
      std::cout << "hello, world2" << std::endl;
      for (int k=0; k<i; k++) {
	std::cout << "hello, world3" << std::endl;
      }
    }
    std::cout << "hello, world4" << std::endl;
  }
  return 0;
}
