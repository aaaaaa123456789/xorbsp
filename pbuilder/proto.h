#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <setjmp.h>

#include "../headers/const.h"
#include "../headers/enum.h"
#include "../codegen/public.h"
#include "../optparse/pubtypes.h"
#include "../util/public.h"

#include "struct.h"
#include "public.h"

#define get_label(member_name, label_name) get_defined_label(&(builder_state -> labels.member_name), label_name)
#define inst(...) add_instruction_to_codefile(builder_state -> codefile, __VA_ARGS__, ARGTYPE_END)

// errorfn.c
void define_error_function(void);
void simple_error_message_function(char **, unsigned);
void descriptive_error_message_function(char **, unsigned);
int add_string_to_printed_error_messages(int **, char ***, unsigned *, char *);

// global.c
extern void * builder_memory_region;
extern struct code_generation_state * builder_state;
extern jmp_buf builder_return_point;
extern char * builder_error;
extern const char * const code_error_messages[];

// init.c
void initialize_builder_state(Options, CodeFile);
void initialize_code_generator(void);
int declare_register(const char *, unsigned char);
int declare_constant(const char *, unsigned);

// main.c
void builder_throw(const char *, ...);

// mainfn.c
void define_main_function(void);

// runtime.c
void generate_runtime(void);
int get_defined_label(int *, const char *);
int generate_banner_lines(const char *, char ***);
void destroy_banner_lines(char **, unsigned);

// utilfn.c
void define_detect_input_function(void);
void define_get_nth_string_function(void);
