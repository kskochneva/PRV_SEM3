#include <iostream>
#include <vector>
#include <string>

class VirtualThread {
private:
    std::vector<std::string> tasks;
    int currentIndex;
    bool taskStarted;

public:
    VirtualThread(const std::vector<std::string>& taskList)
        : tasks(taskList), currentIndex(0), taskStarted(false) {}

    bool hasTasks() {
        return currentIndex < tasks.size();
    }

    void runNextTask(int threadId) {
        if (hasTasks()) {
            std::cout << "Virtual Thread " << threadId << " started task "
                      << tasks[currentIndex] << std::endl;

            // Simulate work
            std::cout << "Virtual Thread " << threadId << " finished task "
                      << tasks[currentIndex] << std::endl;

            currentIndex++;
        }
    }
};

class HyperThreadingSimulator {
private:
    VirtualThread thread1;
    VirtualThread thread2;

public:
    HyperThreadingSimulator(const std::vector<std::string>& t1, const std::vector<std::string>& t2)
        : thread1(t1), thread2(t2) {}

    void execute() {
        while (thread1.hasTasks() || thread2.hasTasks()) {
            if (thread1.hasTasks()) thread1.runNextTask(1);
            if (thread2.hasTasks()) thread2.runNextTask(2);
        }
    }
};

int main() {
    std::vector<std::string> tasks1 = {"Task A", "Task C"};
    std::vector<std::string> tasks2 = {"Task B", "Task D"};

    HyperThreadingSimulator simulator(tasks1, tasks2);
    simulator.execute();

    return 0;
}
