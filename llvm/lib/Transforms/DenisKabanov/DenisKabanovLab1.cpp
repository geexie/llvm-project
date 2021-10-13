#include "llvm/Transforms/DenisKabanov/DenisKabanovLab1.h"
#include "llvm/IR/InstIterator.h" // для shortcut-а к инструкциям функции
#include "llvm/Analysis/LoopInfo.h" // для получения данных о циклах
#include "llvm/ADT/Statistic.h"
#include <set>

#define DEBUG_TYPE "DenisKabanovLab1"

using namespace llvm;

ALWAYS_ENABLED_STATISTIC(FuncCounter, "Function counter");
ALWAYS_ENABLED_STATISTIC(BlockCounter, "Block counter");
ALWAYS_ENABLED_STATISTIC(OpCounter, "Arithmetic operation counter");
ALWAYS_ENABLED_STATISTIC(LoopCounter, "Loop counter");

PreservedAnalyses DenisKabanovLab1Pass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  // FunctionAnalysisManager &AM отвечает за зависимости между проходами и нужен для нахождения циклов
  errs() << "function: " << F.getName() << "\n";
  FuncCounter++;
  for (auto BB = F.begin(); BB != F.end(); ++BB){
    // F.begin(), F.end() - методы функции F для получения базовых блоков внутри себя 
    errs() << "    base block: " << BB->getName() << "\n";
    //errs() << "    base block size: " << BB->size() << "\n";
      // BB->size() возвращает число инструкций в базовом блоке BB
    // У каждого базового блока есть итератор для итерирования по инструкциям базового блока
    BlockCounter++;
    for (auto I = BB->begin(); I != BB->end(); ++I){
      // BB->begin(), BB->end() - возвращают адрес начальной и конечной инструкции внутри базового блока BB
      // I->getOpcode() - возвращает код операции/инструкции (например, сложения)
      errs() << "        instruction: " << I->getOpcode() << "\n";
      // id - instruction
      // 1 - return
      // 13 - "+" add/inc/dec
      // 15 - "-" sub
      // 17 - "*" mul
      // 20 - "/" div
      // 23 - "%" rem
      std::set<int> Operations{13, 15, 17, 20, 23};
      if (Operations.find(I->getOpcode()) != Operations.end())
        OpCounter++;
    }
  }

  // shortcut итератор для получения всех инструкций функции F
  //for (auto& I : instructions(F)){
  //  errs() << "        instruction:" << I.getOpcode() << "\n";
  //}
  auto& LA = AM.getResult<LoopAnalysis>(F); // получение данных о циклах в функции F
  for (auto& L : LA){
    errs() << "        loop:" << L->getName() << "\n";
    //L->getName() вернёт название/заголовок цикла
    LoopCounter++;
  }
  errs() << "Total stats after function: " << F.getName()
         << "\n\tFunction counter: " << FuncCounter
         << "\n\tBlock counter: " << BlockCounter
         << "\n\tArithmetic operation counter: " << OpCounter
         << "\n\tLoop counter: " << LoopCounter << "\n";
  return PreservedAnalyses::all();
}
