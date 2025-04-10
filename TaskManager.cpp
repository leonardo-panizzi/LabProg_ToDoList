//
// Created by leona on 20/03/2025.
//

#include "TaskManager.h"
void TaskManager::saveToFile(const list<Task>& todo, const string& filename) {
    ofstream file(filename);
    if (!file) {
        throw runtime_error("Error opening file for writing!");
    }

    for (const auto& task : todo) { //inserts a task's data in order to save it in a specific way
        file << task.getName() << ";"
             << task.getDescription() << ";"
             << (task.isUrgent() ? "1" : "0") << ";"
             << (task.isCompleted() ? "1" : "0") << "\n";
    } //the syntax is the following: |Name;Description;Urgent;Completed|
    file.close();
}

void TaskManager::loadFromFile(list<Task>& todo, const string& filename) { //loads the saved tasks from file
    ifstream file(filename);
    if (!file) {
        throw runtime_error("Error opening file for reading!");
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string name, desc, urgent, completed;

        if (getline(iss, name, ';') &&
            getline(iss, desc, ';') &&
            getline(iss, urgent, ';') &&
            getline(iss, completed)) {

            bool isUrgent = (urgent == "1");
            bool isCompleted = (completed == "1");

            Task task(name, desc, isUrgent, isCompleted);

            todo.push_back(task);
        }
    }
    file.close();
}

bool TaskManager::isNameTaken(const list<Task> &todo, string& name) { //implemented in task renaming and creation
    for (auto& task : todo) {
        if (task.getName() == name) {
            return true;
        } //if two tasks with the same name exist, the user is notified and the function returns true
    }
    return false;
}