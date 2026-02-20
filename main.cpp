#include <iostream>
#include <cstdlib> // malloc, free를 사용하기 위한 헤더

// 포인터를 매개변수로 받아 배열의 값을 더하는 함수
// 병렬 컴퓨팅에서는 이 함수 내부의 반복문을 여러 스레드가 나눠서 처리하게 됩니다.
void addVectors(float* a, float* b, float* result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] + b[i];
    }
}

int main() {
    // 1. 데이터 크기 설정 (예: 1억 개의 데이터)
    // 병렬 처리는 데이터가 작으면 오히려 스레드 생성 비용 때문에 느려집니다.
    int size = 100000000; 
    size_t bytes = size * sizeof(float);

    // 2. 동적 메모리 할당 (Heap 영역 사용)
    // 일반적인 배열(float a[size])은 크기가 너무 크면 Stack Overflow가 발생합니다.
    // CUDA에서도 GPU 메모리를 할당할 때 이와 매우 유사한 구조(cudaMalloc)를 사용합니다.
    float* A = (float*)malloc(bytes);
    float* B = (float*)malloc(bytes);
    float* C = (float*)malloc(bytes);

    // 3. 데이터 초기화
    for (int i = 0; i < size; i++) {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }

    // 4. 연산 수행 (이 부분을 나중에 OpenMP나 CUDA 코드로 병렬화하게 됩니다)
    std::cout << "벡터 덧셈을 시작합니다..." << std::endl;
    addVectors(A, B, C, size);

    // 5. 결과 검증 (첫 번째 값만 확인)
    std::cout << "C[0]의 값: " << C[0] << " (예상값: 3.0)" << std::endl;

    // 6. 메모리 해제 (매우 중요!)
    // 할당받은 메모리를 OS에 반환하지 않으면 메모리 누수(Memory Leak)가 발생합니다.
    free(A);
    free(B);
    free(C);

    return 0;
}