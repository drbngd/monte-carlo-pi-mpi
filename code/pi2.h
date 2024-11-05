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

//    double start_time, end_time;

    // Start timing for seeding
//    start_time = MPI_Wtime();
    /* seed uniquely for rank */
//    srand(time(NULL) + rank);
//    end_time = MPI_Wtime();
//    std::cout << "Rank " << rank << ": Seeding time = " << end_time - start_time << " seconds" << std::endl;

    // Start timing for point calculation
//    start_time = MPI_Wtime();
    /* calculate # points for each processor */
    long int points_per_proc = n / p;
    long int remainder = n % p;
    if (rank < remainder) { points_per_proc++; }
//    printf("Rank %d: Points per proc = %ld\n", rank, points_per_proc);
//    end_time = MPI_Wtime();
//    std::cout << "Rank " << rank << ": Point calculation time = " << end_time - start_time << " seconds" << std::endl;

    // Start timing for point generation and counting
//    start_time = MPI_Wtime();
    double x, y;
    /* generate random points and count points inside unit circle */
    long int points_in_circle = 0;
    for (long int i = 0; i < points_per_proc; i++) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        if (x * x + y * y <= 1) { points_in_circle++; }
    }
//    end_time = MPI_Wtime();
//    std::cout << "Rank " << rank << ": Point generation and counting time = " << end_time - start_time << " seconds" << std::endl;

    // Start timing for reduction
//    start_time = MPI_Wtime();
    /* reduce the counts from all the procs */
    long int total_points_in_circle;
    MPI_Reduce(&points_in_circle, &total_points_in_circle, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
//    end_time = MPI_Wtime();
//    std::cout << "Rank " << rank << ": Reduction time = " << end_time - start_time << " seconds" << std::endl;

    /* rank:0 calculates value of pi */
    if (rank == 0) {
        return (4.0 * total_points_in_circle) / n;
    }

    ////////////////////////////////////////
    return 0.0;
}