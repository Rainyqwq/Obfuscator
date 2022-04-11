// LLVM include
#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h" //new Pass

namespace llvm {
      Pass* createStringObfuscation(bool flag);
      class StringObfuscationPass : public PassInfoMixin<StringObfuscationPass>{ 
        public:
            PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM);

            static bool isRequired() { return true; }
      };
}
