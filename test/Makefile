all: test.s

bitvec: bit_vector_v32_x86.s bit_vector_v64_x86.s bit_vector_v128_x86.s

llvm:
	@echo "** build llvm **"
	cd ../llvm8.0.0 && ./build_compiler.sh

clean:
	@echo "** remove generated files **"
	rm *.ll *.s  *~

test.s:
	@echo "** test **"
	../llvm8.0.0/build/bin/clang++ -S -emit-llvm test.cpp
	../llvm8.0.0/build/bin/llc -x86-dump-mbb test.ll
	#../llvm8.0.0/build/bin/llc test.ll

bit_vector_v32_x86.s:
	@echo "**  v32 test(x86)  **"
	../llvm8.0.0/build/bin/clang++ -march=core-avx2 \
		-S -std=c++11 -O3 bit_vector_v32_x86.cpp

bit_vector_v64_x86.s:
	@echo "**  v64 test(x86)  **"
	../llvm8.0.0/build/bin/clang++ -march=core-avx2 \
		-S -std=c++11 -O3 bit_vector_v64_x86.cpp

bit_vector_v128_x86.s:
	@echo "**  v128 test(x86)  **"
	../llvm8.0.0/build/bin/clang++ -march=core-avx2 \
		-S -std=c++11 -O3 bit_vector_v128_x86.cpp
