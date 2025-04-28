//
// Created by leona on 27/04/2025.
//
#include "gtest/gtest.h"
#include "../ToDoList/iface.h"
#include "../ToDoList/Task.h"

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



