//
// Created by leona on 05/04/2025.
//

#ifndef PROGTODO_IFACE_H
#define PROGTODO_IFACE_H

#include "Task.h"
#include "TaskList.h"
#include <list>

namespace iface {
    void showMenu(TaskList &todoList); //method that displays a menu from which the user can perform an action
    void handleUserChoice(TaskList &todoList); //function that checks what the user chose and acts consequently on the list

    // taskname can't be set as const as it might be updated in case a modification occurs
    void editTaskProperties(string &taskName, TaskList &todoList); //specific method used to perform an edit on a task
}

#endif //PROGTODO_IFACE_H
