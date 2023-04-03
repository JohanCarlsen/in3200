#include <omp.h>

void omp_first_time_step (int nx, int ny, double dx, double dy, double dt,
			  double **u, double **u_prev)
{
	double u_left, u_right, u_below, u_above;

	#pragma omp parallel for private(u_left, u_right, u_below, u_above)
  	for (int i = 0; i < ny; i++)
  	{
    	for (int j = 0; j < nx; j++)
	    {
	      // Defining element to the left
	      if (j == 0)
	      {
	        u_left = u_prev[i][1];
	      }

	      else
	      {
	        u_left = u_prev[i][j-1];
	      }

	      // Defining element to the right
	      if (j == (nx - 1))
	      {
	        u_right = u_prev[i][nx-2];
	      }

	      else
	      {
	        u_right = u_prev[i][j+1];
	      }

	      // Defining element below 
	      if (i == 0)
	      {
	        u_below = u_prev[1][j];
	      }

	      else
	      {
	        u_below = u_prev[i-1][j];
	      }

	      // Defining element above 
	      if (i == (ny - 1))
	      {
	        u_above = u_prev[ny-2][j];
	      }

	      else
	      {
	        u_above = u_prev[i+1][j];
	      }

	      // Updating u at time level l=1
	      u[i][j] = u_prev[i][j] + dt * dt / (16. * dx * dx)
	              * (u_left - 2 * u_prev[i][j] + u_right) + dt * dt / (16. * dy * dy)
	              * (u_below - 2 * u_prev[i][j] + u_above);
	    }
	}
}
