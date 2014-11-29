#ifndef tap_t_run_h_included
#define tap_t_run_h_included

int run(void (*test_plan)(void), char *expected[], unsigned int n);

#define run(test_plan, expected) \
	run(test_plan, expected, sizeof(expected)/sizeof(*expected))

#endif /* ! tap_t_run_h_included */
