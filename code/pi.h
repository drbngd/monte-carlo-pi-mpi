#include <stdio.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <mpi.h>

double pi_calc(long int n) {

    // Write your code below
    ////////////////////////////////////////

    /* fetch rank & size */
    int p, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* calculate # points for each processor */
    long int points_per_proc = n / p;
    long int remainder = n % p;
    if (rank < remainder) { points_per_proc++; }

    double x, y;
    /* generate random points and count points inside unit circle */
    long int points_in_circle = 0;
    for (long int i = 0; i < points_per_proc; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1) { points_in_circle++; }
    }

    /* reduce the counts from all the procs */
    long int total_points_in_circle;
    MPI_Reduce(&points_in_circle, &total_points_in_circle, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    /* rank:0 calculates value of pi */
    if (rank == 0) {
        return (4.0 * total_points_in_circle) / n;
    }

    ////////////////////////////////////////
    return 0.0;
}