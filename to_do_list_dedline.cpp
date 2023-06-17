/*	to_do_list_dedline.cpp	*/
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

struct Task {
    std::string description;
    std::chrono::system_clock::time_point deadline;
    bool completed;
};

void createTask(std::vector<Task>& tasks, const std::string& description, const std::chrono::system_clock::time_point& deadline) {
    Task newTask;
    newTask.description = description;
    newTask.deadline = deadline;
    newTask.completed = false;
    tasks.push_back(newTask);
    std::cout << "Task created successfully!\n";
}

void deleteTask(std::vector<Task>& tasks, int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
        std::cout << "Task deleted successfully!\n";
    } else {
        std::cout << "Invalid task index!\n";
    }
}

void changeTask(std::vector<Task>& tasks, int index, const std::string& newDescription, const std::chrono::system_clock::time_point& newDeadline) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index].description = newDescription;
        tasks[index].deadline = newDeadline;
        std::cout << "Task changed successfully!\n";
    } else {
        std::cout << "Invalid task index!\n";
    }
}

void markTaskAsCompleted(std::vector<Task>& tasks, int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks[index].completed = true;
        std::cout << "Task marked as completed!\n";
    } else {
        std::cout << "Invalid task index!\n";
    }
}

void displayTaskList(const std::vector<Task>& tasks) {
    int completedCount = 0;
    int uncompletedCount = 0;
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << "[" << i << "] ";
        if (tasks[i].completed) {
            std::cout << "[completed] ";
            ++completedCount;
        } else {
            ++uncompletedCount;
        }
        std::cout << tasks[i].description;

        std::chrono::duration<double> remainingTime = tasks[i].deadline - now;
        if (remainingTime.count() < 86400 && !tasks[i].completed) { // Within a day and not completed
            std::cout << " [Due Soon!]";
        }
        if (remainingTime.count() < 3600 && !tasks[i].completed) { // Within an hour and not completed
            std::cout << " [Due Now!]";
        }

        std::cout << std::endl;
    }

    std::cout << "Total tasks: " << tasks.size() << std::endl;
    std::cout << "Completed tasks: " << completedCount << std::endl;
    std::cout << "Uncompleted tasks: " << uncompletedCount << std::endl;
}

int main() {
    std::vector<Task> tasks;

    while (true) {
        std::cout << "\n==== Task Manager ====\n";
        std::cout << "1. Create task\n";
        std::cout << "2. Delete task\n";
        std::cout << "3. Change task\n";
        std::cout << "4. Mark task as completed\n";
        std::cout << "5. Display task list\n";
        std::cout << "6. Exit\n";
        std::cout << "======================\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cout << "Enter task description: ";
                std::string description;
                std::cin.ignore();
                std::getline(std::cin, description);

                std::cout << "Enter task deadline (YYYY-MM-DD HH:MM): ";
                std::string deadlineStr;
                std::getline(std::cin, deadlineStr);

                std::tm tm = {};
                strptime(deadlineStr.c_str(), "%Y-%m-%d %H:%M", &tm);
                std::time_t deadlineTime = std::mktime(&tm);
                std::chrono::system_clock::time_point deadline = std::chrono::system_clock::from_time_t(deadlineTime);

                createTask(tasks, description, deadline);
                break;
            }
            case 2: {
                std::cout << "Enter task index to delete: ";
                int index;
                std::cin >> index;
                deleteTask(tasks, index);
                break;
            }
            case 3: {
                std::cout << "Enter task index to change: ";
                int index;
                std::cin >> index;

                std::cout << "Enter new task description: ";
                std::string newDescription;
                std::cin.ignore();
                std::getline(std::cin, newDescription);

                std::cout << "Enter new task deadline (YYYY-MM-DD HH:MM): ";
                std::string newDeadlineStr;
                std::getline(std::cin, newDeadlineStr);

                std::tm tm = {};
                strptime(newDeadlineStr.c_str(), "%Y-%m-%d %H:%M", &tm);
                std::time_t newDeadlineTime = std::mktime(&tm);
                std::chrono::system_clock::time_point newDeadline = std::chrono::system_clock::from_time_t(newDeadlineTime);

                changeTask(tasks, index, newDescription, newDeadline);
                break;
            }
            case 4: {
                std::cout << "Enter task index to mark as completed: ";
                int index;
                std::cin >> index;
                markTaskAsCompleted(tasks, index);
                break;
            }
            case 5: {
                displayTaskList(tasks);
                break;
            }
            case 6: {
                std::cout << "Exiting program...\n";
                return 0;
            }
            default:
                std::cout << "Invalid choice! Try again.\n";
                break;
        }
    }
}

