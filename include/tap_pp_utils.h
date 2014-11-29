#ifndef tap_pp_utils_h_included
#define tap_pp_utils_h_included

#define TAP_PRIMITIVE_CAT(x1, x2) x1 ## x2
#define TAP_CAT(x1, x2) TAP_PRIMITIVE_CAT(x1, x2)

#define TAP_PASTE5(x1, x2, x3, x4, x5) x1 ## x2 ## x3 ## x4 ## x5

#define TAP_ARG16(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,N,...) N

#define TAP_HAS_COMMA(...) \
	TAP_ARG16(__VA_ARGS__,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0)

#define TAP_TRIGGER_PARENTHESIS(...) ,

#define TAP_ISEMPTY(...) \
	TAP_ISEMPTY_( \
		TAP_HAS_COMMA(__VA_ARGS__), \
		TAP_HAS_COMMA(TAP_TRIGGER_PARENTHESIS __VA_ARGS__), \
		TAP_HAS_COMMA(__VA_ARGS__ ()), \
		TAP_HAS_COMMA(TAP_TRIGGER_PARENTHESIS __VA_ARGS__ ()) \
	)

#define TAP_ISEMPTY_(x1, x2, x3, x4) \
	TAP_HAS_COMMA(TAP_PASTE5(TAP_IS_EMPTY_CASE_, x1, x2, x3, x4))

#define TAP_IS_EMPTY_CASE_0001 ,

#endif /* ! tap_pp_utils_h_included */
