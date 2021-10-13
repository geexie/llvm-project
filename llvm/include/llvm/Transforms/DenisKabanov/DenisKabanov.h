#ifndef LLVM_TRANSFORMS_DENISKABANOV_H
#define LLVM_TRANSFORMS_DENISKABANOV_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class DenisKabanovPass : public PassInfoMixin<DenisKabanovPass> {
public:
// для запуска на модуле используем следующую команду (модуль состоит из символов глобальных переменных и функций)
// функции состоят из базовых блоков - набора последовательных инструкций
// итерация по llvm модулю: итерация по функциям -> итерация по базовым блокам -> итерация по инструкциям
// переопределяем метод run на функции
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM); };

} // namespace llvm

#endif // LLVM_TRANSFORMS_DENISKABANOV_H
