#include <iostream>
#include <string>

using namespace std;

struct Task {
    int id;
    string description;
    int priority;
    Task* next;
};

class TaskManager {
private:
    Task* head;

public:
    TaskManager() {
        head = nullptr;
    }

    void addTask(int id, string description, int priority) {
        Task* newTask = new Task();
        newTask->id = id;
        newTask->description = description;
        newTask->priority = priority;
        newTask->next = nullptr;

        if (head == nullptr || head->priority < priority) {
            newTask->next = head;
            head = newTask;
        } else {
            Task* current = head;
            while (current->next != nullptr && current->next->priority >= priority) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }

        cout << "Task added successfully!" << endl;
    }

    void removeHighestPriorityTask() {
        if (head == nullptr) {
            cout << "No tasks to remove." << endl;
            return;
        }

        Task* temp = head;
        head = head->next;
        cout << "Removed task with ID: " << temp->id << endl;
        delete temp;
    }

    void removeTaskById(int id) {
        if (head == nullptr) {
            cout << "No tasks to remove." << endl;
            return;
        }

        if (head->id == id) {
            Task* temp = head;
            head = head->next;
            cout << "Removed task with ID: " << temp->id << endl;
            delete temp;
            return;
        }

        Task* current = head;
        while (current->next != nullptr && current->next->id != id) {
            current = current->next;
        }

        if (current->next == nullptr) {
            cout << "Task with ID " << id << " not found." << endl;
        } else {
            Task* temp = current->next;
            current->next = current->next->next;
            cout << "Removed task with ID: " << temp->id << endl;
            delete temp;
        }
    }

    void viewTasks() {
        if (head == nullptr) {
            cout << "No tasks to display." << endl;
            return;
        }

        Task* current = head;
        while (current != nullptr) {
            cout << "ID: " << current->id << ", Description: " << current->description
                 << ", Priority: " << current->priority << endl;
            current = current->next;
        }
    }

    ~TaskManager() {
        while (head != nullptr) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TaskManager manager;
    int choice;

    do {
        cout << "\nTask Management System\n";
        cout << "1. Add a new task\n";
        cout << "2. View all tasks\n";
        cout << "3. Remove the highest priority task\n";
        cout << "4. Remove a task by ID\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, priority;
                string description;
                cout << "Enter task ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter task description: ";
                getline(cin, description);
                cout << "Enter task priority: ";
                cin >> priority;
                manager.addTask(id, description, priority);
                break;
            }
            case 2:
                manager.viewTasks();
                break;
            case 3:
                manager.removeHighestPriorityTask();
                break;
            case 4: {
                int id;
                cout << "Enter task ID to remove: ";
                cin >> id;
                manager.removeTaskById(id);
                break;
            }
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
