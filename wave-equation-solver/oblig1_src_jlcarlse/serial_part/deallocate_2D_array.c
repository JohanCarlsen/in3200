#include <stdlib.h>

void deallocate_2D_array (double **array)
{
  // Deallocating the array using the free() method.
  free(array);
}
