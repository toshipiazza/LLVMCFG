#define DEBUG_TYPE "cfg"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"


using namespace llvm;

namespace {

  void CreateCall(ArrayRef<Value *> args, BranchInst &BI, Instruction *before) {
    auto &context = BI.getContext();
    auto func = BI.getModule()->getOrInsertFunction("__note_taken",
                                                    Type::getVoidTy(context),
                                                    Type::getInt8PtrTy(context),
                                                    Type::getInt8PtrTy(context),
                                                    nullptr);
    CallInst::Create(func, args, "", before);
  }


  void InstrumentBranch(BranchInst &BI, int idx) {
    auto targ = dyn_cast<BasicBlock>(BI.getOperand(idx));
    auto bb = BI.getParent();
    if (&bb->getParent()->getEntryBlock() != BI.getParent()) {
      Value *args[] = 
        { BlockAddress::get(bb),
          BlockAddress::get(targ) };
      CreateCall(args, BI, targ->getFirstNonPHIOrDbgOrLifetime());
    } else {
      // we cannot take the BlockAddress of this instruction...
      // so we must get a pointer to the function itself
      // TODO
    }
  }


  struct CBRVisitor :
      public InstVisitor<CBRVisitor> {
    bool changed = false;
    void visitBranchInst(BranchInst &BI) {
      if (BI.isConditional()) {
        InstrumentBranch(BI, 2);
        InstrumentBranch(BI, 1);
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
