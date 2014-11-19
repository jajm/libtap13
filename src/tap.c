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
#include <string.h>

#include <yaml.h>

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

// We write our own handler, so we can print the initial indent of 2 spaces.
int tap_yaml_write_handler(void *data, unsigned char *buffer, size_t size)
{
	unsigned char *bptr = buffer;
	size_t i = 0;

	// Avoid compilation warning about unused variable
	if (data) {}

	while (*bptr != '\0' && i < size) {
		if (*bptr == '\n') {
			fputc('\n', stdout);
			if (*(bptr+1) != '\0') {
				fputs("  ", stdout);
			}
		} else {
			fputc(*bptr, stdout);
		}
		bptr++;
		i++;
	}

	return 1;
}

void tap_yaml_node_set_block_style(yaml_node_t *node, yaml_document_t *document)
{
	yaml_node_item_t *item_iter;
	yaml_node_pair_t *pair_iter;

	switch (node->type) {
		case YAML_SEQUENCE_NODE:
			node->data.sequence.style = YAML_BLOCK_SEQUENCE_STYLE;

			item_iter = node->data.sequence.items.start;
			while (item_iter < node->data.sequence.items.top) {
				yaml_node_t *n = &(document->nodes.start[(*item_iter) - 1]);
				tap_yaml_node_set_block_style(n, document);
				item_iter++;
			}
			break;

		case YAML_MAPPING_NODE:
			node->data.mapping.style = YAML_BLOCK_MAPPING_STYLE;

			pair_iter = node->data.mapping.pairs.start;
			while (pair_iter < node->data.mapping.pairs.top) {
				yaml_node_t *n = &(document->nodes.start[pair_iter->value - 1]);
				tap_yaml_node_set_block_style(n, document);
				pair_iter++;
			}
			break;

		default:
			break;
	}
}

void tap_yaml_document_set_block_style(yaml_document_t *document)
{
	yaml_node_t *node;

	node = yaml_document_get_root_node(document);
	tap_yaml_node_set_block_style(node, document);
}

void tap_yaml_write(const char *yaml, va_list vl)
{
	yaml_parser_t parser;
	yaml_document_t document;
	yaml_emitter_t emitter;
	char buffer[8192];
	size_t length;

	if (yaml == NULL) {
		return;
	}

	length = vsnprintf(buffer, 8192, yaml, vl);

	yaml_parser_initialize(&parser);
	yaml_parser_set_input_string(&parser, (unsigned char*) buffer, length);
	if (yaml_parser_load(&parser, &document)) {
		document.start_implicit = 0;
		document.end_implicit = 0;

		tap_yaml_document_set_block_style(&document);

		yaml_emitter_initialize(&emitter);
		yaml_emitter_set_output(&emitter, tap_yaml_write_handler, NULL);
		yaml_emitter_set_indent(&emitter, 2);

		// Initial indent
		fputs("  ", stdout);

		yaml_emitter_open(&emitter);
		yaml_emitter_dump(&emitter, &document);
		yaml_emitter_close(&emitter);

		yaml_parser_delete(&parser);
		yaml_emitter_delete(&emitter);
		yaml_document_delete(&document);
	} else {
		fprintf(stderr, "Error: %s %s at offset %zu\n",
			parser.problem, parser.context,
			parser.problem_mark.index);
	}
}

void tap_ok(const char *file, const char *func, int line, int ok,
	const char *description, ...)
{
	va_list vl;
	char buffer[8192];

	current_test += 1;

	if (!planned && current_test == 1) {
		tap_print_version();
	}

	printf("%s %d", ok ? "ok" : "not ok", current_test);

	va_start(vl, description);
	if (description != NULL) {
		vsnprintf(buffer, 8192, description, vl);
		printf(" %s", buffer);
	}

	if (!ok) {
		printf(" in %s (%s:%d)", func, file, line);
	}

	if (in_todo) {
		printf(" # TODO %s",
			(todo_explanation != NULL) ? todo_explanation : "");
	}

	printf("\n");

	if (!ok) {
		tap_yaml_write(va_arg(vl, const char *), vl);
	}
	va_end(vl);
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
