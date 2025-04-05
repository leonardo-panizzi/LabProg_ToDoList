//
// Created by leona on 05/04/2025.
//

#ifndef PROGTODO_IFACE_H
#define PROGTODO_IFACE_H

#include "Task.h"
#include <list>

namespace iface {
    void showMenu(); //method that displays a menu from which the user can perform an action
    void handleUserChoice(list<Task>& todo); //function that checks what the user chose and acts consequently on the list
    void editTaskProperties(Task& task, list<Task>& todo); //specific method which is used to perform an edit on a task
}

#endif //PROGTODO_IFACE_H
