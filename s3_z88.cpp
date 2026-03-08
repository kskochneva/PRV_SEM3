#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

struct Task {
    int value;
    int priority;
    int duration_ms;
    int steps;
    int currentStep;

    Task(int v, int p, int d, int s)
        : value(v), priority(p), duration_ms(d), steps(s), currentStep(0) {}

    bool isCompleted() const {
        return currentStep >= steps;
    }

    int getResult() const {
        return value * value;
    }
};

class VirtualThread {
private:
    std::vector<Task> tasks;

public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    bool hasTasks() const {
        return !tasks.empty();
    }

    // Get task with highest priority
    Task* getHighestPriorityTask() {
        if (tasks.empty()) return nullptr;

        auto highest = std::max_element(tasks.begin(), tasks.end(),
            [](const Task& a, const Task& b) {
                return a.priority < b.priority;
            });

        return &(*highest);
    }

    void runStep(int threadId) {
        Task* task = getHighestPriorityTask();
        if (!task) return;

        task->currentStep++;

        std::cout << "Virtual Thread " << threadId
                  << " executes step " << task->currentStep << "/" << task->steps
                  << " of task " << task->value
                  << " (priority: " << task->priority << ")" << std::endl;

        // Simulate step execution time
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        if (task->isCompleted()) {
            std::cout << "Virtual Thread " << threadId
                      << " completed task " << task->value
                      << ": result = " << task->getResult() << std::endl;

            // Remove completed task
            tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                [task](const Task& t) { return &t == task; }), tasks.end());
        }
    }
};

class HyperThreadingSimulator {
private:
    VirtualThread thread1;
    VirtualThread thread2;

public:
    HyperThreadingSimulator(int tasksPerThread) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> valueDist(1, 50);
        std::uniform_int_distribution<int> priorityDist(1, 10);
        std::uniform_int_distribution<int> durationDist(200, 1000);
        std::uniform_int_distribution<int> stepsDist(2, 5);

        for (int i = 0; i < tasksPerThread; i++) {
            thread1.addTask(Task(
                valueDist(gen),
                priorityDist(gen),
                durationDist(gen),
                stepsDist(gen)
            ));

            thread2.addTask(Task(
                valueDist(gen),
                priorityDist(gen),
                durationDist(gen),
                stepsDist(gen)
            ));
        }
    }

    void execute() {
        while (thread1.hasTasks() || thread2.hasTasks()) {
            if (thread1.hasTasks()) thread1.runStep(1);
            if (thread2.hasTasks()) thread2.runStep(2);
        }
    }
};

int main() {
    HyperThreadingSimulator simulator(2); // 2 tasks per thread
    simulator.execute();

    return 0;
}
