//
// Created by leona on 05/04/2025.
//

#ifndef PROGTODO_TASKLIST_H
#define PROGTODO_TASKLIST_H

#include <iostream>
#include <list>

#include "Task.h"
using namespace std;

class TaskList {
public:
    TaskList(const string &filePath) : filePath(filePath) {
        loadFromFile();
    }
    TaskList() = default;

    void save();

    bool isNameTaken(const string& name);

    int tasksToComplete() { //counter for uncompleted tasks
        int count = 0;

        for(auto task : tasks) {
            if (!task.isCompleted()) {
                count++;
            }
        }

        return count;
    }

    void addTask(const string &name, const string &description, bool urgent) { //adds a task to the list
        if (isNameTaken(name)) { //checks for name collisions
            throw runtime_error("Name is already taken");
        }

        auto newTask = Task(name, description, urgent, false);
        tasks.push_back(newTask);
    }

    void removeTask(const string &name) { //removes a task from the list
        bool found = false;

        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->getName() == name) {
                tasks.erase(it);
                found = true;
                break;
            }
        }

        if (!found) {
            throw runtime_error("Task not found");
        }
    }

    void markTaskAsCompleted(const string &name) {
        auto task = findTask(name);
        task.setCompleted();
        task.setNotUrgent();
    }

    void markTaskAsNotCompleted(const string &name) {
        auto task = findTask(name);
        task.setNotCompleted();
    }

    void markTaskAsUrgent(const string &name) {
        auto task = findTask(name);
        task.setUrgent();
    }

    void markTaskAsNotUrgent(const string &name) {
        auto task = findTask(name);
        task.setNotUrgent();
    }

    void renameTask(const string &oldName, const string &newName) {
        auto task = findTask(oldName);
        if (isNameTaken(newName)) {
            throw runtime_error("Name is already taken");
        }
        task.setName(newName);
    }

    void editDescription(const string &name, const string &newDescription) {
        auto task = findTask(name);
        task.setDescription(newDescription);
    }

    void loadFromFile(); //loads the tasks saved in the file

    list<Task> getTasks() const {
        return tasks;
    }

    bool isEmpty() const {
        return tasks.size() == 0;
    }

    list<Task> getUrgentTasks() const;
    list<Task> getNotUrgentTasks() const;
    list<Task> getCompletedTasks() const;

private:
    const string filePath;
    string listName;
    list<Task> tasks;

    Task& findTask(const string &name) {
        for (auto &task : tasks) {
            if (task.getName() == name) {
                return task;
            }
        }
        throw runtime_error("Task not found");
    }
};


#endif //PROGTODO_TASKLIST_H
