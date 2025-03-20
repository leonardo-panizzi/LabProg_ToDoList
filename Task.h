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
    Task(string& n, string& d, bool u = false, bool c = false) : name(n), description(d), urgent(u), completed(c){}


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

    void setUrgent() {
        if (!urgent) {
            urgent = true;
            cout << "Successfully set as urgent" << endl;
        }
        else {
            cout << "Task is already urgent" << endl;
        }
    }

    void setNotUrgent() {
        if (urgent) {
            urgent = false;
            cout << "Successfully set as not urgent" << endl;
        }
        else {
            cout << "Task is already not urgent" << endl;
        }
    }

    bool isCompleted() const {
        return completed;
    }

    void setCompleted() {
        if (!completed) {
            completed = true;
            cout << "Task set as completed" << endl;
        } else {
            cout << "Task is already set as completed" << endl;
        }
    }

    void setNotCompleted() {
        if (completed) {
            completed = false;
            cout << "Task set as not completed" << endl;
        } else {
            cout << "Task was already marked as not completed" << endl;
        }
    }

private:
    string name, description; //name and task description
    bool urgent, completed; //urgent attribute will be useful later to display urgent tasks first
};


#endif //PROGTODO_TASK_H
