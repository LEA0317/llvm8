#ifndef HEADER_X86_UTIL
#define HEADER_X86_UTIL

#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/PassAnalysisSupport.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"

#include <iostream>

#define B(X) (X->begin())
#define E(X) (X->end())

inline bool
isBranchMI(llvm::MachineInstr* mi) {
  if (mi->isBranch()) {
    return true;
  }
  return false;
}

inline bool
isConditionalBranchMI(llvm::MachineInstr* mi) {
  if (mi->isBranch() && !mi->isBarrier() && !mi->isCall()) {
    return true;
  }
  return false;
}

inline bool
X86SimpleLoopAnalyzer(llvm::MachineBasicBlock *MBB) {
  llvm::MachineBasicBlock::iterator MBBI;
  llvm::MachineInstr               *BranchMI   = nullptr;
  int                               num_branch = 0;

  for (MBBI = B(MBB); MBBI != E(MBB); MBBI++) {
    llvm::MachineInstr* MI = (llvm::MachineInstr*)&(*MBBI);
    if (isBranchMI(MI)) {
      BranchMI = MI;
      num_branch++;

      if (num_branch > 1) {
	return false;
      }
    }
  }

  // one branch check
  if (num_branch != 1) {
    return false;
  }

  // simple loop structure check
  {
    if (!isConditionalBranchMI(BranchMI)) {
      return false;
    }

    llvm::MachineBasicBlock *TargetMBB = BranchMI->getOperand(0).getMBB();
 
    if (TargetMBB->getNumber()      != MBB->getNumber()
	|| TargetMBB->getFullName() != MBB->getFullName()) {
      return false;
    }
  }

  return true;
}

#endif
