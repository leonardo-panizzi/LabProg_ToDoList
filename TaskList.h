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

    void save();

    int tasksToComplete(); //counter for uncompleted tasks

    void addTask(const string &name, const string &description, bool urgent); //adds a task to the list

    void removeTask(const string &name); //removes a task from the list

    bool setTaskCompleted(const string &name, bool completed); //marks a task as completed

    /*bool markTaskAsCompleted(const string &name);

    bool markTaskAsNotCompleted(const string &name);*/

    bool setTaskUrgent(const string &name, bool urgent); //marks a task as urgent

    /*bool markTaskAsUrgent(const string &name);

    bool markTaskAsNotUrgent(const string &name);*/

    void renameTask(const string &oldName, const string &newName);

    void editDescription(const string &name, const string &newDescription) {
        auto task = findTask(name);
        task->setDescription(newDescription);
    }

    list<Task> getTasks() const {
        return tasks;
    }

    bool isEmpty() const {
        return tasks.size() == 0;
    }

    list<Task> getUrgentTasks() const;
    list<Task> getNotUrgentTasks() const;
    list<Task> getCompletedTasks() const;

    int getTaskCount() const {
        return tasks.size();
    }

private:
    const string filePath;
    string listName;
    list<Task> tasks;

    void loadFromFile(); //loads the tasks saved in the file

    bool isNameTaken(const string& name); //private method to avoid renaming a task as an already existing one

    Task* findTask(const string &name) {
        for (auto &task : tasks) {
            if (task.getName() == name) {
                return &task;
            }
        }
        throw runtime_error("Task not found");
    }
};


#endif //PROGTODO_TASKLIST_H
