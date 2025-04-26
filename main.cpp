#include "Task.h"
#include "iface.h"
#include "TaskList.h"

int main() {

    /*what's new:
     * similar code has been recycled, a new counter has appeared in the home screen, const references have
     * been adjusted and unit testing environment has been prepped */

    try {
        TaskList todo("taskList.txt");
        iface::handleUserChoice(todo);
        return 0;

    } catch (const runtime_error& e) {
        cout << "Fatal failure: " << e.what() << endl;
        return 1;
    }
}
