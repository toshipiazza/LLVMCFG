#define DEBUG_TYPE "cfg"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"


using namespace llvm;

namespace {

  BasicBlock *make_taken_branch(BranchInst &BI)
  {
      auto taken = BasicBlock::Create(BI.getContext(),
          "cfg::taken", BI.getFunction());
      IRBuilder<> taken_builder(taken);

      // TODO: call clean call
      // create unconditional jump to original target
      taken_builder.CreateBr(cast<BasicBlock>(BI.getOperand(2)));

      return taken;
  }

  BasicBlock *make_not_taken_branch(BranchInst &BI)
  {
      auto not_taken = BasicBlock::Create(BI.getContext(),
          "cfg::not_taken", BI.getFunction());
      IRBuilder<> not_taken_builder(not_taken);

      // TODO: call clean call
      // create unconditional jump to original fallthrough
      not_taken_builder.CreateBr(cast<BasicBlock>(BI.getOperand(1)));
      return not_taken;
  }

  struct CBRVisitor :
      public InstVisitor<CBRVisitor> {
    bool changed = false;
    void visitBranchInst(BranchInst &BI) {
      if (BI.isConditional()) {
        // victimize the true and false branches
        errs() << "Found conditional branch " << BI << "\n";
 
        // use IRBuilder to create two new basic blocks
        auto taken = make_taken_branch(BI);
        auto not_taken = make_not_taken_branch(BI);

        // hook up original branch instruction to our new branches
        BI.setOperand(2, taken);
        BI.setOperand(1, not_taken);
        changed = true;
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
// vim: tabstop=2:shiftwidth=2:
