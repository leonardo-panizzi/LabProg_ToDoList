//
// Created by leona on 20/03/2025.
//

#ifndef PROGTODO_INTERFACE_H
#define PROGTODO_INTERFACE_H
#include <list>
#include "Task.h"
#include "TaskManager.h"
using namespace std;

class Interface {
public:
    static void showMenu(); //method that displays a menu from which the user can perform an action
    static void handleUserChoice(list<Task>& todo); //function that checks what the user chose and acts consequently on the list
    static void editTaskProperties(Task& task, list<Task>& todo); //specific method which is used to perform an edit on a task
};


#endif //PROGTODO_INTERFACE_H
