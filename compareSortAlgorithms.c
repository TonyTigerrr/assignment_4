#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;
// swap function assists with bubbleSort and selectionSort
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}
// merge function assists with mergeSort
void merge(int pData[], int leftIndex, int midIndex, int rightIndex) {
	int i = 0, j = 0, k = leftIndex;
    int newIndex1 = midIndex - leftIndex + 1,
        newIndex2 = rightIndex - midIndex;
    int *array1 = (int*)malloc(newIndex1*sizeof(int));
	int *array2 = (int*)malloc(newIndex2*sizeof(int));
	extraMemoryAllocated += newIndex1 * sizeof(int) + newIndex2 * sizeof(int);
        array2[newIndex2];
    for(int i=0; i<newIndex1; i++)
        array1[i] = pData[leftIndex+i];
    for(int j=0; j<newIndex2; j++)
        array2[j] = pData[midIndex+1+j];
    while(i<newIndex1&&j<newIndex2){
        if(array1[i]<=array2[j]){
            pData[k] = array1[i];
            i++;
        }else{
            pData[k] = array2[j];
            j++;
        }
        k++;
    }
    while(i<newIndex1){
        pData[k] = array1[i];
        i++;
        k++;
    }
    while(j<newIndex2){
        pData[k] = array2[j];
        j++;
        k++;
    }
}
// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	extraMemoryAllocated = 0;
	if(l<r){
        int midIndex = l + (r - l) / 2;
        mergeSort(pData, l, midIndex);
        mergeSort(pData, midIndex+1, r);
        merge(pData, l, midIndex, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int element, j;
	extraMemoryAllocated = 0;
    for(int i=1; i<n; i++){
        element = pData[i];
        j = i - 1;
        while(j>=0&&pData[j]>element) {
            pData[j+1] = pData[j];
            j -= 1;
        }
        pData[j+1] = element;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	extraMemoryAllocated = 0;
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(pData[j]>pData[j+1])
                swap(&pData[j], &pData[j+1]);
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int minIndex;
	extraMemoryAllocated = 0;
    for(int i=0; i<n-1; i++){
        minIndex = i;
        for(int j=i+1; j<n; j++)
            if(pData[minIndex]>pData[j])
                minIndex = j;
            if(minIndex!=i)
                swap(&pData[minIndex], &pData[i]);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		for(int i=0; i<dataSz; i++){
           fscanf(inFile, "%d\n", &((*ppData)[i]));
		}
	}

	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");

	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};

	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);

		if (dataSz <= 0)
			continue;

		pDataCopy = (int *)malloc(sizeof(int)*dataSz);

		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");

		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		free(pDataCopy);
		free(pDataSrc);
	}

}