// options.c
char * prefix_option(Options, const char *, int);
char * label_prefix_option(Options, const char *, int);
char * constant_prefix_option(Options, const char *, int);
char * variable_prefix_option(Options, const char *, int);
char * set_next_input_file_mode(Options, int);
char * set_compiled_output_file(Options, const char *, int);
char * set_bsp_output_file(Options, const char *, int);
char * set_hide_errors_option(Options, int);
char * set_force_output_menu_option(Options, int);
char * disable_output_validation_option(Options, int);
char * no_source_to_source_option(Options, int);
char * sort_target_list_option(Options, int);
char * set_target_and_reference_option(Options, int);
char * title_file_option(Options, const char *, int);
char * suppress_errors_option(Options, int);
char * targets_per_page_option(Options, const char *, int);
char * check_fragment_permutation_option(Options, int);
char * set_fragment_size(Options, const char *, int);
char * set_padding_value(Options, const char *, int);
char * opening_banner_option(Options, const char *, int);
char * opening_banner_from_file_option(Options, const char *, int);
char * success_message_option(Options, const char *, int);
char * success_message_from_file_option(Options, const char *, int);
char * error_message_option(Options, const char *, int);
char * error_message_from_file_option(Options, const char *, int);
char * error_text_substitute_option(Options, const char *, int);
char * set_operation_mode_option(Options, int);
char * set_patch_method_option(Options, const char *, int);
