/*
 * Copyright 2013 Julian Maurice
 *
 * This file is part of libtap13
 *
 * libtap13 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libtap13 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libtap13.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * libtap13 is a TAP13 emitter.
 * More infos on TAP13: http://podwiki.hexten.net/TAP/TAP13.html
 */

#ifndef libtap13_tap_h_included
#define libtap13_tap_h_included

#include <stdlib.h>
#include <string.h>

/* Declare a test plan.
 *
 * void plan(unsigned int number_of_tests);
 *
 * Parameters
 *   number_of_tests: Number of expected tests.
 */
#define plan(number_of_tests) tap_plan(number_of_tests)

/* Declare that all tests are skipped.
 *
 * void skip_all(const char *reason);
 *
 * Parameters
 *   reason: Why all tests are skipped ?
 */

#define skip_all(reason) tap_skip_all(reason)

/* Declare test plan at the end of tests.
 *
 * If you don't know in advance how many tests will run, use this function
 * after the last test is run.
 *
 * void done_testing(void);
 */
#define done_testing() tap_done_testing()

/* Run a test.
 *
 * void ok(test);
 * void ok(test, description);
 * void ok(test, description, yaml_diagnostic, ...);
 *
 * Parameters
 *   test           : An expression that should evaluate to 0 if test failed, or
 *                    any other value if test succeeded.
 *   description    : Description of test.
 *   yaml_diagnostic: A string in YAML format that is printed if test failed.
 *                    Can contain printf conversion specifications.
 */
#define ok(...) tap_ok(__VA_ARGS__, NULL, NULL)

/* Add a failing test.
 *
 * void fail();
 * void fail(description);
 * void fail(description, yaml_diagnostic, ...);
 *
 * Parameters
 *   description    : Description of test.
 *   yaml_diagnostic: A string in YAML format that is printed if test failed.
 *                    Can contain printf conversion specifications.
 */
#define fail(...) ok(0, ##__VA_ARGS__)

/* Add a passing test.
 *
 * void pass();
 * void pass(description);
 *
 * Parameters:
 *   description: Description of test.
 */
#define pass(...) ok(1, ##__VA_ARGS__)

/* Compare two values with '==' operator.
 *
 * void is(got, expected);
 * void is(got, expected, description);
 * void is(got, expected, description, yaml_diagnostic, ...);
 *
 * Parameters
 *   got            : Value to test.
 *   expected       : Comparison value.
 *   description    : Description of test.
 *   yaml_diagnostic: A string in YAML format that is printed if test failed.
 *                    Can contain printf conversion specifications.
 */
#define is(got, expected, ...) ok(got == expected,  ##__VA_ARGS__)

/* Compare two values with '!=' operator.
 *
 * void isnt(got, expected);
 * void isnt(got, expected, description);
 * void isnt(got, expected, description, yaml_diagnostic, ...);
 *
 * Parameters
 *   got            : Value to test.
 *   expected       : Comparison value.
 *   description    : Description of test.
 *   yaml_diagnostic: A string in YAML format that is printed if test failed.
 *                    Can contain printf conversion specifications.
 */
#define isnt(got, expected, ...) ok(got != expected,  ##__VA_ARGS__)

/* Compare two strings with strcmp().
 *
 * void str_eq(got, expected);
 * void str_eq(got, expected, description);
 * void str_eq(got, expected, description, yaml_diagnostic, ...);
 *
 * Parameters
 *   got            : String to test.
 *   expected       : Comparison string.
 *   description    : Description of test.
 *   yaml_diagnostic: A string in YAML format that is printed if test failed.
 *                    Can contain printf conversion specifications.
 */
#define str_eq(got, expected, ...) ok(0 == strcmp(got, expected), ##__VA_ARGS__)

/* Define a 'todo' block.
 *
 * A 'todo' block is a block which contain tests that are not expected to pass.
 *
 * Syntax is as follows:
 *
 *     todo(explanation) {
 *         ok(not_implemented_yet());
 *         // more tests...
 *     }
 *
 *  OR
 *
 *    todo(explanation) ok(not_implemented_yet()); // for a single test
 *
 * void todo(const char *explanation);
 *
 * Parameters
 *   explanation: Explanation on why these tests are marked as 'todo'
 */
#define todo(explanation) \
	for (int tap_loop_stop = tap_todo_start(explanation); \
	!tap_loop_stop; tap_todo_end(), tap_loop_stop = 1)

/* Skip some tests.
 *
 * void skip(unsigned int number_of_tests, const char *reason);
 *
 * Parameters
 *   number_of_tests: Number of tests to skip.
 *   reason         : Reason to skip those tests.
 */
#define skip(number_of_tests, reason) \
	tap_skip(number_of_tests, reason)

/* Define a 'skip' block.
 *
 * Syntax is as follows:
 *
 *     skip_if(cant_test(), 2, "skip 2 tests because we can't test") {
 *         ok(...);
 *         ok(...);
 *     }
 *
 * void skip_if(condition, unsigned int number_of_tests, const char *reason);
 *
 * Parameters
 *   condition      : An expression which should evaluate to true if tests have
 *                    to be skipped.
 *   number_of_tests: Number of tests to skip.
 *   reason         : Reason to skip those tests.
 */
#define skip_if(condition, number_of_tests, reason) \
	if (condition) skip(number_of_tests, reason); else

/* Bail out!
 *
 * Tell the test harness to stop further testing. This is useful if running a
 * test suite of several test programs.
 *
 * void bail_out(const char *reason);
 *
 * Parameters
 *   reason: Reason to bail out.
 */
#define bail_out(reason) tap_bail_out(reason)

/* Print a diagnostic message.
 *
 * void diag(const char *msg, ...);
 *
 * Parameters
 *   msg: A string in printf format, followed by any required arguments.
 */
#define diag(...) tap_diag(__VA_ARGS__)


/* Do not directly use the functions below */

void tap_plan(unsigned int number_of_tests);
void tap_skip_all(const char *reason);
void tap_done_testing(void);

void tap_ok(int ok, const char *description, const char *yaml, ...);

int tap_todo_start(const char *explanation);
void tap_todo_end(void);
void tap_skip(unsigned int number_of_tests, const char *reason);
void tap_bail_out(const char *reason);
void tap_diag(const char *diagnostic, ...);

#endif /* ! libtap13_tap_h_included */

