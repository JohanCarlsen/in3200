#include <stdlib.h>

void allocate_2D_array (double ***array_ptr, int nx, int ny)
{
  // Allocate space for the 2D array as a 1D contigous memory array.
  double *array_storage = (double*) malloc(ny * nx * sizeof(double*));

  // Allocate the 2D array.
  array_ptr[0] = (double**) malloc(nx * sizeof(double*));

  for (int i = 0; i < ny; i++)
  {
    // Here, each entry i of array_ptr will have nx elements, 
    // ensuring contigous memory allocation of the array.
    array_ptr[0][i] = &(array_storage[i * nx]);
  } 
}
