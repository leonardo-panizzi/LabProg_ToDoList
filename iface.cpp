//
// Created by leona on 20/03/2025.
//

#include <limits>
#include "iface.h"
#include "TaskList.h"

void iface::showMenu(TaskList &todoList) {
    cout << "\n[HOME]" << endl;
    cout << "Pending tasks: " << todoList.tasksToComplete() << endl; //shows how many tasks are still pending
    cout << "1. Add a task" << endl; //inserts a new task into a list
    cout << "2. Remove a task" << endl;
    cout << "3. Edit a task properties" << endl; //allows to fully edit a task with its properties
    cout << "4. Show all tasks" << endl; //displays all kind of tasks in the list
    cout << "5. Show tasks history" << endl; //only shows what has been flagged as "completed"
    cout << "6. Save and quit" << endl; //saves changes permanently into a file and shuts down the program
}

void iface::handleUserChoice(TaskList &todoList) {
    int choice;
    do {
        showMenu(todoList); //shows the menu
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid number." << endl; //system checks for misinputs, warns if one is found
            continue;
        }
        cin.ignore();

        switch (choice) {
            case 1: {
                string name, description;
                cout << "Insert new task Name: ";
                getline(cin, name); //checks what user types and saves the whole line
                if(!todoList.isNameTaken(name)) { //checks for name collisions
                    cout << "Insert new task Description: "; //if no collisions occur, it lets the user continue
                    getline(cin, description);
                    todoList.addTask(name, description, false); //inserts newly added task into the list
                    cout << "Task added!" << endl;
                }  else {
                    cout << "Task name already taken!" << endl; //if a collision is found, the user is warned
                }
                break;
            }
            case 2: {
                string name; //search by name
                cout << "Insert task name to remove it: ";
                getline(cin, name);
                bool found = false;
                for (const auto& it:todoList.getTasks()) { //checks the whole list
                    if (it.getName() == name) { //if a task has the same name as the targeted one
                        todoList.removeTask(it.getName()); //it's deleted
                        cout << "Task removed." << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Task not found." << endl;
                }
                break;
            }
            case 3: {
                string taskName;
                cout << "Enter task name to edit it: ";
                getline(cin, taskName);
                bool found = false;
                for (auto& task : todoList.getTasks()) { //looks for the task
                    if (task.getName() == taskName) { //if found
                        editTaskProperties(taskName, todoList); //uses an apposite function whose purpose is task editing
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Task not found!" << endl;
                }
                break;
            }
            case 4: {
                cout << "\nAll tasks:" << endl;
                if (todoList.isEmpty()) {
                    cout << "No tasks available." << endl; //if no tasks are saved yet
                    break;
                } else { //3 different cycles
                    cout << "Urgent tasks: " << endl;
                    for (const auto &task: todoList.getUrgentTasks()) { //1st cycle shows "urgent" tasks first
                        cout << "- " << task.getName() << ": " << task.getDescription() << endl;
                    }
                    cout << "Regular tasks: " << endl;
                    for (const auto &task: todoList.getNotUrgentTasks()) { //2nd cycle shows regular tasks
                        cout << "- " << task.getName() << ": " << task.getDescription() << endl;
                    }
                    cout << "Completed tasks: " << endl; //3rd cycle only shows already completed tasks
                    for (const auto &task : todoList.getCompletedTasks()){
                        cout << "[X] " << task.getName() << ": " << task.getDescription() << endl;
                    }
                }
                break;
            }
            case 5: {
                cout << "\nCompleted tasks:" << endl;
                for (const auto& task : todoList.getCompletedTasks()) { //history, hence only completed tasks are shown
                    cout << "[X] " << task.getName() << ": " << task.getDescription() << endl;
                }
                break;
            }
            case 6: {
                try {
                    todoList.save(); //saves the list into a file
                } catch (const runtime_error& e) {
                    cout << "Fatal failure: " << e.what() << endl;
                    return;
                }
                cout << "Tasks saved successfully. Exiting..." << endl;
                return;
            }

            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
    } while (choice != 6); //the user is shown the menu until he chooses to quit using the corresponding key
}

void iface::editTaskProperties(string& taskName, TaskList &todoList) { //choice switch
    int option;
    do {
        cout << "\nEDIT TASK '" << taskName << "'" << endl;
        cout << "1. Rename task" << endl; //anti-collision mechanism implemented
        cout << "2. Change description" << endl;
        cout << "3. Mark as completed" << endl;
        cout << "4. Mark as ToDo" << endl;
        cout << "5. Mark as urgent" << endl;
        cout << "6. Mark as non urgent" << endl;
        cout << "7. Go back" << endl;
        cout << "Enter your choice: " << endl;
        cin >> option;
        cin.ignore();

        switch (option) {
            case 1: {
                string newName;
                cout << "Insert new name: ";
                getline(cin, newName);
                if (!todoList.isNameTaken(newName)) { //checks to avoid renaming a task as an already existing one
                    todoList.renameTask(taskName, newName);
                    cout << "Task renamed successfully." << endl;
                    taskName = newName; //updates the name of the task
                    break;
                } else {
                    cout << "Task name already taken!" << endl;
                }
                break;
            }
            case 2: {
                string newDesc;
                cout << "New description: ";
                getline(cin, newDesc);
                todoList.editDescription(taskName, newDesc); //uses the method to edit the description
                cout << "Description updated." << endl;
                break;
            }
            case 3: {
                bool success = todoList.markTaskAsCompleted(taskName); //uses the method to set the task as completed
                if (success) {
                    cout << "Task marked as completed." << endl;
                } else {
                    cout << "Task is already completed." << endl;
                }
                break;
            }
            case 4: {
                bool success = todoList.markTaskAsNotCompleted(taskName);
                if (success) {
                    cout << "Task marked as ToDo." << endl;
                } else {
                    cout << "Task is already ToDo." << endl;
                }
                break;
            }
            case 5: {
                bool success = todoList.markTaskAsUrgent(taskName);
                if (success) {
                    cout << "Task set as urgent." << endl;

                } else {
                    cout << "Task is already urgent." << endl;
                }
                break;
            }
            case 6: {
                bool success = todoList.markTaskAsNotUrgent(taskName);
                if (success) {
                    cout << "Task set as not urgent." << endl;
                } else {
                    cout << "Task is already not urgent." << endl;
                }
                break;
            }
            case 7:
                return;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (option != 7); //the "7" key works like a "back" button, taking back the user to the home page
}