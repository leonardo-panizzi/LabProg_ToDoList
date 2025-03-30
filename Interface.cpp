//
// Created by leona on 20/03/2025.
//

#include <limits>
#include "Interface.h"

void Interface::showMenu() {
    cout << "\n[HOME]" << endl;
    cout << "1. Add a task" << endl; //inserts a new task into a list
    cout << "2. Remove a task" << endl;
    cout << "3. Edit a task properties" << endl; //allows to fully edit a task with its properties
    cout << "4. Show all tasks" << endl; //displays all kind of tasks in the list
    cout << "5. Show tasks history" << endl; //only shows what has been flagged as "completed"
    cout << "6. Save and quit" << endl; //saves changes permanently into a file and shuts down the program
}

void Interface::handleUserChoice(list<Task>& todo) {
    int choice;
    do {
        showMenu();
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
                if(!TaskManager::isNameTaken(todo, name)){ //uses function to look for names collision
                    cout << "Insert new task Description: "; //if no collisions occur, it lets the user continue
                    getline(cin, description);
                    todo.emplace_back(Task(name, description)); //inserts newly added task into the list
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
                for (auto it = todo.begin(); it != todo.end(); it++) { //checks the whole list
                    if (it->getName() == name) { //if a task has the same name as the targeted one
                        todo.erase(it); //it's deleted
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
                string name;
                cout << "Enter task name to edit it: ";
                getline(cin, name);
                bool found = false;
                for (auto& task : todo) { //looks for the task
                    if (task.getName() == name) { //if found
                        editTaskProperties(task, todo); //uses an apposite function whose purpose is task editing
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
                if (todo.empty()) {
                    cout << "No tasks available." << endl; //if no tasks are saved yet
                    break;
                } else { //3 different cycles
                    for (const auto &task: todo) { //1st cycle shows "urgent" tasks first
                        if (task.isUrgent() && !task.isCompleted()) {
                            cout << "- " << task.getName() << ": " << task.getDescription() << endl;
                        }
                    }
                    for (const auto &task: todo) { //2nd cycle shows regular tasks
                        if (!task.isUrgent() && !task.isCompleted()) {
                            cout << "- " << task.getName() << ": " << task.getDescription() << endl;
                        }
                    }
                    cout << "Completed tasks: " << endl; //3rd cycle only shows already completed tasks
                    for (const auto &task : todo){
                        if(task.isCompleted()){
                            cout << "[X] " << task.getName() << ": " << task.getDescription() << endl;
                        } //displays task preceded by a "tick"
                    }
                }
                break;
            }
            case 5: {
                cout << "\nCompleted tasks:" << endl;
                for (const auto& task : todo) { //history, hence only completed tasks are shown
                    if(task.isCompleted()) {
                        cout << "[X] " << task.getName() << ": " << task.getDescription() << endl;
                    }
                }
                break;
            }
            case 6: {
                try {
                    TaskManager::saveToFile(todo, "taskList.txt"); //saves the list into a file
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

void Interface::editTaskProperties(Task& task, list<Task>& todo) { //choice switch
    int option;
    do {
        cout << "\nEDIT TASK " << task.getName() << endl;
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
                if (!TaskManager::isNameTaken(todo, newName)) { //checks to avoid renaming a task as an already existing one
                    task.setName(newName);
                    cout << "Task renamed successfully." << endl;
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
                task.setDescription(newDesc);
                cout << "Description updated." << endl;
                break;
            }
            case 3:{
                bool success = task.setCompleted();
                if (success) {
                    cout << "Task marked as completed." << endl;
                } else {
                    cout << "Task is already completed." << endl;
                }
                break;
            }
            case 4: {
                bool success = task.setNotCompleted();
                if (success) {
                    cout << "Task marked as ToDo." << endl;
                } else {
                    cout << "Task is already ToDo." << endl;
                }
                break;
            }
            case 5: {
                bool success = task.setUrgent();
                if (success) {
                    cout << "Task set as urgent." << endl;

                } else {
                    cout << "Task is already urgent." << endl;
                }
                break;
            }
            case 6: {
                bool success = task.setNotUrgent();
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
    } while (option != 7); //"7" key works like a "back" button, taking back the user to the home page
}