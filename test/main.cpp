#include <catch2/catch_test_macros.hpp>
#include "../controller/Task/Task.h"
#include "../controller/Analysis/Analysis.h"

/**
 * Using Catch2 testing library, this test file aims to cover the majority of failure as well successful cases for
 * calculating the earliest completed time, critical path as well as the slack cost based on CPM (Critical Path Method).
 * These will cover:
 *   1) First user case allows to retract those information with the assumption tasks are given with the duration
 * and their precedent dependencies.
 *
 */

/**
 *
 * @require:
 */


unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

SCENARIO("Success case 1: simple path") {
    GIVEN("initialization: simple path, no changing midway, single end and start") {
        Task taskA = Task(5, 5, "A");
        std::vector<Task> taskADep;
        Task taskB = Task(10, 10, "B");
        std::vector<Task> taskBDep;
        taskBDep.push_back(taskA);
        Task taskC = Task(8, 8, "C");
        std::vector<Task> taskCDep;
        taskCDep.push_back(taskA);
        Task taskD = Task(6, 6, "D");
        std::vector<Task> taskDDep;
        taskDDep.push_back(taskB);
        Task taskE = Task(7, 7, "E");
        std::vector<Task> taskEDep;
        taskEDep.push_back(taskC);
        Task taskF = Task(4, 4, "F");
        std::vector<Task> taskFDep;
        taskFDep.push_back(taskC);
        Task taskG = Task(4, 4, "G");
        std::vector<Task> taskGDep;
        taskGDep.push_back(taskE);
        taskGDep.push_back(taskF);



        std::unordered_map<Task, std::vector<Task>> taskDependencies
                {
                        {taskA, taskADep},
                        {taskB, taskBDep},
                        {taskC, taskCDep},
                        {taskD, taskDDep},
                        {taskE, taskEDep},
                        {taskG, taskGDep},
                }
        ;



        WHEN("simple path, no changes in critical path midway") {
            double expected_ECT = 25;
            std::vector<Task> expected_sorted {taskA, taskB, taskC, taskE, taskF, taskF, taskD, taskG};
            std::vector<Task> critical_path{taskA, taskB, taskD, taskG};
        }

        WHEN("simple path, changes in critical path in midway") {
            taskDependencies.erase(taskE);
            taskDependencies.erase(taskG);
            Task taskE = Task(12, 12, "E");
            Task taskF = Task(10, 10, "F");
            taskDependencies.insert({taskE, taskEDep});
            taskDependencies.insert({taskF, taskFDep});
            double expected_EST = 29;
            std::vector<Task> expected_sorted {taskA, taskB, taskC, taskE, taskF, taskF, taskD, taskG};
            std::vector<Task> critical_path{taskA, taskB, taskD, taskG};

        }

    }
}