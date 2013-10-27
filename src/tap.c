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

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static int planned = 0;
static unsigned int current_test = 0;
static int in_todo = 0;
static const char *todo_explanation = NULL;

void tap_print_version(void)
{
	printf("TAP version 13\n");
}

void tap_plan(unsigned int number_of_tests)
{
	if (planned) {
		fprintf(stderr, "Tests already planned.\n");
		return;
	}

	if (number_of_tests == 0) {
		fprintf(stderr, "Cannot plan 0 tests, use tap_skip_all.\n");
		return;
	}

	tap_print_version();
	printf("1..%d\n", number_of_tests);
	planned = 1;
}

void tap_skip_all(const char *reason)
{
	if (planned) {
		fprintf(stderr, "Tests already planned.\n");
		return;
	}

	tap_print_version();
	printf("1..0 # SKIP %s\n", (reason != NULL) ? reason : "");
	planned = 1;
}

void tap_done_testing(void)
{
	if (planned) {
		fprintf(stderr, "Tests already planned.\n");
		return;
	}

	printf("1..%d\n", current_test);
	planned = 1;
}

void tap_ok(int ok, const char *description, const char *yaml, ...)
{
	current_test += 1;

	if (!planned && current_test == 1) {
		tap_print_version();
	}

	printf("%s %d %s", ok ? "ok" : "not ok", current_test,
		(description != NULL) ? description : "");

	if (in_todo) {
		printf(" # TODO %s",
			(todo_explanation != NULL) ? todo_explanation : "");
	}

	printf("\n");

	if (!ok && yaml != NULL) {
		// TODO implement YAML feature
		printf("  ---\n");
		printf("  - 'YAML feature not implemented yet'\n");
		printf("  - 'raw yaml: %s'\n", yaml);
		printf("  ...\n");
	}
}

int tap_todo_start(const char *explanation)
{
	in_todo = 1;
	todo_explanation = explanation;

	return 0;
}

void tap_todo_end(void)
{
	in_todo = 0;
	todo_explanation = NULL;
}

void tap_skip(unsigned int number_of_tests, const char *reason)
{
	unsigned int i;

	if (!planned && current_test == 1) {
		tap_print_version();
	}

	for (i = 0; i < number_of_tests; i++) {
		current_test += 1;
		printf("ok %d # SKIP %s\n", current_test,
			(reason != NULL) ? reason : "");
	}
}

void tap_bail_out(const char *reason)
{
	if (!planned && current_test == 1) {
		tap_print_version();
	}

	printf("Bail out! %s\n", (reason != NULL) ? reason : "");
}

void tap_diag(const char *diagnostic, ...)
{
	va_list vl;

	printf("# ");
	va_start(vl, diagnostic);
	vprintf(diagnostic, vl);
	va_end(vl);
	printf("\n");
}
