#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *curr = free_list_ptr;

  while (curr != NULL) {
    if (curr->size >= size) {
      return curr->id;
    }
    curr = curr->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  struct header *curr = free_list_ptr;
  uint64_t smallest_diff = UINT64_MAX;

  while (curr != NULL) {
    if (curr->size >= size) {
      uint64_t diff = curr->size - size;

      if (diff < smallest_diff) {
        smallest_diff = diff;
        best_fit_id = curr->id;
      }
    }
    curr = curr->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  struct header *curr = free_list_ptr;
  uint64_t largest_size = 0;

  while (curr != NULL) {
    if (curr->size >= size && curr->size > largest_size) {
      largest_size = curr->size;
      worst_fit_id = curr->id;
    }
    curr = curr->next;
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);
  return 0;
}

/*
 * part 2: coalescing contiguous free blocks
 *
 * first: setting prev = null, curr = free_list_ptr
 *
 * second: loop through, and find where the free block should go
 *
 * third: insert a new_free_block between prev and curr.
 * new_free_block->curr
 *
 * fourth: if the blocks touch with the previous block, then merge them together
 *
 * fifth: if the next block touch, then merge with it as well
 *
 * */
