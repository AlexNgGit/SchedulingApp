#include <catch2/catch_test_macros.hpp>
#include <cstdint>
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

#include <catch2/catch_test_macros.hpp>

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

SCENARIO("Success case 1: simple path") {
    GIVEN("initialization: simple path, no changing midway, single end and start") {
        Task taskA = Task(5, 5, "A");
        Task taskB = Task(10, 10, "B");
        Task taskC = Task(8, 8, "C");
        Task taskD = Task(6, 6, "D");
        Task taskE = Task(7, 7, "E");
        Task taskF = Task(4, 4, "F");
        Task taskG = Task(4, 4, "G");
    }
}