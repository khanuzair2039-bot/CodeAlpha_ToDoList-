#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Task {
public:
    string description;
    bool completed;

    Task(string desc, bool status = false) {
        description = desc;
        completed = status;
    }
};

vector<Task> tasks;

// Save tasks to file
void saveTasks() {
    ofstream file("tasks.txt");
    for (auto &t : tasks) {
        file << t.description << "|" << t.completed << endl;
    }
    file.close();
}

// Load tasks from file
void loadTasks() {
    ifstream file("tasks.txt");
    string desc;
    bool status;

    while (getline(file, desc, '|') && file >> status) {
        file.ignore();
        tasks.push_back(Task(desc, status));
    }
    file.close();
}

// Add task
void addTask() {
    string desc;
    cin.ignore();
    cout << "Enter task: ";
    getline(cin, desc);
    tasks.push_back(Task(desc));
    cout << "Task Added!\n";
}

// View tasks
void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". " << tasks[i].description;
        cout << (tasks[i].completed ? " [Done]" : " [Pending]") << endl;
    }
}

// Mark complete
void markComplete() {
    int n;
    cout << "Enter task number: ";
    cin >> n;

    if (n > 0 && n <= tasks.size()) {
        tasks[n - 1].completed = true;
        cout << "Marked as completed!\n";
    } else {
        cout << "Invalid task number!\n";
    }
}

// Main menu
int main() {
    loadTasks();
    int choice;

    do {
        cout << "\n--- TO-DO LIST MENU ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Completed\n";
        cout << "4. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: markComplete(); break;
            case 4: saveTasks(); cout << "Saved! Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}