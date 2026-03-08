#include <iostream>
#include <vector>

class VirtualThread {
private:
    std::vector<int> numbers;
    int currentIndex;

public:
    VirtualThread(const std::vector<int>& nums) : numbers(nums), currentIndex(0) {}

    bool hasNext() {
        return currentIndex < numbers.size();
    }

    void run(int threadId) {
        if (hasNext()) {
            int n = numbers[currentIndex];
            long long fact = 1;
            for (int i = 1; i <= n; i++) {
                fact *= i;
            }
            std::cout << "Virtual Thread " << threadId << " computes " << n
                      << "! = " << fact << std::endl;
            currentIndex++;
        }
    }
};

class HyperThreadingSimulator {
private:
    VirtualThread thread1;
    VirtualThread thread2;

public:
    HyperThreadingSimulator(const std::vector<int>& nums1, const std::vector<int>& nums2)
        : thread1(nums1), thread2(nums2) {}

    void execute() {
        while (thread1.hasNext() || thread2.hasNext()) {
            if (thread1.hasNext()) thread1.run(1);
            if (thread2.hasNext()) thread2.run(2);
        }
    }
};

int main() {
    std::vector<int> tasks1 = {5, 10};
    std::vector<int> tasks2 = {7, 12};

    HyperThreadingSimulator simulator(tasks1, tasks2);
    simulator.execute();

    return 0;
}
