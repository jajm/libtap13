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

#ifndef libtap13_tap_h_included
#define libtap13_tap_h_included

#include <stdlib.h>
#include <string.h>

void tap_plan(unsigned int number_of_tests);
void tap_skip_all(const char *reason);
void tap_done_testing(void);

void tap_ok(int ok, const char *description, const char *yaml, ...);

int tap_todo_start(const char *explanation);
void tap_todo_end(void);
void tap_skip(unsigned int number_of_tests, const char *reason);
void tap_bail_out(const char *reason);
void tap_diag(const char *diagnostic, ...);

#define plan(number_of_tests) tap_plan(number_of_tests)
#define skip_all(reason) tap_skip_all(reason)
#define done_testing() tap_done_testing()

#define ok(...) tap_ok(__VA_ARGS__, NULL, NULL)

#define fail(...) ok(0, __VA_ARGS__)
#define pass(...) ok(1, __VA_ARGS__)

#define is(got, expected, ...) ok(got == expected,  ##__VA_ARGS__)
#define isnt(got, expected, ...) ok(got != expected,  ##__VA_ARGS__)

#define str_eq(got, expected, ...) ok(0 == strcmp(got, expected), ##__VA_ARGS__)

#define todo(explanation) \
	for (int tap_loop_stop = tap_todo_start(explanation); \
	!tap_loop_stop; tap_todo_end(), tap_loop_stop = 1)

#define skip(number_of_tests, reason) \
	tap_skip(number_of_tests, reason)

#define skip_if(condition, number_of_tests, reason) \
	if (condition) skip(number_of_tests, reason); else

#define bail_out(reason) tap_bail_out(reason)
#define diag(...) tap_diag(__VA_ARGS__)

#endif /* ! libtap13_tap_h_included */

