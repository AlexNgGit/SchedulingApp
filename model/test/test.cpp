#include <catch2/catch_test_macros.hpp>
using namespace std;
#include "../src/Project.h"

bool checkInclude (vector<shared_ptr<Task> > expected, vector<shared_ptr<Task> > ret) {
    bool isInclude = true;
    for (auto element: expected) {
        bool curr = false;
        for (auto sub: ret) {
            if (sub == element) {
                curr = true;
            }
        }
        isInclude = curr && isInclude;
    }
    return isInclude;
}

bool checkInnerTask(shared_ptr<Task> expected, shared_ptr<Task> actual) {
    return expected->getDuration() == actual->getDuration() &&
    expected->getName() == actual->getName() &&
            checkInclude(expected->getDependencies(), actual->getDependencies())
    ;
}


SCENARIO("Test1: excel file has one (1) sheet, no start or end keywords are specified, all rows have values") {
    GIVEN("initialization: read from existed \"./testXLSX/Test1\" ") {
        const string pathName = "/Users/datnguyen/Desktop/SchedulingApp/testXLSX/Test1.xlsx";

        Project newProject = Project();

        vector<shared_ptr<Task> > taskList;

        shared_ptr<Task> taskA(new Task(5, 5, "A", vector<shared_ptr<Task>>()));
        shared_ptr<Task> taskB(new Task(10, 10, "B", vector<shared_ptr<Task>>({
                                                                                      taskA
                                                                              })));
        shared_ptr<Task> taskC(new Task(8, 8, "C", vector<shared_ptr<Task>>({
                                                                                    taskA})));
        shared_ptr<Task> taskD(new Task(6, 6, "D", vector<shared_ptr<Task>>({
                                                                                    taskB})));
        shared_ptr<Task> taskE(new Task(7, 7, "E", vector<shared_ptr<Task>>({
                                                                                    taskC})));
        shared_ptr<Task> taskF(new Task(4, 4, "F", vector<shared_ptr<Task>>({
                                                                                    taskC})));
        shared_ptr<Task> taskG(new Task(4, 4, "G", vector<shared_ptr<Task>>({
                                                                                    taskE, taskF, taskD})));

        taskList.insert(taskList.end(), {taskA, taskB, taskC, taskD, taskE, taskF, taskG});

        WHEN("load an existing excel files with valid format") {
            try {
                auto ret = newProject.addTasks(pathName);
                REQUIRE(ret.get());
                THEN("CHECK INTERNAL TASKS") {
                    /*for (auto element: newProject.getInput()) {
                        bool ret = false;
                        for (auto subElement: taskList) {
                            if (checkInnerTask(subElement, element)) {
                                ret = true;
                                continue;
                            }
                        }
                        REQUIRE(ret);
                    }*/
                }
            } catch (const exception& e) {
                FAIL("SHOULD NOT THROW ANY ERRORS HERE");
            }
        }

    }
}

/*SCENARIO("Test2: excel file has one (1) sheet, Start and End keywords are specified, all rows have valid values") {
    GIVEN("initialization: read from existed \"./testXLSX/Test2\" ") {
        const string pathName = "../../testXLSX/Test2.xlsx";

        Project newProject = Project();

        vector<shared_ptr<Task> > taskList;

        shared_ptr<Task> taskA(new Task(5, 5, "A", vector<shared_ptr<Task>>()));
        shared_ptr<Task> taskB(new Task(10, 10, "B", vector<shared_ptr<Task>>({
                                                                                      taskA
                                                                              })));
        shared_ptr<Task> taskC(new Task(8, 8, "C", vector<shared_ptr<Task>>({
                                                                                    taskA})));
        shared_ptr<Task> taskD(new Task(6, 6, "D", vector<shared_ptr<Task>>({
                                                                                    taskB})));
        shared_ptr<Task> taskE(new Task(12, 12, "E", vector<shared_ptr<Task>>({
                                                                                    taskC})));
        shared_ptr<Task> taskF(new Task(10, 10, "F", vector<shared_ptr<Task>>({
                                                                                    taskC})));
        shared_ptr<Task> taskG(new Task(4, 4, "G", vector<shared_ptr<Task>>({
                                                                                    taskE, taskF, taskD})));

        taskList.insert(taskList.end(), {taskA, taskB, taskC, taskD, taskE, taskF, taskG});

        WHEN("load an existing excel files with valid format") {
            try {
                auto ret = newProject.addTasks(pathName);
                REQUIRE(ret.get());
                THEN("CHECK INTERNAL TASKS") {
                    for (auto element: newProject.getInput()) {
                        bool ret = false;
                        for (auto subElement: taskList) {
                            if (checkInnerTask(subElement, element)) {
                                ret = true;
                                continue;
                            }
                        }
                        REQUIRE(ret);
                    }
                }
            } catch (const exception& e) {
                FAIL("SHOULD NOT THROW ANY ERRORS HERE");
            }
        }

    }
}*/
//TODO: need to figure out on how to throws warning.

/*SCENARIO("Test3: excel file has one (1) sheet, Start and End keywords are specified, some rows have missing values") {
    GIVEN("initialization: read from existed \"./testXLSX/Test3\" ") {
        const string pathName = "../../testXLSX/Test3.xlsx";

        Project newProject = Project();

        vector<shared_ptr<Task> > taskList;

        shared_ptr<Task> taskA(new Task(0, 5, "A", vector<shared_ptr<Task>>()));
        shared_ptr<Task> taskB(new Task(10, 10, "B", vector<shared_ptr<Task>>({
                                                                                      taskA
                                                                              })));
        shared_ptr<Task> taskC(new Task(8, 8, "C", vector<shared_ptr<Task>>({
                                                                                    taskA})));
        shared_ptr<Task> taskD(new Task(0, 6, "D", vector<shared_ptr<Task>>({
                                                                                    taskB})));
        shared_ptr<Task> taskE(new Task(12, 12, "E", vector<shared_ptr<Task>>({
                                                                                      taskC})));
        shared_ptr<Task> taskF(new Task(10, 10, "F", vector<shared_ptr<Task>>({
                                                                                      taskC})));
        shared_ptr<Task> taskG(new Task(0, 4, "G", vector<shared_ptr<Task>>({
                                                                                    taskE, taskF, taskD})));

        taskList.insert(taskList.end(), {taskA, taskB, taskC, taskD, taskE, taskF, taskG});

        WHEN("load an existing excel files with valid format") {
            try {
                auto ret = newProject.addTasks(pathName);
                REQUIRE(ret.get());
                THEN("CHECK INTERNAL TASKS") {
                    for (auto element: newProject.getInput()) {
                        bool ret = false;
                        for (auto subElement: taskList) {
                            if (checkInnerTask(subElement, element)) {
                                ret = true;
                                continue;
                            }
                        }
                        REQUIRE(ret);
                    }
                }
            } catch (const exception& e) {
                FAIL("SHOULD NOT THROW ANY ERRORS HERE");
            }
        }

    }
}*/





