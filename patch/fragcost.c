#include "proto.h"

unsigned ** generate_fragment_cost_matrix (Buffer source, Buffer target, unsigned fragment_length) {
  unsigned source_fragments = source -> length ? 1 + (source -> length - 1) / fragment_length : 0;
  unsigned target_fragments = target -> length ? 1 + (target -> length - 1) / fragment_length : 0;
  unsigned ** result = malloc((sizeof(unsigned) * (target_fragments + 1) + sizeof(unsigned *)) * (source_fragments + 1));
  unsigned * row_pointer = (unsigned *) (result + source_fragments + 1);
  unsigned source_fragment, target_fragment;
  const unsigned char * source_pointer = source -> data;
  const unsigned char * target_pointer;
  for (source_fragment = 0; source_fragment < source_fragments; source_fragment ++) {
    result[source_fragment] = row_pointer;
    target_pointer = target -> data;
    for (target_fragment = 0; target_fragment < target_fragments; target_fragment ++) {
      result[source_fragment][target_fragment] = calculate_estimated_fragment_cost(source_pointer, target_pointer, fragment_length);
      target_pointer += fragment_length;
    }
    result[source_fragment][target_fragments] = calculate_estimated_fragment_cost(source_pointer, NULL, fragment_length);
    row_pointer += target_fragments + 1;
    source_pointer += fragment_length;
  }
  result[source_fragments] = row_pointer;
  target_pointer = target -> data;
  for (target_fragment = 0; target_fragment < target_fragments; target_fragment ++) {
    result[source_fragments][target_fragment] = calculate_estimated_fragment_cost(NULL, target_pointer, fragment_length);
    target_pointer += fragment_length;
  }
  result[source_fragments][target_fragments] = calculate_estimated_fragment_cost(NULL, NULL, fragment_length);
  return result;
}

unsigned calculate_estimated_fragment_cost (const unsigned char * source, const unsigned char * target, unsigned length) {
  if (!source) {
    if (!target) return 0;
    return calculate_estimated_fragment_cost(target, source, length);
  }
  unsigned pos, result = 0;
  if (target)
    for (pos = 0; pos < length; pos ++) if (source[pos] == target[pos]) result ++;
  else
    for (pos = 0; pos < length; pos ++) if (!source[pos]) result ++;
  return result;
}
