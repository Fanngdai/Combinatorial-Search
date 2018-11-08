
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

int **edges;
int amt_vertex;
int amt_edge;
int *result;
int bandwidth;
int min;

/*
 * Checks for the max bandwidth in this permutation
 *
 * Loops through the edges and checks in the permutation to find the distance
 * using the difference of index of the 2 verties. What you do first is find the
 * first value of the two and keep it as an index. Then, you look for the second
 * value of the edge and take the difference. If the difference is grreater than
 * the bandwidth, we would return immediately! We only want to find a smaller
 * bandwidth. We will continue until we have a bandwidth of less than or equal
 * to what we originally had.
 */
int checkMax(int a[], int k){
	int max = 0;
	for(int e = 0; e < amt_edge; e++) {
		int index = -1;
		int one = edges[e][0];
		int two = edges[e][1];

		for(int i=0; i<k; i++) {
			if(index!=-1 && (a[i]==one || a[i]==two)) {
				int tempMax = abs(index-i);
				// Optimization
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

/*
 * Gets the max bandwidth of the current permutation and compare it with the
 * minimum bandwidth which we previous got. If the current bandwidth is smaller
 * than what we have, we will replace the result permutation along with a record
 * of the new min bandwidth.
 *
 * You get the bandwidth of the current permutation and compare it to the
 * previous. We want the smaller bandwidth therefore, if the current bandwidth
 * is less than, we replace the bandwidth with this permutation.
 */
void process_solution(int a[]) {
	int max = checkMax(a, amt_vertex);
	if(max < bandwidth) {
		memcpy(result, a, (amt_vertex)*sizeof(int));
		bandwidth = max;
	}
}

/*
 * This function swaps the values of the two integer addresses.
 */
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
 * Creates all the permutations. (Look at getMin() for the first Optimization)
 * If we have a complete set, we will first check to see if this value was
 * already used.
 * A value (permutation) was already used if the last element is
 * greater than the first element. Notice 123 is the same as 321. If we use 123,
 * 321 will be eliminated. Note how the first index is greater than the last
 * index. This will cut half the amount of time to process_solution.
 * If the set is not complete, I first checked to see if the the subset we have
 * have a bandwidth which is greater than the bandwidth we already have. Since
 * we are searching for a smaller bandwidth, if the subset has a greater
 * bandwidth, we would stop this subset from continuing and move to another
 * subset.
 *
 */
void permute(int *a,int i) {
	// Optimization - look at getMin()
	if(bandwidth==min)
		return;
	else if (amt_vertex-1 == i){
		// Optimization
		if(a[0]<a[amt_vertex-1]) {
			process_solution(a);
		}
		return;
   }

	// Optimization
   if(checkMax(a, i)>bandwidth)
	   return;
	for (int j = i; j<amt_vertex; j++) {
		swap(a+i,a+j);
		permute(a,i+1);
		swap(a+i,a+j);
	}
}

/*
 * I noticed that if a vertex is adjacent to x amount of vertex, then the max
 * bandwidth would be x/2. I searched for the vertex with the most amount of
 * degree. The value which I get (x/2) is the minimum value the bandwidth can
 * be.
 */
void getMin() {
	int vals[amt_vertex];
	for(int i=0; i<amt_vertex; i++)
		vals[i]=0;
	for(int i=0; i<amt_edge; i++) {
		int one = edges[i][0];
		int two = edges[i][1];
		vals[one-1]++;
		vals[two-1]++;
	}
	min = 0;
	for(int i=0; i<amt_vertex; i++) {
		printf("%d ", vals[i]);
		if(vals[i]>min)
			min = vals[i];
	}
	min += 1;
	min /= 2;
}

/*
 * I do not calculate the time I spent reading the file and setting up my
 * program since there are many ways of doing it such as hardcoding. Since
 * everyone did it differently and some can be O(1) time, I chose to leave it
 * out. My edges are in a 2d array which always has a column of 2 and a row of
 * the amount of edges.
 */
int main() {
	char *filename = "./Samples/g-t-8-7";
	FILE *file = fopen(filename, "r");
	if(file == NULL)
		exit(0);

	fscanf(file, "%d\n%d", &amt_vertex, &amt_edge);
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
    }

	int a[amt_vertex];
	for(int i=0; i<amt_vertex; i++)
		a[i] = i+1;
	clock_t start, end;
	start = clock();
	getMin();
	permute(a, 0);
	end = clock();

	printf("Filename: %s\n", filename);
	printf("Max size: %d\n", bandwidth);
	for(int i=0; i<amt_vertex; i++) {
		printf("%d ", result[i]);
	}
	printf("\nTotal time taken by CPU: %f\n", (double)(end-start)/CLOCKS_PER_SEC);

	fclose(file);
	free(edges);
	free(result);
}
