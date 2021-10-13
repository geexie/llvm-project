#include "llvm/Transforms/DenisKabanov/DenisKabanov.h"

#define DEBUG_TYPE "DenisKabanov-count"
#include "llvm/ADT/Statistic.h"

//данный pass выводит имена всех функций в целевом файле.ll

using namespace llvm;
// PreservedAnalyses возвращает данные о том, изменили ли мы что-то в коде или нет 
// если код не изменён - проход без сайд эффектов (всё, что верно до нашего прохода - верно и после)
// если что-то изменилось - инвалидируем информацию о коде (последующим проходам придётся перезапускать анализ, так как будет трансформационный проход)
PreservedAnalyses DenisKabanovPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  errs() << "functions " << F.getName() << "\n"; // выводит название функции
  //FunctionAnalysisManager отвечает за зависимости  
  return PreservedAnalyses::all();
}
