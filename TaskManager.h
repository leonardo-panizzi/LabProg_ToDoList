//
// Created by leona on 20/03/2025.
//

#ifndef PROGTODO_TASKMANAGER_H
#define PROGTODO_TASKMANAGER_H
#include "Task.h"
#include <list>
#include <fstream>
#include <sstream>

class TaskManager {
/*TODO: delete class and implement methods inside of a dedicated "taskList" class featuring name, todo task no,
 * tasks amount, add, edit and delete tasks + tasks research.
 * All the lists must be managed into a "TaskList/taskManager" class that manages all lists*/
public:
    static void saveToFile(const list<Task>& todo, const string& filename); //method that permanently saves/updates tasks to a file
    static void loadFromFile(list<Task>& todo, const string& filename); //loads tasks from file as the program is run
    static bool isNameTaken(const list<Task>& todo, string& name); /*checks for names collision in the list
 * (useful in order to avoid renaming a task as an already existing one or creating two tasks with the same name) */
};


#endif //PROGTODO_TASKMANAGER_H
