//===------- X86ExpandPseudo.cpp - Expand pseudo instructions -------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a pass that expands pseudo instructions into target
// instructions to allow proper scheduling, if-conversion, other late
// optimizations, or simply the encoding of the instructions.
//
//===----------------------------------------------------------------------===//

#include "X86.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/Passes.h" // For IDs of passes that are preserved.
#include "llvm/IR/GlobalValue.h"
using namespace llvm;

#define DEBUG_TYPE "x86-dump-mbb"

namespace {
class X86DumpMBB : public MachineFunctionPass {
public:
  static char ID;
  X86DumpMBB() : MachineFunctionPass(ID) {}

  bool runOnMachineFunction(MachineFunction &Fn) override;

  StringRef getPassName() const override {
    return "X86 dump machine basic block pass";
  }
};
char X86DumpMBB::ID = 0;
} // End anonymous namespace.

bool X86DumpMBB::runOnMachineFunction(MachineFunction &MF) {
  for (MachineBasicBlock &MBB : MF) {
    MBB.dump();
  }
  return false;
}

/// Returns an instance of the pseudo instruction expansion pass.
FunctionPass *llvm::createX86DumpMBBPass() {
  return new X86DumpMBB();
}
