#include <iostream>
#include <omp.h> // OpenMP 기능을 사용하기 위한 필수 헤더

int main() {
    std::cout << "=== OpenMP 병렬 처리 시작 ===" << std::endl;

    // 이 아래의 중괄호 영역을 가능한 모든 스레드를 동원해서 병렬로 실행하라는 마법의 주문입니다.
    #pragma omp parallel
    {
        // 각 스레드는 자신이 몇 번째 스레드인지(ID), 전체 스레드는 몇 개인지 확인합니다.
        int thread_id = omp_get_thread_num();
        int total_threads = omp_get_num_threads();

        // cout은 병렬 처리 시 문자가 심하게 섞일 수 있어 printf를 사용하는 것이 좋습니다.
        printf("안녕하세요! 저는 %d번 스레드입니다. (전체 스레드: %d개)\n", thread_id, total_threads);
    }

    std::cout << "=== OpenMP 병렬 처리 종료 ===" << std::endl;
    return 0;
}