#include "Task.h"
#include "iface.h"
#include "TaskList.h"

int main() {

    /*what's new:
     * all functions from virtual class "TaskManager" were replaced using a namespace instead
     * a TaskList class was added for better list management
     * a new "pending tasks" counter was added to constantly show what's left to do*/

    try {
        TaskList todo("taskList.txt");
        iface::handleUserChoice(todo);
        return 0;

    } catch (const runtime_error& e) {
        cout << "Fatal failure: " << e.what() << endl;
        return 1;
    }
}
