int getMinElement(char *arr[], int size);
void leftshift(char* arr[], FILE *f[], int index, int n);
void mergefiles(char *outfile, FILE **fin, int n, char option);
void mergefiles_m(char *outfile, FILE **fin, int n, char option);
void bufferSort(char *buffer[], int n);
int countLines(char *filenames[],int n);
int removetempfiles(int n);
void mergeSort(char* arr[], int l, int r, char option);
void merge(char *arr[], int i1, int j1, int i2, int j2);

int getMinElement_b(char *arr[], int size);
void merge_b(char *arr[], int i1, int j1, int i2, int j2);

int getMinElement_d(char *arr[], int size);
void merge_d(char *arr[], int i1, int j1, int i2, int j2);

int getMinElement_i(char *arr[], int size);
void merge_i(char *arr[], int i1, int j1, int i2, int j2);

int getMinElement_n(char *arr[], int size);
void merge_n(char *arr[], int i1, int j1, int i2, int j2);

int getMinElement_r(char *arr[], int size);
void merge_r(char *arr[], int i1, int j1, int i2, int j2);

int getMinElement_f(char *arr[], int size);
void merge_f(char *arr[], int i1, int j1, int i2, int j2);
#define BUF_SIZE 512000

