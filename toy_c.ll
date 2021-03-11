; ModuleID = 'C:\Users\HP\toy_c.c'
source_filename = "C:\\Users\\HP\\toy_c.c"
target datalayout = "e-m:w-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-windows-msvc19.24.28314"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local <4 x float> @foo(<4 x float> %a, <4 x float> %b) #0 {
entry:
  %b.addr = alloca <4 x float>, align 16
  %a.addr = alloca <4 x float>, align 16
  store <4 x float> %b, <4 x float>* %b.addr, align 16
  store <4 x float> %a, <4 x float>* %a.addr, align 16
  %0 = load <4 x float>, <4 x float>* %a.addr, align 16
  %1 = load <4 x float>, <4 x float>* %b.addr, align 16
  %2 = load <4 x float>, <4 x float>* %a.addr, align 16
  %mul = fmul <4 x float> %1, %2
  %add = fadd <4 x float> %0, %mul
  ret <4 x float> %add
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="none" "min-legal-vector-width"="128" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 2}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 13.0.0 (https://github.com/anastasiaudachina/llvm-project.git 99b0032ce0b8afa67a36da2b8c02cfcacdc561d1)"}
