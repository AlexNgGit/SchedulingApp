#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include "../controller/Task/Task.h"
#include "../controller/Analysis/Analysis.h"
/**
 * Using Catch2 testing library, this test file aims to cover the majority of failure as well successful cases for
 * calculating the earliest completed time, critical path as well as the slack cost based on CPM (Critical Path Method,
 * specified in Analysis file's documentation).
 * These will cover:
 *   1) First user case allows to retract those information with the assumption tasks are given with the duration
 *   and their precedent dependencies.
 *      - Successful cases:
 *        a. Single end, single start, critical path does not change midway.
 *        b. Single end, single start, critical path changes midway.
 *        c. Multiple starts, multiple ends, critical path changes multiple times.
 *     - Failure cases:
 *       a. Invalid numerical input: tasks' duration is not a number,
 *          or less than 1000 and invalid number larger than max double
 *       b. Invalid graphical input: the graph presentation of input is not directed acyclic graph. Graph presentation
 *          of input must be a tree for this implementation of CPM to work.
 *
 */



SCENARIO("Success case 1: simple path") {

    GIVEN("Simple valid graph, no changing midway, single end and start") {

        std::vector<Task> taskADep;
        Task taskA = Task(5, 5, "A", taskADep);
        std::vector<Task> taskBDep;
        taskBDep.push_back(taskA);
        Task taskB = Task(10, 10, "B", taskBDep);
        std::vector<Task> taskCDep;
        taskCDep.push_back(taskA);
        Task taskC = Task(8, 8, "C", taskCDep);
        std::vector<Task> taskDDep;
        taskDDep.push_back(taskB);
        Task taskD = Task(6, 6, "D", taskDDep);
        std::vector<Task> taskEDep;
        taskEDep.push_back(taskC);
        Task taskE = Task(7, 7, "E", taskEDep);
        std::vector<Task> taskFDep;
        taskFDep.push_back(taskC);
        Task taskF = Task(4, 4, "F", taskFDep);
        std::vector<Task> taskGDep;
        taskGDep.push_back(taskE);
        taskGDep.push_back(taskF);
        Task taskG = Task(4, 4, "G", taskGDep);

        std::vector<Task> input;
        input.insert(input.end(), {taskA, taskB, taskC, taskD, taskE, taskF, taskC});

        WHEN("simple path, no change in critical path midway") {
            Task newTaskE = Task(12, 12, "newTaskE", taskEDep);
            Task newTaskF = Task(10, 10, "newTaskF", taskFDep);
            input.erase(std::remove(input.begin(), input.end(), taskE), input.end());
            input.erase(std::remove(input.begin(), input.end(), taskF), input.end());
            input.insert(input.end(), newTaskE);
            input.insert(input.end(), newTaskF);

            double expected_ECT = 27;
            std::vector<Task> critical_path{taskA, taskB, taskD, taskG};
            Analysis newAnalysis = Analysis(input);

            THEN("no change critical path") {
                auto ret = newAnalysis.performAnalysis();
                REQUIRE(ret.ECT == expected_ECT);
                REQUIRE(ret.criticalPath == critical_path);
            }

        }

        WHEN("simple path, changes in critical path midway") {
            Task newTaskE = Task(12, 12, "newTaskE", taskEDep);
            Task newTaskF = Task(10, 10, "newTaskF", taskFDep);
            input.erase(std::remove(input.begin(), input.end(), taskE), input.end());
            input.erase(std::remove(input.begin(), input.end(), taskF), input.end());
            input.insert(input.end(), newTaskE);
            input.insert(input.end(), newTaskF);

            double expected_ECT = 29;
            std::vector<Task> critical_path{taskA, taskB, taskD, taskG};
            Analysis newAnalysis = Analysis(input);

            THEN("changes in critical path") {
                auto ret = newAnalysis.performAnalysis();
                REQUIRE(ret.ECT == expected_ECT);
                REQUIRE(ret.criticalPath == critical_path);
            }
        }

    }

    GIVEN("Complex valid path, multiple starts, multiple ends, paths changes continuously") {

    }
}