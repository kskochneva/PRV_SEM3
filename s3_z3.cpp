#include <iostream>
#include <chrono>

int main() {
    // Get total seconds from user
    long long total_seconds;
    std::cout << "Enter the number of seconds: ";
    std::cin >> total_seconds;

    // Create duration object
    std::chrono::seconds total_sec(total_seconds);

    // Convert to hours
    auto hours = std::chrono::duration_cast<std::chrono::hours>(total_sec);

    // Subtract hours to get remaining time
    auto remaining_after_hours = total_sec - hours;

    // Convert remaining to minutes
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(remaining_after_hours);

    // Subtract minutes to get remaining seconds
    auto seconds = remaining_after_hours - minutes;

    // Output result
    std::cout << hours.count() << " hour(s) "
              << minutes.count() << " minute(s) "
              << seconds.count() << " second(s)" << std::endl;

    return 0;
}
