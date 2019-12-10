#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
//remove blanks from front and then compare
int strcmp_b(char *s1, char *s2){
	int i = 0,j = 0;
	int diff;
	while(s1[i] == ' ' || s1[i] == '\t'){
		i++;
	}
	while(s2[j] == ' ' || s2[j] == '\t'){
		j++;
	}
	return strcmp(s1+i, s2+j);
}
// if a character is not alphanumeric or spaces skip if two strings are entirely non alphanumeric then use normal strcmp
int strcmp_d(char *s1, char *s2){
	int i = 0, j = 0;
	int ch1, ch2;
	int s1valid = 0, s2valid = 0;
	int diff = INT_MIN;
	while(s1[i] && s2[j]){
		ch1 = (int)s1[i]; 
		if(ch1 == 32 || ch1 == 9 || (ch1 >=48 && ch1 <= 57) || (ch1 >= 97 && ch1 <= 122) || (ch1 >=65 && ch1 <=90)){
			s1valid = 1;
			ch2 = (int)s2[j];
			if(ch2 == 32 || ch2 == 9 || (ch2 >=48 && ch2 <= 57) || (ch2 >= 97 && ch2 <= 122) || (ch2 >=65 && ch2 <=90)){
				s2valid = 1;
				diff = ch1 - ch2;
				if(diff != 0 && diff != INT_MIN){
					return diff;
				}
				i++; j++;
			}
			else{
				j++;
			}
		}
		else{
			i++;
		}
	}
	int k = i, l= j;
	while(s1[k]){
		ch1 = (int)s1[k++]; 
		if(ch1 == 32 || ch1 == 9 || (ch1 >=48 && ch1 <= 57) || (ch1 >= 97 && ch1 <= 122) || (ch1 >=65 && ch1 <=90)){
			s1valid = 1;
		}	
	}
	while(s2[l]){
		ch2 = (int)s2[l++];
		if(ch2 == 32 || ch2 == 9 || (ch2 >=48 && ch2 <= 57) || (ch2 >= 97 && ch2 <= 122) || (ch2 >=65 && ch2 <=90)){
			s2valid = 1;
		}		
	}
	if(s1valid ==0 && s2valid == 0){
		return strcmp(s1,s2);
	}
	if(!s1[i] && diff == INT_MIN){
		return -1;
	}
	if(!s2[j] && diff == INT_MIN){
		return 1;
	}
	return diff;
}
// if a charachter is non printable then skip and move to next then compare
int strcmp_i(char *s1, char *s2){
	int i = 0, j = 0;
	int ch1, ch2;
	int diff = INT_MIN;
	while(s1[i] && s2[j]){
		ch1 = (int)s1[i]; 
		if(ch1 >= 31 && ch1 <= 255){
			ch2 = (int)s2[j];
			if(ch2 >= 31 && ch2 <= 255){
				diff = ch1 - ch2;
				if(diff != 0 && diff != INT_MIN){
					return diff;
				}
				i++; j++;
			}
			else{
				j++;
			}
		}
		else{
			i++;
		}
	}
	if(!s1[i] && diff == INT_MIN){
		return -1;
	}
	if(!s2[j] && diff == INT_MIN){
		return 1;
	}
	return diff;
}
// converts string into long double and then sorts if both strings are 
// cant be a double it compares them by simple strcmp
long double strcmp_n(char *s1, char *s2){
	char *endptr,*endptr1;
	long double val, val2;
	 	  errno = 0;    /* To distinguish success/failure after call */
          val = strtold(s1, &endptr);
          if ((errno == ERANGE && (val == LDBL_MAX || val == LDBL_MIN))
                  || (errno != 0 && val == 0)) {
          	return -1;
          }
          val2 =  strtold(s2, &endptr1);
          if ((errno == ERANGE && (val2 == LDBL_MAX || val2 == LDBL_MIN))
                  || (errno != 0 && val2 == 0)) {
          	return 1;
          }
          if (endptr1 == s2 && endptr == s1) {
              return strcmp(s1,s2);
          }
          if (endptr == s1) {
              return -1;
          }
          if (endptr == s2) {
              return 1;
          }
          return val - val2;
}

