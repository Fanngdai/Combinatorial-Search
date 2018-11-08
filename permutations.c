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

// max possible next extensions
#define MAXCANDIDATES   100
// maximum solution size
#define NMAX            100
int **edges;
int amt_vertex;
int amt_edge;
int *result;
int bandwidth;



int checkMax(int a[], int k){
	int max = 0;
	for(int e = 0; e < amt_edge; e++) {
		int index = -1;
		int one = edges[e][0];
		int two = edges[e][1];

		for(int i=0; i<k; i++) {
			if(index!=-1 && (a[i]==one || a[i]==two)) {
				int tempMax = abs(index-i);
				if(tempMax > bandwidth) {
					return tempMax;
				} else if(tempMax > max) {
					max = tempMax;
				}
				break;
			} else if(a[i]==one || a[i]==two) {
				index = i;
			}
		}
	}
	return max;
}



void process_solution(int a[]) {
	int max = checkMax(a, amt_vertex);
	if(max < bandwidth) {
		memcpy(result, a, (amt_vertex)*sizeof(int));
		bandwidth = max;
	}
}



void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}



void permute(int *a,int i) {
	if (amt_vertex == i){
		if(a[0]<a[amt_vertex-1]) {
			// for(int j=0; j<amt_vertex; j++)
			// 	printf("%d ", a[j]);
			// printf("\n");
			process_solution(a);
		}
		return;
   }

	for (int j = i; j<amt_vertex; j++) {
		swap(a+i,a+j);
		if(checkMax(a, j)>bandwidth)
			return;
		permute(a,i+1);
		swap(a+i,a+j);
	}
}



int main() {
	char *filename = "./Samples/g-bt-10-9";
	FILE *file = fopen(filename, "r");
	if(file == NULL)
		exit(0);

	fscanf(file, "%d\n%d", &amt_vertex, &amt_edge);
	// printf("%d\n%d\n", amt_vertex, amt_edge);
	// printf("%d\n", amt_edge);

	result = (int *)malloc(amt_vertex* sizeof(int));
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

	int a[amt_vertex];
	for(int i=0; i<amt_vertex; i++)
		a[i] = i+1;
	clock_t start, end;
	start = clock();
	permute(a, 0);
	// backtrack(a,0);
	end = clock();

	printf("Filename: %s\n", filename);
	printf("Max size: %d\n", bandwidth);
	for(int i=0; i<amt_vertex; i++) {
		printf("%d ", result[i]);
	}
	printf("\n");

	fclose(file);

	// free(edges);
	// free(result);
   	printf("Total time taken by CPU: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
}

















/*	What are possible elements of the next slot in the permutation?  */
void construct_candidates(int a[], int k, int c[], int *ncandidates) {
	// What is not in the permutation?
	int in_perm[NMAX] = {0};
	// int in_perm[NMAX];
	// for (int i=1; i<amt_vertex; i++) {
	// 	in_perm[i] = 0;
	// }

	for (int i=1; i<k; i++) {
		in_perm[a[i]] = 1;
	}

	*ncandidates = 0;
	for(int i=1; i<=amt_vertex; i++) {
		if (in_perm[i] == 0) {
			c[(*ncandidates)++] = i;
		}
	}
}



void backtrack(int a[], int k) {
	// candidates for next position
    int c[MAXCANDIDATES];
	// next position candidate count
    int ncandidates;

    if (k==amt_vertex) {
		if(a[1]<a[amt_vertex]) {
			process_solution(a);
		}
	} else {
		construct_candidates(a,++k,c,&ncandidates);
        for(int i=0; i<ncandidates; i++) {
            a[k] = c[i];
        	backtrack(a,k);
        }
    }
}
