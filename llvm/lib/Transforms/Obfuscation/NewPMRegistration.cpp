#include "Transforms/Obfuscation/BogusControlFlow.h"
#include "Transforms/Obfuscation/Flattening.h"
#include "Transforms/Obfuscation/Split.h"
#include "Transforms/Obfuscation/Substitution.h"
#include "Transforms/Obfuscation/StringObfuscation.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"

llvm::PassPluginLibraryInfo getOllvmPluginInfo() {
  return {
    LLVM_PLUGIN_API_VERSION, "Obfuscation", LLVM_VERSION_STRING,
        [](PassBuilder &PB) {

            // #1 注册标记 "opt -passes=obf-bcf"
            PB.registerPipelineParsingCallback(
              [&](StringRef Name, FunctionPassManager &FPM,
                  ArrayRef<PassBuilder::PipelineElement>) {
                if (Name == "obf-bcf") {
                  FPM.addPass(BogusControlFlowPass());
                  return true;
                }
                if(Name == "obf-fla"){
                  FPM.addPass(FlatteningPass());
                  return true;
                }
                if(Name == "obf-sub"){
                  FPM.addPass(SubstitutionPass());
                  return true;
                }
                if(Name == "obf-split"){
                  FPM.addPass(SplitBasicBlockPass());
                  return true;
                }
                return false;
              });
            PB.registerPipelineParsingCallback(
              [&](StringRef Name, ModulePassManager &MPM,
                  ArrayRef<PassBuilder::PipelineElement>) {
                if (Name == "obf-str") {
                  MPM.addPass(StringObfuscationPass());
                  return true;
                }
                return false;
              });

            // #2 找到具体时机插入pass
            //registerVectorizerStartEPCallback这个方法插入需要加-O1的flag不然可能不生效会被跳过
            PB.registerVectorizerStartEPCallback(
              [](llvm::FunctionPassManager &PM,
                 llvm::PassBuilder::OptimizationLevel Level) {
                PM.addPass(SplitBasicBlockPass());
                PM.addPass(BogusControlFlowPass());
                #if LLVM_VERSION_MAJOR >= 9
                    PM.addPass(LowerSwitchPass());
                #endif
                PM.addPass(FlatteningPass());
                PM.addPass(SubstitutionPass());
                
              });
            PB.registerPipelineStartEPCallback(
              [](llvm::ModulePassManager &PM,
                 llvm::PassBuilder::OptimizationLevel Level) {
                PM.addPass(StringObfuscationPass());
              });
          
        };
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getOllvmPluginInfo();
}