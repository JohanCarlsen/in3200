void one_fast_time_step (int nx, int ny, double dx, double dy, double dt,
                         double **u_new, double **u, double **u_prev)
{
  // Since dx, dy, and dt are constant, it will be optimal to compute 
  // dt^2/8, 1/dx^2, and 1/dy^2 beforehand, and use them in the loop later.
  double dt_over8 = dt * dt / 8.;
  double dt_overdx = dt_over8 / (dx * dx);
  double dt_overdy = dt_over8 / (dy * dy);

  // Declaring the left, right, above, and below variabels 
  double u_left, u_right, u_below, u_above;

  // We start by initializing the value at i = j = 0.
  u_new[0][0] = 2 * u[0][0] + dt_overdx * (u[0][1] - 2 * u[0][0] + u[0][1])
                            + dt_overdy * (u[1][0] - 2 * u[0][0] + u[1][0])
                            - u_prev[0][0];

  // Iterating over all the elements.
  for (int i = 1; i < ny - 1; i++)
  {
    // Defining the left, right, below, and above elements of u
    // for i = 1, 2, 3, ... , ny-2, and j = 0.
    u_left = u[i][1];
    u_right = u[i][1];
    u_below = u[i-1][0];
    u_above = u[i+1][0];

    // Assigning the values at (i,0).
    u_new[i][0] = 2 * u[i][0] + dt_overdx * (u_left - 2 * u[i][0] + u_right)
                              + dt_overdy * (u_below - 2 *  u[i][0] + u_above)
                              - u_prev[i][0];

    // Assigning for j = 1, 2, 3, ... , nx-2.
    for (int j = 1; j < nx - 1; j++)
    {
      // Defining the left, right, below, and above elements of u.
      u_left = u[i][j-1];
      u_right = u[i][j+1];
      u_below = u[i-1][j];
      u_above = u[i+1][j];

      u_new[i][j] = 2 * u[i][j] + dt_overdx * (u_left - 2 * u[i][j] + u_right)
                                + dt_overdy * (u_below - 2 * u[i][j] + u_above)
                                - u_prev[i][j];
    }

    // Defining the left, right, below, and above elements of u 
    // for i = 1, 2, 3, ... , ny-2, and j = nx - 1.
    u_left = u[i][nx-2];
    u_right = u[i][nx-2];
    u_below = u[i-1][nx-1];
    u_above = u[i+1][nx-1];

    u_new[i][nx-1] = 2 * u[i][nx-1] + dt_overdx * (u_left - 2 * u[i][nx-1] + u_right)
                                    + dt_overdy * (u_below - 2 * u[i][nx-1] + u_above)
                                    - u_prev[i][nx-1];
  }

  // Finally, assigning the values at i = ny - 1, j = nx - 1.
  u_new[ny-1][nx-1] = 2 * u[ny-1][nx-1] + dt_overdx * (u[ny-1][nx-2] - 2 * u[ny-1][nx-1] + u[ny-1][nx-2])
                                        + dt_overdy * (u[ny-2][nx-1] - 2 * u[ny-1][nx-1] + u[ny-2][nx-1])
                                        - u_prev[ny-1][nx-1];
 
}
