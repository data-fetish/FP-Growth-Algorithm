#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 122

#include "subset.c"
int k = 3;

/*typedef struct frequent_item_set{
	int k;
	int *frequentItem;
	int supportCount;
}frequent_item_set_t;
*/
/*typedef struct consequent_item_set{
	int k;
	int consequentItem;
	int supportCount;
}consequent_item_set_t;
*/
frequent_item_set_t *frequentItem_data;
//void subset(int arr[], int data[], int start, int end, int index, int r);
void display();
void gen_rules();
void apri_gen_rule(int *arr,int k,int support);
//void ap-genrules(frequent_item_set_t *frequentItem_data_k,// struct of consequent_m);

int main(int argc, char const *argv[])
{	/*file format k <items> support*/ 
	FILE *fin;
	fin = fopen("frequentItemSetData.txt","r");
	frequentItem_data = (frequent_item_set_t*) malloc (sizeof(frequent_item_set_t) * SIZE * ( sizeof(int) * k));
	// initialize frequentItem_data
	int i = 0;
	int k_temp,j, data,s;

	while(fscanf(fin, "%d", &k_temp) != EOF){
		frequentItem_data[i].k = k_temp;
		frequentItem_data[i].frequentItem = (int *) malloc (sizeof(int) * k_temp);
		for(j = 0 ; j < k_temp; j++){
			fscanf(fin,"%d",&data);
			frequentItem_data[i].frequentItem[j] = data;
		}
		fscanf(fin, "%d", &s);
		frequentItem_data[i].supportCount = s;
		i++;
	}
	// testing if everything is stored correctly in the structure
	display();
	fclose(fin);
	//printf("\nhi");
	gen_rules();
	
	return 0;
}

void display(){
	int i,j;
	for ( i = 0; i < SIZE; i++)
	{
		printf("\nk = %d\tItemSet: ",frequentItem_data[i].k);
		for(j = 0 ; j < frequentItem_data[i].k ; j++){
			printf("%d ", frequentItem_data[i].frequentItem[j] );
		}
		printf("\tsupport: %d\n",frequentItem_data[i].supportCount);
	}
}

void gen_rules()
{	//printf("help");
	int *arr;
	//arr=malloc(sizeof(int));
	int i,j;
	
	for(i=0;i<SIZE;i++)
	{
	arr=malloc(frequentItem_data[i].k*sizeof(int));		//memory alloc
	for(j=0;j<frequentItem_data[i].k;j++)
		arr[j]=frequentItem_data[i].frequentItem[j];
	if(frequentItem_data[i].k>2)
	apri_gen_rule(arr,frequentItem_data[i].k,frequentItem_data[i].supportCount);
	}
}

void apri_gen_rule(int *arr,int k,int support)
{

	subset_gen_function(arr,k,support,frequentItem_data);	
}



