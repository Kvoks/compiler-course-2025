// RUN: %clang_cc1 -load %llvmshlibdir/ImplicitConvPlugin_Khovansky_Dmitry_FIIT2_ClangAST%pluginext -plugin ImplicitConvPlugin -fsyntax-only %s 2>&1 | FileCheck %s

// Проверка глобального скоупа
// CHECK: In global scope:
// CHECK-NEXT: int -> double: 1
static double GlobalPar = 42;

// Проверка задач варианта
// CHECK: Function: Sum
// CHECK-NEXT: float -> double: 1
// CHECK-NEXT: int -> float: 1

// CHECK: Function: Mul
// CHECK-NEXT: double -> int: 1
// CHECK-NEXT: float -> double: 1
// CHECK-NEXT: float -> int: 1

static double Sum(int A, float B) {
    return A + B;
}

static int Mul(float A, float B) {
    return A + Sum(A, B);
}

// Проверка обычной функции с несколькими преобразованиями
// CHECK: Function: StandartFunc
// CHECK-NEXT: float -> double: 2
// CHECK-NEXT: int -> float: 1
// CHECK-NEXT: int -> bool: 1

static void StandartFunc(float F) {
    double D = F;
    float X = 3;
    bool Flag = 10;
    double K = F;
}

// Проверка return с преобразованием
// CHECK: Function: MakeBool
// CHECK-NEXT: int -> bool: 1

static bool MakeBool() {
    return 100;
}

// Проверка указателей
// CHECK: Function: PointerTest
// CHECK-NEXT: nullptr_t -> char *: 1
// CHECK-NEXT: char * -> void *: 1

static void PointerTest() {
    char* P = nullptr;
    void* Vp = P;
}

