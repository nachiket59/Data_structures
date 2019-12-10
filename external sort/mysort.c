#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "functions.h"

int main(int argc, char const *argv[])
{
	char *fread;
	char line[1024];
	char fname[100];
	char *buffer[BUF_SIZE];
	int i = 0, j = 0, k, fc = 0,n = 0, fcount = 0,x;
	int arg;
	char option = 'x';
	char *filenames[100];
	FILE *ftemp;
	// read from standar input
	if(argc < 2){
		FILE *newtempfile = fopen("newtempfile.txt","w+");
		char str[1024];
		while(fgets(str, 1024, stdin)){
			fputs(str, newtempfile);
		}
		filenames[0] = malloc(100 * sizeof(char));
		strcpy(filenames[0], "newtempfile.txt");
		fc ++;
		fcount ++;
		fclose(newtempfile);
		printf("\n");
	}
	//get filies and options
	else{
		for(arg = 1,fc = 0; arg < argc; arg++){
		if(argv[arg][0] != '-'){
			ftemp = fopen(argv[arg], "r");
			if(!ftemp){
				printf("Invalid file, cant open\n");
				return errno;
			}
			filenames[fc] = malloc(100 * sizeof(char));
			strcpy(filenames[fc], argv[arg]);
			fcount++;
			fc++;
		}
		else {
			if(strlen(argv[arg]) > 2){
				printf("Invalid option\n");
				return errno;
			}
			if(argv[arg][1] != 'f' && argv[arg][1] != 'n' && argv[arg][1] != 'm' && argv[arg][1] != 'r' && argv[arg][1] != 'b' && argv[arg][1] != 'd' && argv[arg][1] != 'i' && argv[arg][1] != 'u')
			{
				printf("Invalid option\n");
				return errno;
			}
			option = argv[arg][1];
		}
	}
	}
	// read from standard input
	if(fc == 0){
		FILE *newtempfile = fopen("newtempfile.txt","w+");
		char str[1024];
		while(fgets(str, 1024, stdin)){
			fputs(str, newtempfile);
		}
		filenames[0] = malloc(100 * sizeof(char));
		strcpy(filenames[0], "newtempfile.txt");
		fc ++;
		fcount ++;
		fclose(newtempfile);
		printf("\n");
	}
	// if option is m then merge and exit
	if(option == 'm'){
		FILE **m_files = malloc(fcount * sizeof(FILE*));
		for(fc = 0; fc < fcount; fc++){
			m_files[fc] = fopen(filenames[fc], "r");
		}
		mergefiles_m("total.txt", m_files, fc, option);
		system("cat total.txt");
		return 0;	
	}

	FILE *fin;
	FILE *test;
	// count lines from all files and decide no temp files to be created
	x = countLines(filenames, fcount)/BUF_SIZE;
	FILE **fout = (FILE **)malloc((x+1) * sizeof(FILE*));
	for(i = 0; i < x+1; i++){
		sprintf(fname,"out%d",i);
		fout[i] = fopen(fname,"w+");
		if(fout[i] == NULL){
			printf("error\n");
			return errno;
		}
	}
	i = 0;
	//create buffer sort and write into file
	for(fc = 0; fc < fcount; fc++) {
		fin = fopen(filenames[fc], "r");
		if(!fin){
			perror("error occured");
		}
		while(fgets(line, 1024, fin)){
			if(j >= BUF_SIZE){
				if(option != 'm')
					mergeSort(buffer, 0, j-1, option);
				n = 0;
				for(n = 0; n < j; n++){
					fprintf(fout[i],"%s", *(buffer + n));
				}
				for(n = 0; n < j; n++){
					free(buffer[n]);
				}
				i++;
				j = 0;
			}
			buffer[j] = (char*) malloc(1024 * sizeof(char));
			strcpy(buffer[j], line);
			j++;
		}
	}
	if(buffer[0]){
		if(option != 'm')
			mergeSort(buffer, 0, j-1,option);
		n = 0;
		for(n = 0; n < j; n++){
			fprintf(fout[i], "%s", *(buffer + n));
		}
		for(n = 0; n < j ; n++){
			free(buffer[n]);
		}
	}
	//merge all temp files 	
	mergefiles("total.txt", fout, i+1, option);
	//remove them
	removetempfiles(i+1);
	// check printing options -r -u
	if(option == 'u'){
		system("uniq total.txt");
	}
	else if(option == 'r'){
		system("tac total.txt");
	}
	else{
		system("cat total.txt");	
	}
	remove("newtempfile.txt");
	fclose(fin);
	remove("total.txt");
	return 0;
}




