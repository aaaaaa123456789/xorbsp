#include "proto.h"

Buffer create_buffer (void) {
  return calloc(1, sizeof(struct buffer));
}

Buffer create_buffer_from_size (unsigned size) {
  Buffer buffer = malloc(sizeof(struct buffer) + size);
  buffer -> length = size;
  return buffer;
}

void append_data_to_buffer (Buffer * buffer, const void * data, unsigned length) {
  *buffer = realloc(*buffer, sizeof(struct buffer) + (*buffer) -> length + length);
  if (data)
    memcpy((*buffer) -> data + (*buffer) -> length, data, length);
  else
    memset((*buffer) -> data + (*buffer) -> length, 0, length);
  (*buffer) -> length += length;
}

void resize_buffer (Buffer * buffer, unsigned new_length) {
  *buffer = realloc(*buffer, sizeof(struct buffer) + new_length);
  (*buffer) -> length = new_length;
}

void append_big_endian_number_to_buffer (Buffer * buffer, uintmax_t number, unsigned char length) {
  uintmax_t vbuf, vflip; // use the storage space for these variables as buffers
  unsigned char * buf = (unsigned char *) &vbuf;
  unsigned char * flipped = (unsigned char *) &vflip;
  unsigned char pos;
  write_number_to_buffer(buf, number, length);
  for (pos = 0; pos < length; pos ++) flipped[pos] = buf[length - 1 - pos];
  append_data_to_buffer(buffer, flipped, length);
}

void write_halfword_to_buffer (void * buffer, unsigned short number) {
  write_number_to_buffer(buffer, number, 2);
}

void write_word_to_buffer (void * buffer, unsigned number) {
  write_number_to_buffer(buffer, number, 4);
}

void write_number_to_buffer (void * buffer, uintmax_t number, unsigned char length) {
  unsigned char pos;
  unsigned char * bytebuf = buffer;
  for (pos = 0; pos < length; pos ++) {
    *(bytebuf ++) = number;
    number >>= 8;
  }
}

uintmax_t read_number_from_buffer (const void * buffer, unsigned char length) {
  if (length > sizeof(uintmax_t)) return UINTMAX_MAX;
  unsigned char current;
  uintmax_t result = 0;
  for (current = 0; current < length; current ++) result |= ((uintmax_t) current[(const unsigned char *) buffer]) << (current << 3);
  return result;
}
