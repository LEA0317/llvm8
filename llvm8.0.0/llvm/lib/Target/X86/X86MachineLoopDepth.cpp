//===-- X86MachineLoopDepth.cpp ---===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//

#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineLoopInfo.h"
#include "llvm/CodeGen/MachineDominators.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/DebugLoc.h"

#include "X86.h"
#include "X86Subtarget.h"
#include "X86RegisterInfo.h"

#include <iostream>

#define DEBUG_TYPE "x86-ml-depth"

using namespace llvm;

namespace llvm {
  FunctionPass *createX86MachineLoopDepthPass();
}

namespace {
  struct X86MachineLoopDepth : public MachineFunctionPass {
    explicit X86MachineLoopDepth() 
      : MachineFunctionPass(ID) {
      initializeX86MachineLoopDepthPass(*PassRegistry::getPassRegistry());
    }

    StringRef getPassName() const override {
      return "X86 print machine loop depth";
    }

    bool runOnMachineFunction(MachineFunction &F) override;

    virtual void
    getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.addRequired<MachineLoopInfo>();
      AU.addPreservedID(MachineDominatorTree::ID);
      MachineFunctionPass::getAnalysisUsage(AU);
    }
    
    static char ID;
  };
  char X86MachineLoopDepth::ID = 0;
}

INITIALIZE_PASS(X86MachineLoopDepth,
		"x86-ml-depth",
		"X86 Machineloop Depth",
		false,
		false)

FunctionPass*
llvm::createX86MachineLoopDepthPass(void) {
  return new X86MachineLoopDepth();
}

bool
X86MachineLoopDepth::runOnMachineFunction(MachineFunction &F) {
  LLVM_DEBUG(dbgs() << ("== X86MachineLoopDepth ==\n"));

  // Get MachineLoopInfo
  const  MachineLoopInfo *MLI = &getAnalysis<MachineLoopInfo>();
  
  for (MachineFunction::iterator MFI = F.begin(), MFIE = F.end(); MFI != MFIE; MFI++) {
    MachineBasicBlock *BB = (MachineBasicBlock*)&(*MFI);

    // Get Loop Depth from MachineLoopInfo
    int MLDepth = MLI->getLoopDepth(BB);

    std::cout << ">> loop depth ( " << MLDepth << " )" << std::endl;
    BB->dump();
    std::cout << std::endl;
  }

  return false;
}
