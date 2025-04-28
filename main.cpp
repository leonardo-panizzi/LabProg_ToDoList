#include "Task.h"
#include "iface.h"
#include "TaskList.h"

int main() {

    /*what's new:
     * similar code has been recycled, a new counter has appeared in the home screen (for both completed
     * and pending tasks), const references have been adjusted where they needed to
     * and unit testing has been executed */

    try {
        TaskList todo("/home/master/ProgToDo/taskList.txt");
        iface::handleUserChoice(todo);
        return 0;

    } catch (const runtime_error& e) {
        cout << "Fatal failure: " << e.what() << endl;
        return 1;
    }
}
