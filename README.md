# matrix-multiplication-openMP

## Problem: 
The task is to develop an efficient algorithm for matrix multiplication using OpenMP libraries. The efficiency of the program is calculated based on the execution time.

## Solution:
The register blocking approach is used to calculate the matrix multiplication of large dimensions more efficiently. The program is written in C programming language using OpenMP libraries to get more optimized result. OpenMP libraries are used because it supports multiprocessing. It creates parallel threads in the program and executes a block or single line of code. The libraries are imported by defining a header of omp.h which contains all the required threading definitions. The register blocking approach is used because it mainly optimizes memory bandwidth and thus, does not waste memory blocks as similar to naïve approach. The program is compiled and run using Cygwin application having gcc compiler tools installed in it.

## Algorithm:
1.	Declare total dimensions (N) of square matrix.
2.	Create two input matrices as A and B having N dimensions and assigned values which are generated using rand () function.
3.	Set Number_of_Threads: = 1 to 4 
4.	Calculate matrix multiplication time using parallel block execution. Create a single dimension vectors for both input matrix. Construct a parallel pragma as
 
5.	Calculate matrix multiplication time using sequential execution.
6.	Repeat. Go to Step 3.
