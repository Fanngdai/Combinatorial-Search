
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
	if (amt_vertex-1 == i){
		if(a[0]<a[amt_vertex-1]) {
			// for(int j=0; j<amt_vertex; j++)
			// 	printf("%d ", a[j]);
			// printf("\n");
			process_solution(a);
		}
		return;
   }

   if(checkMax(a, i)>bandwidth)
	   return;
	for (int j = i; j<amt_vertex; j++) {
		swap(a+i,a+j);
		permute(a,i+1);
		swap(a+i,a+j);
	}
}



int main() {
	char *filename = "./Samples/g-t-13-12";
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
















// /*	What are possible elements of the next slot in the permutation?  */
// void construct_candidates(int a[], int k, int c[], int *ncandidates) {
// 	// What is not in the permutation?
// 	int in_perm[NMAX] = {0};
// 	// int in_perm[NMAX];
// 	// for (int i=1; i<amt_vertex; i++) {
// 	// 	in_perm[i] = 0;
// 	// }
//
// 	for (int i=1; i<k; i++) {
// 		in_perm[a[i]] = 1;
// 	}
//
// 	*ncandidates = 0;
// 	for(int i=1; i<=amt_vertex; i++) {
// 		if (in_perm[i] == 0) {
// 			c[(*ncandidates)++] = i;
// 		}
// 	}
// }
//
//
//
// void backtrack(int a[], int k) {
// 	// candidates for next position
//     int c[MAXCANDIDATES];
// 	// next position candidate count
//     int ncandidates;
//
//     if (k==amt_vertex) {
// 		if(a[1]<a[amt_vertex]) {
// 			process_solution(a);
// 		}
// 	} else {
// 		construct_candidates(a,++k,c,&ncandidates);
//         for(int i=0; i<ncandidates; i++) {
//             a[k] = c[i];
//         	backtrack(a,k);
//         }
//     }
// }
//
//
// char *file[77] = { "g-bt-10-9", "g-bt-11-10", "g-bt-12-11", "g-bt-127-126",
// 				"g-bt-13-12", "g-bt-14-13", "g-bt-15-14", "g-bt-16-15",
// 				"g-bt-17-16", "g-bt-18-17", "g-bt-19-18", "g-bt-20-19",
// 				"g-bt-63-62", "g-gg-100-180", "g-gg-12-17", "g-gg-15-22",
// 				"g-gg-16-24", "g-gg-18-27", "g-gg-20-31", "g-gg-24-38",
// 				"g-gg-25-40", "g-gg-28-45", "g-gg-30-49", "g-gg-33-52",
// 				"g-gg-35-58", "g-gg-36-60", "g-gg-9-12", "g-gg-91-162",
// 				"g-k-50-1225", "g-p-10-9", "g-p-100-99", "g-p-11-10",
// 				"g-p-12-11", "g-p-13-12", "g-p-14-13", "g-p-15-14",
// 				"g-p-16-15", "g-p-17-16", "g-p-18-17", "g-p-19-18",
// 				"g-p-20-19", "g-p-25-24", "g-p-30-29", "g-p-40-39",
// 				"g-p-50-49", "g-r-10-14", "g-r-10-9", "g-r-100-501",
// 				"g-r-11-15", "g-r-12-15", "g-r-13-15", "g-r-15-24",
// 				"g-r-18-46", "g-r-20-42", "g-r-25-83", "g-r-30-109",
// 				"g-r-50-301", "g-r-7-7", "g-r-8-11", "g-r-8-4", "g-r-8-6",
// 				"g-r-9-13", "g-t-10-9", "g-t-11-10", "g-t-12-11",
// 				"g-t-13-12", "g-t-14-13", "g-t-15-14", "g-t-17-16",
// 				"g-t-20-19", "g-t-25-24", "g-t-30-29", "g-t-35-34",
// 				"g-t-40-39", "g-t-7-6", "g-t-8-7","g-t-9-8"};
