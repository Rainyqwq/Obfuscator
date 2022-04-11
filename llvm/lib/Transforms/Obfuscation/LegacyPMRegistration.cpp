#include "Transforms/Obfuscation/BogusControlFlow.h"
#include "Transforms/Obfuscation/Flattening.h"
#include "Transforms/Obfuscation/Split.h"
#include "Transforms/Obfuscation/Substitution.h"
#include "Transforms/Obfuscation/StringObfuscation.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

static void registerOllvmPass(const PassManagerBuilder &,
                              legacy::PassManagerBase &PM) {

    PM.add(createBogus(true));
#if LLVM_VERSION_MAJOR >= 9
    PM.add(createLowerSwitchPass());
#endif
    PM.add(createFlattening(true));
    PM.add(createSplitBasicBlock(true));
    PM.add(createSubstitution(true));
}

static void registerOllvmModulePass(const PassManagerBuilder &,
                              legacy::PassManagerBase &PM) {
    PM.add(createStringObfuscation(true));
}

static RegisterStandardPasses
        RegisterMyPass1(PassManagerBuilder::EP_EnabledOnOptLevel0,
                       registerOllvmModulePass);
static RegisterStandardPasses
        RegisterMyPass2(PassManagerBuilder::EP_OptimizerLast,
                        registerOllvmModulePass);
static RegisterStandardPasses
        RegisterMyPass3(PassManagerBuilder::EP_EarlyAsPossible,
                       registerOllvmFunctionPass);