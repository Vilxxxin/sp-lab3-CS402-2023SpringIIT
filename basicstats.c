#include <stdio.h>
#include <stdlib.h>



//create a getMean function
float getMean(float* data, int n){
    float sum =0;
    for(int i=0; i<n; i++){
        sum += data[i];
    }
    return sum/n;
}

//create a getMedian function
float getMedian(float* data, int n){
    float median;
    if (n % 2 == 0) {
        median = (data[n/2 - 1] + data[n/2]) / 2;
    } else {
        median = data[n/2];
    }
    return median;
}

//create a getStddev function
float getStddev(float* data, int n, float mean){
    float sumOfSquares, stddev;
    for (int i=0; i<n;i++){
        sumOfSquares += pow(data[i]- mean, 2);
    }
    stddev = sqrt(sumOfSquares / n);
    return stddev;
}


int main()
{
    FILE *fp;
    char filename[50];
    printf("Enter the input file's name: \n");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL){
        fprintf(stderr, "\nError in opening file\n");
        exit(1);
    }

    //read data from the input file;
    int capacity = 10;
    float* data = (float*) malloc(capacity * sizeof(float));
    int count =0;
    float x;
    while(fscanf(fp,"%f",&x)==1){
        if(count == capacity){
            capacity *= 2;
            data = (float*)  realloc(data, capacity * sizeof(float));//
        }
        data[count] = x;
        count++;
    }
    fclose(fp);
    //sort the array
    selectionSort(data, count);

    //declare statics result
    float mean, median, stddev;
    mean = getMean(data,  count);
    median = getMedian(data, count);
    stddev = getStddev(data, count, mean);


    // print the results
    printf("Results:\n");
    printf("--------\n");
    printf("Num values: \t%d\n", count);
    printf("      mean: \t%.3f\n", mean);
    printf("    median: \t%.3f\n", median);
    printf("    stddev: \t%.3f\n", stddev);
    printf("Unused array capacity: %d", capacity - count);

    // free the memory allocated for the data array
    free(data);

    return 0;


}


//create a function to compare the data
void selectionSort(float* data, int n){
    int i, j, minIndex;
    float temp;

    for (i = 0; i < n-1; i++) {
        minIndex = i;
        for (j = i+1; j < n; j++) {
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            temp = data[i];
            data[i] = data[minIndex];
            data[minIndex] = temp;
        }
    }
}


