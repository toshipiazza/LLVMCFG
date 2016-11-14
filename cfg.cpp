#define DEBUG_TYPE "cfg"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"

using namespace llvm;

namespace {

  struct CBRVisitor :
      public InstVisitor<CBRVisitor> {
    bool changed = false;
    void visitBranchInst(BranchInst &BI) {
      if (BI.isConditional()) {
        // victimize the true and false branches
      }
    }
  };

  struct CFG : public BasicBlockPass {
    static char ID;
    CFG() : BasicBlockPass(ID) { }
    bool runOnBasicBlock(BasicBlock &B) override {
      CBRVisitor cbrVisitor;
      cbrVisitor.visit(B);
      return cbrVisitor.changed;
    }
  };

}

char CFG::ID = 0;
static RegisterPass<CFG> X("cfg", "Control Flow Graph Pass");
