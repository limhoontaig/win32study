// c++forEfficiency.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//


#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void fn1(const std::size_t size) {
    const size_t N = size;
    const size_t M = size;
    std::vector<std::vector<int>> arr(N, std::vector<int>(M, 0));

    auto start = std::chrono::system_clock::now();
    for (std::size_t i = 0; i < N; i++) {
        for (std::size_t j = 0; j < M; j++) {
            arr[i][j] = i + j;
            arr[i][j] *= 2;
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "fn1 : " << diff.count() << std::endl;
}

void fn2(const std::size_t size) {
    const size_t N = size;
    const size_t M = size;
    std::vector<std::vector<int>> arr(N, std::vector<int>(M, 0));

    auto start = std::chrono::system_clock::now();
    for (std::size_t j = 0; j < M; j++) {
        for (std::size_t i = 0; i < N; i++) {
            arr[i][j] = i + j;
            arr[i][j] *= 2;
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "fn2 : " << diff.count() << std::endl;
}

int main(void) {
    constexpr std::size_t size = 20000;
    std::thread t1(fn1, size);
    std::thread t2(fn2, size);

    return 0;
}