#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <vector>
#include "../controller/Task/Task.h"
#include "../controller/Analysis/Project/Project.h"
/**
 * Using Catch2 testing library, this test file aims to cover the majority of failure as well successful cases for
 * calculating the earliest completed time, critical path as well as the slack cost based on CPM (Critical Path Method,
 * specified in Project file's documentation).
 * These will cover:
 *   1) First user case allows to retract those information with the assumption tasks are given with the duration
 *   and their precedent dependencies.
 *      - Successful cases:
 *        a. Single end, single start, critical path does not change midway.
 *        b. Single end, single start, critical path changes midway.
 *        c. Multiple starts, multiple ends, critical path changes multiple times.
 *     - Failure cases:
 *       a. Invalid numerical input: tasks' duration is not a number,
 *          any invalid number larger than max double or less than 0.
 *       b. Invalid graphical input: the graph presentation of input is not directed acyclic graph. Graph presentation
 *          of input must be a tree for this implementation of CPM to work.
 *
 */

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

SCENARIO("Success case 1: simple path") {

    GIVEN("Simple valid graph, no changing midway, single end and start") {

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

        std::vector<shared_ptr<Task>> input;
        input.insert(input.end(), {taskA, taskB, taskC, taskD, taskE, taskF, taskG});

        WHEN ("simple valid path, no change in critical path midway") {

            double expected_ECT = 25;
            std::vector<shared_ptr<Task>> critical_path{taskA, taskB, taskD, taskG};
            shared_ptr<Project> newAnalysis(new Project(input));

            THEN("no change critical path") {
                try{
                    auto ret =  newAnalysis->getAnalysis();
                    REQUIRE(ret->ECT == expected_ECT);
                    REQUIRE(ret->criticalPath.size() == critical_path.size());
                    REQUIRE(checkInclude(critical_path, ret->criticalPath));
                } catch (std::logic_error) {
                    FAIL("LOGIC ERROR");
                }
            }

        }

        WHEN("simple vaid path, changes in critical path") {
            shared_ptr<Task> newTaskE (new Task(12, 12, "newTaskE", vector<shared_ptr<Task> > {
                taskC
            }));
            shared_ptr<Task> newTaskF (new Task(10, 10, "newTaskF", vector<shared_ptr<Task> > {
                taskC
            }));

            input.erase(remove(input.begin(), input.end(), taskE), input.end());
            input.erase(remove(input.begin(), input.end(), taskF), input.end());
            input.insert(input.end(), newTaskE);
            input.insert(input.end(), newTaskF);

            taskG->dependencies.erase(remove(taskG->dependencies.begin(), taskG->dependencies.end(), taskE), taskG->dependencies.end());
            taskG->dependencies.erase(remove(taskG->dependencies.begin(), taskG->dependencies.end(), taskF), taskG->dependencies.end());
            taskG->dependencies.push_back(newTaskE);
            taskG->dependencies.push_back(newTaskF);


            double expected_ECT = 29;
            std::vector<shared_ptr<Task>> critical_path{taskA, taskC, newTaskE, taskG};
            shared_ptr<Project> newAnalysis (new Project(input));

            THEN("changes in critical path") {
                try{
                    auto ret =  newAnalysis->getAnalysis();
                    REQUIRE(ret->ECT == expected_ECT);
                    REQUIRE(ret->criticalPath.size() == critical_path.size());
                    REQUIRE(checkInclude(critical_path, ret->criticalPath));
                } catch (std::logic_error) {
                    FAIL("LOGIC ERROR");
                }
            }
        }

    }

    GIVEN("Complex valid path, multiple starts, multiple ends, paths changes continuously") {
        shared_ptr<Task> taskA1(new Task(5, 5, "A1", vector<shared_ptr<Task>>()));
        shared_ptr<Task> taskA2(new Task(6, 6, "A2", vector<shared_ptr<Task>>()));
        shared_ptr<Task> taskB(new Task(10, 10, "B",
                                        vector<shared_ptr<Task>>({taskA1})));
        shared_ptr<Task> taskC(new Task(8, 8, "C",
                                        vector<shared_ptr<Task>>({taskA1, taskA2})));
        shared_ptr<Task> taskE(new Task(12, 12, "E",
                                        vector<shared_ptr<Task>>({taskC})));
        shared_ptr<Task> taskF(new Task(10, 10, "F",
                                        vector<shared_ptr<Task>>({taskC})));
        shared_ptr<Task> taskD(new Task(6, 6, "D",
                                        vector<shared_ptr<Task>>({taskB, taskE})));
        shared_ptr<Task> taskG(new Task(4, 4, "G",
                                        vector<shared_ptr<Task>>({taskF})));
        std::vector<shared_ptr<Task>> input;
        input.insert(input.end(), {taskA1, taskA2, taskB, taskC, taskD, taskE, taskF, taskG});


        WHEN("complex path, changes in critical path midway") {
            double expected_ECT = 32;
            std::vector<shared_ptr<Task>> critical_path{taskA2, taskC, taskC, taskD};
            shared_ptr<Project> newAnalysis (new  Project(input));

            THEN("changes in critical path") {
                try{
                    auto ret =  newAnalysis->getAnalysis();
                    REQUIRE(ret->ECT == expected_ECT);
                    REQUIRE(ret->criticalPath.size() == critical_path.size());
                    REQUIRE(checkInclude(critical_path, ret->criticalPath));
                } catch (std::logic_error) {
                    FAIL("LOGIC ERROR");
                }
            }
        }
    }

    GIVEN("invalid input, graph has cycles, single end, single start") {
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
        //add loop at taskG
        taskE->dependencies.push_back(taskG);

        vector<shared_ptr<Task>> input;
        input.insert(input.end(), {taskA, taskB, taskC, taskD, taskE, taskF, taskG});

        WHEN ("simple valid path, no change in critical path midway") {
            shared_ptr<Project> newAnalysis(new Project(input));

            THEN("no change critical path") {
                try {
                    newAnalysis->getAnalysis();
                    FAIL("EXPECTED ERROR THROWN");
                } catch (logic_error) {
                    SUCCEED("EXPECTED");
                }
            }

        }
    }
}