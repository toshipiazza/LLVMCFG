#define DEBUG_TYPE "cfg"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Pass.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

namespace {

  struct CFG : public FunctionPass {
    static char ID;
    CFG() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      // TODO
      return false;
    }
  };
}

char CFG::ID = 0;
static RegisterPass<CFG> X("cfg", "Control Flow Graph Pass");
// vim:tabstop=2:set shiftwidth=2:
