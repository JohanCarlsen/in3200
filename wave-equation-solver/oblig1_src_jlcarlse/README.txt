This program was made on macOS, so in order to bypass the Apple Clang, the GNU compiler version 12 is specifically used.

The serial_part is built like this:

> gcc-12 allocate_2D_array.c compute_numerical_error.c deallocate_2D_array.c one_fast_time_step.c first_time_step.c one_regular_time_step.c serial_main.c -o main.exe	

As the author has installed the version 12 of GCC, this method ensures the GCC compiler is used and not the Clang. 
The program is then run by:

> ./main.exe

The parallel_part is built like this:

> gcc-12 ../serial_part/allocate_2D_array.c ../serial_part/deallocate_2D_array.c omp_compute_numerical_error.c omp_first_time_step.c omp_one_fast_time_step.c omp_one_regular_time_step.c para_main.c -fopenmp -o main.exe

Remember to export the number of threads, eg. like this:

> export OMP_NUM_THREADS=4

The program is the run by:

> ./main.exe

The program will ask the user to re-enter the number of threads. This is done to correctly compute the time is takes the
program to finish. 

Both parts can be built with their respective makefile. 
In either folder, type:

> make build

in order to build the programs. This will run the same build-command(s) as above. 