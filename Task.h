//
// Created by leona on 20/03/2025.
//

#ifndef PROGTODO_TASK_H
#define PROGTODO_TASK_H
#include <iostream>
#include <utility>
using namespace std;


class Task {
public:
    Task(const string& n, const string& d, bool u = false, bool c = false) : name(n), description(d), urgent(u), completed(c) {}


    //getter and setter methods
    const string& getName() const {
        return name;
    }

    void setName(const string& newName) {
        name = newName;
    }

    const string& getDescription() const {
        return description;
    }

    void setDescription(const string& newDescription) {
        description = newDescription;
    }

    bool isUrgent() const {
        return urgent;
    }

    bool setUrgent() {
        if (!urgent) {
            urgent = true;
            return true;
        }

        return false;
    }

    bool setNotUrgent() {
        if (urgent) {
            urgent = false;
            return true;
        }
        return false;
    }

    bool isCompleted() const {
        return completed;
    }

    bool setCompleted() {
        if (!completed) {
            completed = true;
            return true;
        }
        return false;
    }

    bool setNotCompleted() {
        if (completed) {
            completed = false;
            return true;
        }
        return false;
    }

private:
    string name, description; //name and task description
    bool urgent, completed; //urgent attribute will be useful later to display urgent tasks first
};


#endif //PROGTODO_TASK_H
