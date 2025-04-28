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

TEST(TaskTest, SetCompletenessChangesUrgentStatus) { //according to the way the code has been written, a completed task cannot be urgent, let's check this:
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
TEST(TaskListTest, RenameTaskChangesName) {
    const string testFilePath = "test_dummy5.txt";
    ofstream(testFilePath).close();

    TaskList taskList(testFilePath);
    taskList.addTask("OldName", "Description", false);
    taskList.renameTask("OldName", "NewName");

    auto tasks = taskList.getTasks();
    bool foundNewName = false;
    for (const auto& task : tasks) {
        if (task.getName() == "NewName") {
            foundNewName = true;
            break;
        }
    }
    EXPECT_TRUE(foundNewName);

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

