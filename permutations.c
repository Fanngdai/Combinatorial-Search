/*	permutations.c

	Construct all permutations via backtracking.

	by: Steven Skiena
	begun: March 27, 2002
*/
/*
Copyright 2003 by Steven S. Skiena; all rights reserved.

Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

This program appears in my book:

"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.

See our website www.programming-challenges.com for additional information.

This book can be ordered from Amazon.com at

http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define TRUE    1
#define FALSE   0
typedef int bool;

// max possible next extensions
#define MAXCANDIDATES   100
// maximum solution size
#define NMAX            100
int **edges;
int amt_vertex;
int amt_edge;
int *result;
int bandwidth;
// found all solutions yet?
bool finished = FALSE;



void process_solution(int a[], int k) {
	int max = 0;
	for(int e = 0; e < amt_edge; e++) {
		int index = -1;
		int one = edges[e][0];
		int two = edges[e][1];
		for(int i=1; i<=k; i++) {
			if(index!=-1 && (a[i]==one || a[i]==two)) {
				// printf("###%d\t%d\t%d\n", index, i, abs(index-i));
				if(abs(index-i) > max) {
					max = abs(index-i);
				}
				break;
			} else if(a[i]==one || a[i]==two) {
				index = i;
			}
		}
	}

	if(max < bandwidth) {
		memcpy(result, a, (amt_vertex+1)*sizeof(int));
		// result = a;
		bandwidth = max;

		// for(int i=1; i<=amt_vertex; i++)
		// 	printf("%d\n", result[i]);
		// printf("\n\n");
	}
}



/*	What are possible elements of the next slot in the permutation?  */
void construct_candidates(int a[], int k, int n, int c[], int *ncandidates) {
	// counter
	int i;
	// What is not in the permutation?
	bool in_perm[NMAX];

	for (i=1; i<NMAX; i++)
		in_perm[i] = FALSE;
	for (i=1; i<k; i++)
		in_perm[a[i]] = TRUE;

	*ncandidates = 0;
	for (i=1; i<=n; i++)
		if (in_perm[i] == FALSE) {
			c[ *ncandidates] = i;
			*ncandidates = *ncandidates + 1;
		}
}



void backtrack(int a[], int k, int input) {
	// candidates for next position
    int c[MAXCANDIDATES];
	// next position candidate count
    int ncandidates;

    if (k==input) {
        process_solution(a,k);
	} else {
        k = k+1;
        construct_candidates(a,k,input,c,&ncandidates);
        for(int i=0; i<ncandidates; i++) {
            a[k] = c[i];
            backtrack(a,k,input);
			if(finished)
				return;	/* terminate early */
        }
    }

}



int main() {
	clock_t start, end;
	FILE *file = fopen("./Samples/g-bt-10-9", "r");

	fscanf(file, "%d\n%d", &amt_vertex, &amt_edge);
	// printf("%d\n%d\n", amt_vertex, amt_edge);
	// printf("%d\n", amt_edge);
	result = (int *)malloc(amt_vertex * sizeof(int));
	edges = (int **)malloc(amt_edge*sizeof(int *));
	for(int i=0; i<amt_edge; i++)
		edges[i] = (int *)malloc(2 * sizeof(int));
	bandwidth = INT_MAX;

	int temp_amt_edge = 0;
  	while(temp_amt_edge != amt_edge) {
		int temp_from;
		int temp_to;
      	int temp = fscanf(file, "%d %d", &temp_from, &temp_to);
		// If there are 2 numbers
		if(temp == 2){
			edges[temp_amt_edge][0] = temp_from;
			edges[temp_amt_edge][1] = temp_to;
		}
		temp_amt_edge++;
	  	// printf ("%d %d\n", amt_vertex, amt_edge);
		// make sure the values are not ""
    }

	start = clock();
	int a[amt_vertex];
	backtrack(a,0,amt_vertex);
	end = clock();

	printf("Max size:\t%d\n", bandwidth);
	for(int i=1; i<=amt_vertex; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");

	fclose(file);

	// free(edges);
	// free(result);
   	printf("Total time taken by CPU: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
}
