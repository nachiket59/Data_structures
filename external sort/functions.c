#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "options.h"
// find index of minimum element
int getMinElement(char *arr[], int size){
	int i, j = 0;
	int index;
	for(i = 1; i < size; i++){
		if(strcmp(arr[j],arr[i]) > 0)
			j = i;
	}
	index = j;
	return index;
}

int getMinElement_b(char *arr[], int size){
	int i, j = 0;
	int index;
	for(i = 1; i < size; i++){
		if(strcmp_b(arr[j],arr[i]) > 0)
			j = i;
	}
	index = j;
	return index;
}

int getMinElement_d(char *arr[], int size){
	int i, j = 0;
	int index;
	for(i = 1; i < size; i++){
		if(strcmp_d(arr[j],arr[i]) > 0)
			j = i;
	}
	index = j;
	return index;
}

int getMinElement_i(char *arr[], int size){
	int i, j = 0;
	int index;
	for(i = 1; i < size; i++){
		if(strcmp_i(arr[j],arr[i]) > 0)
			j = i;
	}
	index = j;
	return index;
}

int getMinElement_n(char *arr[], int size){
	int i, j = 0;
	int index;
	for(i = 1; i < size; i++){
		if(strcmp_n(arr[j],arr[i]) > 0)
			j = i;
	}
	index = j;
	return index;
}
int getMinElement_r(char *arr[], int size){
	int i, j = 0;
	int index;
	for(i = 1; i < size; i++){
		if(strcmp_n(arr[j],arr[i]) < 0)
			j = i;
	}
	index = j;
	return index;
}
int getMinElement_f(char *arr[], int size){
	int i, j = 0;
	int index;
	for(i = 1; i < size; i++){
		if(strcasecmp(arr[j],arr[i]) < 0)
			j = i;
	}
	index = j;
	return index;
}
// left shift char array and file pointer array to specified index by n
void leftshift(char* arr[], FILE *f[], int index, int n){
	int i, j;
	char *temp1;
	FILE *temp2;
	temp1 = arr[index];
	temp2 = f[index];
	for(i = index; i < n - 1; i++ ){
		arr[i] = arr[i + 1];
		f[i] = f[i + 1];
	}
	free(temp1);// arr is malloced memory being freed here.
	free(temp2);
}
// merges files from file pointers array according to option and writes into output file.
void mergefiles(char *outfile, FILE **fin, int n, char option){
	FILE *outf = fopen(outfile, "w");
	if(!outf){
		printf("Cant create output file\n");
		exit(0);
	}
	char **arr = malloc(n * sizeof(char *));
	int i, min_index;
	char line[1024];
	char *fread;
	char fname[10];
	for(i = 0; i < n; i++){
		rewind(fin[i]);
	}
	for(i = 0; i < n; i++){
		arr[i] = malloc(1024 * sizeof(char));
		fread = fgets(arr[i], 1024, fin[i]);
	}
	while(n > 0){
		switch(option){
  			case 'x':
        		min_index = getMinElement(arr, n);
        		break;
        	case 'b':
        		min_index = getMinElement_b(arr, n);
        		break;
        	case 'd':
        		min_index = getMinElement_d(arr, n);
        		break;
        	case 'i':
        		min_index = getMinElement_i(arr, n);
        		break;
        	case 'n':
        		min_index = getMinElement_n(arr, n);
        		break;
        	default:
        		min_index = getMinElement(arr, n);		 
  		}
		fprintf(outf, "%s", arr[min_index]);
		fread = fgets(arr[min_index], 1024, fin[min_index]);
		if(fread == NULL){
			
			leftshift(arr, fin, min_index, n);
			n --;
		}
	}
	fclose(outf);
}

void mergefiles_m(char *outfile, FILE **fin, int n, char option){
	FILE *outf = fopen(outfile, "w");
	if(!outf){
		printf("Cant create output file\n");
		exit(0);
	}
	char **arr = malloc(n * sizeof(char *));
	int i, min_index;
	char line[1024];
	char *fread;
	char fname[10];
	for(i = 0; i < n; i++){
		rewind(fin[i]);
	}
	for(i = 0; i < n; i++){
		arr[i] = malloc(1024 * sizeof(char));
		fread = fgets(arr[i], 1024, fin[i]);
	}
	while(n > 0){
		switch(option){
  			case 'x':
        		min_index = getMinElement(arr, n);
        		break;
        	case 'b':
        		min_index = getMinElement_b(arr, n);
        		break;
        	case 'd':
        		min_index = getMinElement_d(arr, n);
        		break;
        	case 'i':
        		min_index = getMinElement_i(arr, n);
        		break;
        	case 'n':
        		min_index = getMinElement_n(arr, n);
        		break;
        	case 'f':
        		min_index = getMinElement_f(arr, n);
        		break;	
        	default:
        		min_index = getMinElement(arr, n);		 
  		}
		fprintf(outf, "%s", arr[min_index]);
		fread = fgets(arr[min_index], 1024, fin[min_index]);
		if(fread == NULL){
			
			leftshift(arr, fin, min_index, n);
			n --;
		}
	}
	fclose(outf);
}

// counts lines from all the files in given array
int countLines(char *filenames[], int n){
	char line[1024];
	int i, count = 0;
	FILE *f;
	for(i = 0; i < n; i++){
		f = fopen(filenames[i], "r");
		while(fgets(line, 1024, f)){
			count ++;
		}
	}
	return count;
}
// removes n number of temperory files created
int removetempfiles(int n){
	int i;
	int flag = 1;
	char fname[50];
	for(i = 0; i < n; i++){
		sprintf(fname,"out%d",i);
		if(remove(fname) != 0)
			flag = 0;
	}
	return flag;
}
// sorts array of strings according to option.
void mergeSort(char* arr[], int l, int r, char option) 
{ 
    if (l < r) { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 
        // Sort first and second halves 
        mergeSort(arr, l, m, option); 
        mergeSort(arr, m+1, r, option); 
  		switch(option){
  			case 'x':
        		merge(arr, l, m, m+1, r);
        		break;
        	case 'b':
        		merge_b(arr, l, m, m+1, r);
        		break;
        	case 'd':
        		merge_d(arr, l, m, m+1, r);
        		break;
        	case 'i':
        		merge_i(arr, l, m, m+1, r);
        		break;
        	case 'n':
        		merge_n(arr, l, m, m+1, r);
        		break;
        	case 'f':
        		merge_f(arr, l, m, m+1, r);
        		break;		
        	default:
        		merge(arr, l, m, m+1, r);		 
  		}
    } 
}
void merge(char *arr[], int i1, int j1, int i2, int j2){
	char *temp[BUF_SIZE];
	int i,j,k;
	i= i1;
	j= i2;
	k = 0;
	while(i <= j1 && j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		if(strcmp(arr[i], arr[j]) <= 0){
			strcpy(temp[k++],arr[i++]);
		}
		else{
			strcpy(temp[k++],arr[j++]);
		}
	}
	while(i<=j1){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[i++]);
	}
	while(j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[j++]);
	}
	for(i=i1,j=0; i<=j2; i++,j++){
		strcpy(arr[i],temp[j]);
		free(temp[j]);
	}
}

void merge_b(char *arr[], int i1, int j1, int i2, int j2){
	char *temp[BUF_SIZE];
	int i,j,k;
	i= i1;
	j= i2;
	k = 0;
	while(i <= j1 && j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		if(strcmp_b(arr[i], arr[j]) <= 0){
			strcpy(temp[k++],arr[i++]);
		}
		else{
			strcpy(temp[k++],arr[j++]);
		}
	}
	while(i<=j1){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[i++]);
	}
	while(j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[j++]);
	}
	for(i=i1,j=0; i<=j2; i++,j++){
		strcpy(arr[i],temp[j]);
		free(temp[j]);
	}
}

void merge_d(char *arr[], int i1, int j1, int i2, int j2){
	char *temp[BUF_SIZE];
	int i,j,k;
	i= i1;
	j= i2;
	k = 0;
	while(i <= j1 && j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		if(strcmp_d(arr[i], arr[j]) <= 0){
			strcpy(temp[k++],arr[i++]);
		}
		else{
			strcpy(temp[k++],arr[j++]);
		}
	}
	while(i<=j1){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[i++]);
	}
	while(j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[j++]);
	}
	for(i=i1,j=0; i<=j2; i++,j++){
		strcpy(arr[i],temp[j]);
		free(temp[j]);
	}
}

void merge_i(char *arr[], int i1, int j1, int i2, int j2){
	char *temp[BUF_SIZE];
	int i,j,k;
	i= i1;
	j= i2;
	k = 0;
	while(i <= j1 && j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		if(strcmp_i(arr[i], arr[j]) <= 0){
			strcpy(temp[k++],arr[i++]);
		}
		else{
			strcpy(temp[k++],arr[j++]);
		}
	}
	while(i<=j1){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[i++]);
	}
	while(j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[j++]);
	}
	for(i=i1,j=0; i<=j2; i++,j++){
		strcpy(arr[i],temp[j]);
		free(temp[j]);
	}
}

void merge_n(char *arr[], int i1, int j1, int i2, int j2){
	char *temp[BUF_SIZE];
	int i,j,k;
	i= i1;
	j= i2;
	k = 0;
	while(i <= j1 && j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		if(strcmp_n(arr[i], arr[j]) < 0){
			strcpy(temp[k++],arr[i++]);
		}
		else{
			strcpy(temp[k++],arr[j++]);
		}
	}
	while(i<=j1){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[i++]);
	}
	while(j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[j++]);
	}
	for(i=i1,j=0; i<=j2; i++,j++){
		strcpy(arr[i],temp[j]);
		free(temp[j]);
	}
}

void merge_r(char *arr[], int i1, int j1, int i2, int j2){
	char *temp[BUF_SIZE];
	int i,j,k;
	i= i1;
	j= i2;
	k = 0;
	while(i <= j1 && j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		if(strcmp_n(arr[i], arr[j]) >= 0){
			strcpy(temp[k++],arr[i++]);
		}
		else{
			strcpy(temp[k++],arr[j++]);
		}
	}
	while(i<=j1){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[i++]);
	}
	while(j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[j++]);
	}
	for(i=i1,j=0; i<=j2; i++,j++){
		strcpy(arr[i],temp[j]);
		free(temp[j]);
	}
}

void merge_f(char *arr[], int i1, int j1, int i2, int j2){
	char *temp[BUF_SIZE];
	int i,j,k;
	i= i1;
	j= i2;
	k = 0;
	while(i <= j1 && j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		if(strcasecmp(arr[i], arr[j]) <= 0){
			strcpy(temp[k++],arr[i++]);
		}
		else{
			strcpy(temp[k++],arr[j++]);
		}
	}
	while(i<=j1){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[i++]);
	}
	while(j<=j2){
		temp[k] = malloc(1024*sizeof(char));
		strcpy(temp[k++],arr[j++]);
	}
	for(i=i1,j=0; i<=j2; i++,j++){
		strcpy(arr[i],temp[j]);
		free(temp[j]);
	}
}
