#include <iostream>
#include <cstdlib>
#include <omp.h> // OpenMP 기능과 시간 측정 함수를 쓰기 위해 필수

// 병렬 덧셈 함수
void addVectors(float* a, float* b, float* result, int size) {
    // 이 한 줄만 쓰면, 아래의 for 반복문을 스레드들이 자동으로 N등분해서 나눠 가집니다.
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    int size = 100000000; // 1억 개 데이터 (약 400MB)
    size_t bytes = size * sizeof(float);

    float* A = (float*)malloc(bytes);
    float* B = (float*)malloc(bytes);
    float* C = (float*)malloc(bytes);

    // 데이터 초기화도 1억 번 해야 하니, 여기서도 병렬 처리를 해줍니다!
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }

    std::cout << "=== 스레드 32개가 1억 번 덧셈을 시작합니다 ===" << std::endl;

    // OpenMP 전용 초정밀 타이머 작동 시작!
    double start_time = omp_get_wtime();

    addVectors(A, B, C, size);

    // 타이머 종료!
    double end_time = omp_get_wtime();

    std::cout << "C[0]의 값: " << C[0] << " (예상값: 3.0)" << std::endl;
    std::cout << "걸린 시간: " << (end_time - start_time) << " 초" << std::endl;

    free(A);
    free(B);
    free(C);

    return 0;
}