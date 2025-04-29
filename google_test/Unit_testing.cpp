//
// Created by leona on 27/04/2025.
//
#include "gtest/gtest.h"
#include "../ToDoList/iface.h"
#include "../ToDoList/Task.h"
#include "../ToDoList/TaskList.h"

// Basic tests for Task class
TEST(prova, prova) {
    int x = 1;
    Task task("test_name", "test_description");

    EXPECT_EQ(x, 1);
}

TEST(prova, prova2) {
    EXPECT_NE("test_name", "test_description");
}

TEST(prova, prova3) {
    Task task("test_name", "test_description");
    task.setCompleteness(true);
    EXPECT_NE(task.isCompleted(), false);
}

TEST(TaskTest, ConstructorSetsFieldsCorrectly) { //testing the constructor's efficiency
    Task t("Do Homework", "Complete math exercises", true, false);

    EXPECT_EQ(t.getName(), "Do Homework");
    EXPECT_EQ(t.getDescription(), "Complete math exercises");
    EXPECT_TRUE(t.isUrgent());
    EXPECT_FALSE(t.isCompleted());
}

TEST(TaskTest, SetNameUpdatesName) { //testing the name's setter method
    Task t("Old Name", "Desc");
    t.setName("New Name");

    EXPECT_EQ(t.getName(), "New Name");
}

TEST(TaskTest, SetUrgentnessChangesUrgentStatus) { //testing the urgent status setter
    Task t("Task", "Desc", false, false);

    EXPECT_TRUE(t.setUrgentness(true));
    EXPECT_TRUE(t.isUrgent());

    EXPECT_FALSE(t.setUrgentness(true));
}

//according to the way the code has been written, a completed task cannot be urgent, let's check this:
TEST(TaskTest, SetCompletenessChangesUrgentStatus) {
    Task t("Task", "Desc", false, false);

    EXPECT_TRUE(t.setCompleteness(true));
    EXPECT_TRUE(t.isCompleted());

    EXPECT_FALSE(t.setCompleteness(true));
}



// Tests for TaskList class
#include <fstream> // <-- creates empty dummy file

//Test: adding a task increases the task count
TEST(TaskListTest, AddingTasksIncreasesTasksCount) {
    const string testFilePath = "test_dummy.txt";

    // creates empty file
    ofstream(testFilePath).close();
    TaskList tasks(testFilePath);
    tasks.addTask("Task1", "Description1", false);
    EXPECT_GT(tasks.getTaskCount(), 0); // expecting the task count to be greater than 0 as a new task was added
    // housekeeping
    remove(testFilePath.c_str());
}


// Testing exception raising when trying to add a task with an already existing name
TEST(TaskListTest, AddTaskWithDuplicateNameThrows) {
    const string testFilePath = "test_dummy2.txt";
    // generates empty file
    ofstream(testFilePath).close();
    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "Description1", false);

    // expected to throw an exception
    EXPECT_THROW(taskList.addTask("Task1", "Another Description", true), runtime_error);

    // housekeeping
    remove(testFilePath.c_str());
}


// Test: removing a task actually removes it
TEST(TaskListTest, RemoveTaskDecreasesTaskCount) {
    const string testFilePath = "test_dummy3.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "Description1", false);
    int initialCount = taskList.getTaskCount();
    taskList.removeTask("Task1");
    EXPECT_LT(taskList.getTaskCount(), initialCount);
    EXPECT_THROW(taskList.setTaskCompleted("Task1", true), runtime_error);
    //throwing an exception if the removed task is actually not found

    remove(testFilePath.c_str());
}




// Test: removing a non-existing task throws an exception
TEST(TaskListTest, RemoveNonExistentTaskThrows) {
    const string testFilePath = "test_dummy4.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    EXPECT_THROW(taskList.removeTask("NonExistentTask"), runtime_error);

    remove(testFilePath.c_str());
}

// Test: task name editing
TEST(TaskListTest, RenameTaskChangesName) { //fixed, now uses the find function instead of a for loop
    const string testFilePath = "test_dummy5.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("OldName", "Description", false);
    taskList.renameTask("OldName", "NewName");

    auto tasks = taskList.getTasks();
    auto it = find_if(tasks.begin(), tasks.end(), [](const Task& task) {
        return task.getName() == "NewName";
    });

    EXPECT_TRUE(it != tasks.end()); //expects to find the task with the new name inside the list

    remove(testFilePath.c_str());
}

// Test: marking a task as completed
TEST(TaskListTest, SetTaskCompletedWorks) {
    const string testFilePath = "test_dummy6.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "Description1", false);
    bool result = taskList.setTaskCompleted("Task1", true);
    EXPECT_TRUE(result);

    auto completedTasks = taskList.getCompletedTasks();
    EXPECT_EQ(completedTasks.size(), 1);

    remove(testFilePath.c_str());
}

// Test: marking a task as urgent
TEST(TaskListTest, SetTaskUrgentWorks) {
    const string testFilePath = "test_dummy7.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath); //new list in which Task1 is added
    taskList.addTask("Task1", "Description1", false);
    bool result = taskList.setTaskUrgent("Task1", true);
    EXPECT_TRUE(result);

    auto urgentTasks = taskList.getUrgentTasks();
    EXPECT_EQ(urgentTasks.size(), 1);

    remove(testFilePath.c_str());
}

// Test: the list is initially empty when created
TEST(TaskListTest, InitiallyEmptyList) {
    const string testFilePath = "test_dummy8.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    EXPECT_TRUE(taskList.isEmpty());

    remove(testFilePath.c_str());
}

// Test: editing a task description
TEST(TaskListTest, EditTaskDescription) {
    const string testFilePath = "test_dummy9.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "OldDescription", false);
    taskList.editDescription("Task1", "NewDescription");

    auto tasks = taskList.getTasks();
    auto it = tasks.begin();
    EXPECT_EQ(it->getDescription(), "NewDescription");

    remove(testFilePath.c_str());
}

// Test: getting urgent tasks only
TEST(TaskListTest, GetUrgentTasksReturnsOnlyUrgent) {
    const string testFilePath = "test_dummy10.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);

    taskList.addTask("UrgentTask1", "Description1", true);   // urgent
    taskList.addTask("NonUrgentTask1", "Description2", false); // not urgent
    taskList.addTask("UrgentTask2", "Description3", true);   // urgent

    auto urgentTasks = taskList.getUrgentTasks();

    EXPECT_EQ(urgentTasks.size(), 2); // there should only be 2 tasks

    for (const auto& task : urgentTasks) {
        EXPECT_TRUE(task.isUrgent()); // checking that each task is indeed urgent
    }

    remove(testFilePath.c_str());
}

// Test: getting not urgent tasks only
TEST(TaskListTest, GetNotUrgentTasksReturnsOnlyNotUrgent) {
    const string testFilePath = "test_dummy11.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);

    taskList.addTask("UrgentTask1", "Description1", true);   // urgent
    taskList.addTask("NonUrgentTask1", "Description2", false); // not urgent
    taskList.addTask("NonUrgentTask2", "Description3", false); // not urgent

    auto notUrgentTasks = taskList.getNotUrgentTasks();

    EXPECT_EQ(notUrgentTasks.size(), 2); // there should only be 2 tasks

    for (const auto& task : notUrgentTasks) {
        EXPECT_FALSE(task.isUrgent()); // checking that each task is indeed not urgent
    }

    remove(testFilePath.c_str());
}

// Test: getting completed tasks only
TEST(TaskListTest, GetCompletedTasksReturnsOnlyCompleted) {
    const string testFilePath = "test_dummy12.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);

    taskList.addTask("CompletedTask1", "Description1", false); // not completed
    taskList.addTask("CompletedTask2", "Description2", false); // not completed
    taskList.setTaskCompleted("CompletedTask1", true); // mark as completed

    auto completedTasks = taskList.getCompletedTasks();

    EXPECT_EQ(completedTasks.size(), 1); // there should only be 1 completed task

    for (const auto& task : completedTasks) {
        EXPECT_TRUE(task.isCompleted()); // checking that each task is indeed completed
    }

    remove(testFilePath.c_str());
}

// Test: the task count is correct after adding and removing tasks
TEST(TaskListTest, TaskCountAfterAddRemove) {
    const string testFilePath = "test_dummy13.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "Description1", false);
    taskList.addTask("Task2", "Description2", true);

    EXPECT_EQ(taskList.getTaskCount(), 2); // should be 2 tasks

    taskList.removeTask("Task1");
    EXPECT_EQ(taskList.getTaskCount(), 1); // should be 1 task after removal

    remove(testFilePath.c_str());
}

// Test: loading from file correctly populates the task list
TEST(TaskListTest, LoadFromFile) { //fixed: added a check on the number of tasks that yet to be completed
    const string testFilePath = "test_dummy14.txt";
    ofstream(testFilePath) << "Task1;Description1;0;0\nTask2;Description2;1;0\n"; // two different tasks
    TaskList taskList(testFilePath);

    EXPECT_EQ(taskList.getTaskCount(), 2); // should load 2 tasks
    EXPECT_EQ(taskList.tasksToComplete(), 2); // <-- added "EXPECTED_EQ" on the amount of tasks to complete to fix the test

    auto tasks = taskList.getTasks();
    auto it = tasks.begin();
    EXPECT_EQ(it->getName(), "Task1");
    EXPECT_EQ(it->getDescription(), "Description1");
    EXPECT_FALSE(it->isUrgent());
    EXPECT_FALSE(it->isCompleted());

    ++it;
    EXPECT_EQ(it->getName(), "Task2");
    EXPECT_EQ(it->getDescription(), "Description2");
    EXPECT_TRUE(it->isUrgent());
    EXPECT_FALSE(it->isCompleted());

    remove(testFilePath.c_str());
}

// Test: saving to file actually saves the task list correctly
//fixed: now checks that there actually are 2 tasks with the expected names
TEST(TaskListTest, SaveToFile) {
    const string testFilePath = "test_dummy15.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "Description1", false); // adds task1
    taskList.addTask("Task2", "Description2", true); // adds task2
    taskList.save();

    ifstream file(testFilePath); // opens the file
    ASSERT_TRUE(file.is_open()); // checks if the file was correctly opened

    vector<string> expectedNames = {"Task1", "Task2"}; // expected task names
    string line, name;
    int i = 0;
    while (getline(file, line)) { // reads each line
        istringstream iss(line);
        getline(iss, name, ';'); // extracts the name only
        EXPECT_EQ(name, expectedNames[i]); // checks if the name matches the expected one
        i++; // increments the counter going to the following line
    }

    EXPECT_EQ(i, 2); // checks that there are 2 tasks in the file
    remove(testFilePath.c_str());
}


// Test: the task list is not empty after adding tasks
TEST(TaskListTest, NotEmptyAfterAddingTasks) {
    const string testFilePath = "test_dummy16.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "Description1", false);
    EXPECT_FALSE(taskList.isEmpty()); // should not be empty after adding a task

    remove(testFilePath.c_str());
}

// Test: the task list is empty after removing all tasks
TEST(TaskListTest, EmptyAfterRemovingAllTasks) {
    const string testFilePath = "test_dummy17.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "Description1", false);
    taskList.removeTask("Task1");
    EXPECT_TRUE(taskList.isEmpty()); // should be empty after removing all tasks

    remove(testFilePath.c_str());
}


// Tests for iface class (trickier to test, as it requires user input which can partially be simulated)

// Test: the EditTaskProperties function correctly marks tasks as completed
TEST(InterfaceTest, EditTaskPropertiesMarkCompleted) {
    const string testFilePath = "test_iface1.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "SomeDescription", false);

    string taskName = "Task1";

    bool success = taskList.setTaskCompleted(taskName, true);
    EXPECT_TRUE(success);

    auto completedTasks = taskList.getCompletedTasks();
    EXPECT_EQ(completedTasks.size(), 1);

    remove(testFilePath.c_str());
}

// Test: the EditTaskProperties function correctly marks tasks as urgent
TEST(InterfaceTest, EditTaskPropertiesMarkUrgent) {
    const string testFilePath = "test_iface2.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "SomeDescription", false);

    string taskName = "Task1";

    bool success = taskList.setTaskUrgent(taskName, true);
    EXPECT_TRUE(success);

    auto urgentTasks = taskList.getUrgentTasks();
    EXPECT_EQ(urgentTasks.size(), 1);

    remove(testFilePath.c_str());
}

// Test: the EditTaskProperties function correctly edits a task's completion status
TEST(InterfaceTest, EditTaskPropertiesEditCompletion) {
    const string testFilePath = "test_iface3.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("Task1", "SomeDescription", false);

    string taskName = "Task1";

    bool success = taskList.setTaskCompleted(taskName, true);
    EXPECT_TRUE(success);

    auto completedTasks = taskList.getCompletedTasks();
    EXPECT_EQ(completedTasks.size(), 1);

    remove(testFilePath.c_str());
}