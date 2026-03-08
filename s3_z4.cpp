#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

class TaskTimer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    bool running;

public:
    TaskTimer() : running(false) {}

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        running = true;
    }

    void stop() {
        if (running) {
            end_time = std::chrono::high_resolution_clock::now();
            running = false;
        }
    }

    long long getDuration() {
        if (!running) {
            return std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
        }
        return 0;
    }

    void measureSorting(std::vector<int>& arr) {
        start();
        std::sort(arr.begin(), arr.end());
        stop();
        std::cout << "Sorting time: " << getDuration() << " milliseconds" << std::endl;
    }
};

int main() {
    TaskTimer timer;
    std::vector<int> arr(100000);

    // Fill array with random numbers
    for (int i = 0; i < 100000; i++) {
        arr[i] = rand() % 100000;
    }

    timer.measureSorting(arr);

    // Generate new random array
    for (int i = 0; i < 100000; i++) {
        arr[i] = rand() % 100000;
    }

    timer.measureSorting(arr);

    return 0;
}
