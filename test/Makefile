all: test.s

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
