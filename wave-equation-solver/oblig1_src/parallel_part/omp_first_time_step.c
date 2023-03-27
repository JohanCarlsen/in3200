#include <omp.h>

void omp_first_time_step (int nx, int ny, double dx, double dy, double dt,
			  double **u, double **u_prev)
{
	double dt_over16 = dt * dt / 16.;
	double dt_overdx = dt_over16 / (dx * dx);
	double dt_overdy = dt_over16 / (dy * dy);
	double u_left, u_right, u_below, u_above;

	// Set value for i = j = 0.
	u[0][0] = u_prev[0][0] + dt_overdx * (u_prev[0][1] - 2 * u_prev[0][0] + u_prev[0][1])
												 + dt_overdy * (u_prev[1][0] - 2 * u_prev[0][0] + u_prev[1][0]);

  // Parallel region.
  #pragma omp parallel for private(dt_overdx, dt_overdy, u_left, u_right, u_below, u_above)
  for (int i = 1; i < ny - 1; i++)
  {
  	u_left = u_prev[i][1];
  	u_right = u_prev[i][1];
  	u_below = u_prev[i-1][0];
  	u_above = u_prev[i+1][0];

  	u[i][0] = u_prev[i][0] + dt_overdx * (u_left - 2 * u_prev[i][0] + u_right)
													 + dt_overdy * (u_below - 2 * u_prev[i][0] + u_above);

		for (int j = 1; j < nx - 1; j++)
		{
			u_left = u_prev[i][j-1];
			u_right = u_prev[i][j+1];
			u_below = u_prev[i-1][j];
			u_above = u_prev[i+1][j];

			u[i][j] = u_prev[i][j] + dt_overdx * (u_left - 2 * u_prev[i][j] + u_right)
														 + dt_overdy * (u_below - 2 * u_prev[i][j] + u_above);
		}

		u[i][nx-1] = u_prev[i][nx-1] + dt_overdx * (u_prev[i][nx-2] - 2 * u_prev[i][nx-1] + u_prev[i][nx-2])
																 + dt_overdy * (u_prev[i-1][nx-1] - 2 * u_prev[i][nx-1] + u_prev[i+1][nx-1]);
  }

  u[ny-1][nx-1] = u_prev[ny-1][nx-1] + dt_overdx * (u_prev[ny-1][nx-2] - 2 * u_prev[ny-1][nx-1] + u_prev[ny-1][nx-2])
  																	 + dt_overdy * (u_prev[ny-2][nx-1] - 2 * u_prev[ny-1][nx-1] + u_prev[ny-2][nx-1]);
}
