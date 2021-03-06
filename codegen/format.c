#include "proto.h"

char * generate_formatted_number_for_file (unsigned number) {
  // rules:
  // 1) anything between -255 and 255 is printed in decimal (123, -45)
  // 2) anything that fits in 16 bits and sign is printed in four hex digits and sign (0x0123, -0x4567)
  // 3) anything else is printed as a full 32-bit unsigned value in hex (0x00012345, 0x89abcdef, 0xfffedcba)
  char * result = malloc(16);
  unsigned negated = 0x100000000 - number; // technically this is just -number, but let's be standards-compliant
  if (number < 0x100)
    sprintf(result, "%u", number);
  else if (number < 0x10000)
    sprintf(result, "0x%04x", number);
  else if (negated < 0x100)
    sprintf(result, "-%u", negated);
  else if (negated < 0x10000)
    sprintf(result, "-0x%04x", negated);
  else
    sprintf(result, "0x%08x", number);
  return result;
}

char * generate_formatted_argument (CodeFile file, struct instruction_argument argument, char ** error) {
  if (error) *error = NULL;
  switch (argument.type) {
    case ARGTYPE_NONE:
      return duplicate_string("");
    case ARGTYPE_IMMEDIATE:
      return generate_formatted_number_for_file(argument.value);
    case ARGTYPE_NAMED_CONSTANT:
      if (argument.value < file -> constant_count) return duplicate_string(file -> constants[argument.value]);
      if (error) *error = generate_string("undefined constant (ID %u)", argument.value);
      return NULL;
    case ARGTYPE_REGISTER:
      if (argument.value <= 255) return generate_string("#%u", argument.value);
      if (error) *error = generate_string("invalid variable number: %u", argument.value);
      return NULL;
    case ARGTYPE_NAMED_REGISTER:
      if (argument.value < file -> register_count) return generate_string("#%s", file -> registers[argument.value]);
      if (error) *error = generate_string("undefined variable (ID %u)", argument.value);
      return NULL;
    case ARGTYPE_NAMED_LABEL:
      if ((argument.value < file -> label_count) && file -> labels[argument.value]) return duplicate_string(file -> labels[argument.value]);
      if (error) *error = generate_string("undefined label (ID %u)", argument.value);
      return NULL;
    case ARGTYPE_NUMERIC_LOCAL:
      if (argument.value && (argument.value <= file -> next_numeric_local)) return generate_string(".L%u", argument.value);
      if (error) *error = generate_string("invalid numeric local %u", argument.value);
      return NULL;
    case ARGTYPE_NUMERIC_DATA:
      if (argument.value && (argument.value <= file -> next_numeric_data)) {
        char buffer[16];
        sprintf(buffer, "Data%u", argument.value);
        return generate_prefixed_label(file, buffer);
      }
      if (error) *error = generate_string("invalid numeric data label %u", argument.value);
      return NULL;
    case ARGTYPE_LOCAL_LABEL:
      if (validate_named_object(argument.string)) return generate_string(".%s", argument.string);
      if (error) *error = generate_string("invalid label: %s", argument.string);
      return NULL;
    case ARGTYPE_GLOBAL_LABEL:
      if (!validate_named_object(argument.string)) {
        if (error) *error = generate_string("invalid label: %s", argument.string);
        return NULL;
      }
    case ARGTYPE_PASSTHROUGH:
      return duplicate_string(argument.string);
    default:
      if (error) *error = generate_string("invalid argument type: %hhu", argument.type);
      return NULL;
  }
}
