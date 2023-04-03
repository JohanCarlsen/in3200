#include <math.h>
#include <omp.h>

double omp_compute_numerical_error (int nx, int ny, double dx, double dy,
				    double t_value, double **u)
{
  // Defining pi.
  double pi = 4. * atan(1);
  double u_true, u_l, y, x;
  double error = 0.; 

  // Starting parallel region with a reduction clause. Each
  // thread will add their result to the error variable. 
  #pragma omp parallel for private(u_true, u_l, y, x) reduction (+: error)
  for (int i = 0; i < ny; i++)
  {
    y = i * dy;

    for (int j = 0; j < nx; j++)
    {
      x = j * dx;

      u_true = cos(2 * pi * x) * cos(2 * pi * y) * cos(pi * t_value);
      u_l = u[i][j];

      error += (u_true - u_l) * (u_true - u_l);
    }
  }

  error *= dx * dy;

  return sqrt(error);
}

