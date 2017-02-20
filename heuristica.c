#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
long int get_max(long int a[], long int num_elements){
   long int i, max= a[0];
   for (i=0; i<num_elements; i++)
   {
  if (a[i]>max)
  {
     max=a[i];
  }
   }
   return(max);
}
long int get_min(long int a[], long int num_elements){
   long int i, min= a[0];
   for (i=0; i<num_elements; i++)
   {
  if (a[i]<min)
  {
     min=a[i];
  }
   }
   return(min);
}

void quick(long int * v, long int inicio, long int fim){
	long int i, j, pivo, aux;
	i = inicio;
	j = fim;
	pivo = v[(inicio + fim)/2];
	while(i<j){
		while(v[i] < pivo) 
			i++;
		while(v[j] > pivo) 
			j--;
		if(i <= j){
			aux = v[i];
			v[i++] = v[j];
			v[j--] = aux;
		}
	}
	if(j > inicio) 
		quick(v, inicio, j);
	if(i < fim) 
		quick(v, i, fim);

	return;
}


void counting(long int arr[], long int size , long int range){
	long int min ;

	min = get_min(arr, size);
	//printf(" %ld \n" , min);

	long int output[size];
	long int i;
	long int count[range + 1];

	for(i = 0 ; i <size ; i++)
		arr[i] = arr[i] - min ;
	memset(count, 0, sizeof(count));


	for(i = 0; i< size; ++i)
		++count[arr[i]];

	for (i = 1; i <= range; ++i)
		count[i] += count[i-1];

	for (i = 0; i < size; ++i){
        	output[count[arr[i]]-1] = arr[i];
        	--count[arr[i]];
    	}
  
	for (i = 0; i<size; ++i){
        	arr[i] = output[i]+ min;
	}
}

void swapStrings( char **a, char **b){
	char *temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void radixSortInternal(int n, char **a, int k){
	int i;
	int count[UCHAR_MAX+1];  
	int mode;               
	char **bucket[UCHAR_MAX+1]; 
	char **top[UCHAR_MAX+1];
	while(n > 1) {
		memset(count, 0, sizeof(int)*(UCHAR_MAX+1));
	for(i = 0; i < n; i++) {
		count[(unsigned char) a[i][k]]++;
	}

		mode = 1;
	for(i = 2; i < UCHAR_MAX+1; i++) {
		if(count[i] > count[mode]) {
		mode = i;
		}
	}
	if(count[mode] < n) {
		bucket[0] = top[0] = a;
		for(i = 1; i < UCHAR_MAX+1; i++) {
			top[i] = bucket[i] = bucket[i-1] + count[i-1];
		}

		for(i = 0; i < UCHAR_MAX+1; i++) {
			while(top[i] < bucket[i] + count[i]) {
				if((unsigned char) top[i][0][k] == i) {
					top[i]++;
				} else {
					swapStrings(top[i], top[(unsigned char) top[i][0][k]]++);
				}
			}
		}
		for(i = 1; i < UCHAR_MAX+1; i++) {
			if(i != mode) {
				radixSortInternal(count[i], bucket[i], k+1);
			}
		}
		n = count[mode];
		a = bucket[mode];
		k = k+1;
		} else {
	  
		k = k+1;
		}
	}
}	 
void radixSort(int n, char **a){
	radixSortInternal(n, a, 0);
}
	
int main(){
	char isString=0;
	long int size,i;
	scanf("%ld", &size);
	
	char * buffer;
	size_t buffsize = 100000;
	buffer = malloc(sizeof(char)*buffsize);
	scanf ("%s", buffer);

	//printf("%s\n", buffer);
	int length = strlen (buffer);
	for (i=0;i<length; i++)
        if (!isdigit(buffer[i]) && buffer[i] != '-')
        {
        	//printf ("Entered input is not a number\n");
        	isString = 1;
        	break;
        }else{
		//printf ("Entered input is a number\n");	
		break;

	}

    if(isString){//char
    	char** vector = malloc(sizeof(char*)*size);
    	for(i = 0; i < size; i++) vector[i] = malloc(sizeof(char)*buffsize);
    	vector[0] = buffer;
    	for(i = 1; i < size; i++) scanf("%s", vector[i]);
	//printf("RADIX");
	radixSort(size , vector);
    	for(i = 0; i < size; i++) printf("%s\n",vector[i]);	
    }
	else{//inteiro
		long int* vector = malloc(sizeof(long int)*size);
		vector[0] = atol(buffer);
		free(buffer);
		for(i = 1; i < size; i++) scanf("%ld", &vector[i]); 
		long int max; 
		long int min;
		max = get_max(vector, size);	
		min = get_min(vector, size);
		if(max - min > size*10){
			//printf(" QUICK \n");
			quick(vector, 0 , size -1);
		}else{
			//printf(" COUNTING \n");
			counting(vector, size , max - min);
		}
		for(i = 0; i < size; i++) printf("%ld\n",vector[i]);
	}
}
