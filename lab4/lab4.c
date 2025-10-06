#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

int main() {
  void *heap_start = sbrk(256);
  if (heap_start == (void *)-1)
    return 1;

  struct header *first = (struct header *)heap_start;
  struct header *second = (struct header *)((char *)heap_start + 128);

  first->size = 128;
  first->next = NULL;
  second->size = 128;
  second->next = first;

  void *firstData = (char *)first + sizeof(struct header);
  void *secondData = (char *)second + sizeof(struct header);

  memset(firstData, 0, 128 - sizeof(struct header));
  memset(secondData, 1, 128 - sizeof(struct header));

  printf("first block: %p\n", (void *)first);
  printf("second block: %p\n", (void *)second);
  printf("first block size: %lu\n", first->size);
  printf("first block next: %p\n", (void *)first->next);
  printf("second block size: %lu\n", second->size);
  printf("second block next: %p\n", (void *)second->next);

  unsigned char *first_data = (unsigned char *)firstData;
  unsigned char *second_data = (unsigned char *)secondData;

  for (int i = 0; i < 128 - sizeof(struct header); i++) {
    printf("%d\n", first_data[i]);
  }
  for (int i = 0; i < 128 - sizeof(struct header); i++) {
    printf("%d\n", second_data[i]);
  }

  return 0;
}
