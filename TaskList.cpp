//
// Created by leona on 05/04/2025.
//

#include <fstream>
#include <sstream>
#include "TaskList.h"

void TaskList::loadFromFile() { //loads the saved tasks from file
    ifstream file(filePath);
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

            tasks.push_back(task);
        }
    }
    file.close();
}

void TaskList::save() {
    ofstream file(filePath);
    if (!file) {
        throw runtime_error("Error opening file for writing!");
    }

    for (const auto& task : tasks) { //inserts a task's data in order to save it in a specific way
        file << task.getName() << ";"
             << task.getDescription() << ";"
             << (task.isUrgent() ? "1" : "0") << ";"
             << (task.isCompleted() ? "1" : "0") << "\n";
    } //the syntax is the following: |Name;Description;Urgent;Completed|
    file.close();
}

bool TaskList::isNameTaken(const std::string& name) {
    for(auto& task : tasks) {
        if (task.getName() == name) {
            return true; //if the name's already taken
        }
    }
    return false;
}

list<Task> TaskList::getUrgentTasks() const {
    list<Task> urgentTasks;
    for(auto task : tasks) {
        if (task.isUrgent()) {
            urgentTasks.push_back(task);
        }
    }
    return urgentTasks;
}

list<Task> TaskList::getNotUrgentTasks() const {
    list<Task> nonUrgentTasks;
    for(auto task : tasks) {
        if (!task.isUrgent() && !task.isCompleted()) { //only non-urgent and uncompleted tasks
            nonUrgentTasks.push_back(task);
        }
    }
    return nonUrgentTasks;
}

list<Task> TaskList::getCompletedTasks() const {
    list<Task> completedTasks;
    for(auto task : tasks) {
        if (task.isCompleted()) {
            completedTasks.push_back(task);
        }
    }
    return completedTasks;
}

