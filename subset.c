#include <stdio.h>
//#define min_conf 37
typedef struct frequent_item_set{
	int k;
	int *frequentItem;
	int supportCount;
}frequent_item_set_t;

int find_support_den(int *subset_item,int numberOfItems,frequent_item_set_t *frequentItem_data)
{
//assuming that the frequentItem_data can be accessed by this function too
	int counter=0;
	int i=0;int flag=0;		//flag to check whether that subset exists
	while(frequentItem_data[i].k!=numberOfItems)
	{i++;}
	while(frequentItem_data[i].k==numberOfItems)
	{
		int temp[numberOfItems];
		int j=0;
		for(j=0;j<numberOfItems;j++)
		temp[j]=frequentItem_data[i].frequentItem[j];
		if(memcmp(subset_item,temp,sizeof(subset_item))==0)
		{flag=1;break;}		//element found
	i++;
	}
	if(flag==1)
	return frequentItem_data[i].supportCount;
	else 
	return -1;		//in case not found .. conf val would be negative then 
}

void conf_cal(int *arr,int *subset_item,int support_num,int numberOfItems,frequent_item_set_t *frequentItem_data)
{
	int mul=sizeof(arr)-sizeof(subset_item);
	int rem_item[mul];
	double min_conf;
	printf("Enter the  min_conf:");
	scanf("%lf",&min_conf);
	int support_den=find_support_den(subset_item,numberOfItems,frequentItem_data);
	double conf=((double)support_num/(double)support_den)*100;
	int m=0,n=0;		//to find arr -	subset_item
	int count=0;
	while(m<(sizeof(arr)) && count<mul)
	{	
		if(arr[m]==subset_item[n])
		{
		m++;
		rem_item[count]=subset_item[n];
		n++;
		}
		else if(arr[m]<subset_item[n])	
		{
		rem_item[count++]=arr[m];
		m++;
		}
		else if(arr[m]>subset_item[n])
		break;
	}
	printf("hi");
	if(conf>min_conf)
	{
	int i;
	for(i=0;i<sizeof(subset_item);i++)
	printf("%d ",subset_item[i]);	
	printf("->");
	for(i=0;i<sizeof(rem_item);i++)
	printf("%d ",rem_item[i]);
	}
} 

/*  Function to generate subset  */

void subset(int arr[], int subset_item[], int start, int end, int index, int r,int support_num,frequent_item_set_t *frequentItem_data)
{
    int j, i;
    if (index == r) {
printf("SUBSET IS : \n");
	for(i=0;i<r;i++)
	printf("%d ",subset_item[i]); 
	conf_cal(arr,subset_item,support_num,r,frequentItem_data);
        return;
    }

     for (i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        subset_item[index] = arr[i];
        subset(arr, subset_item, i+1, end, index+1, r,support_num,frequentItem_data);
    }
}

void printsubset(int arr[], int n, int r,int support_num,frequent_item_set_t *frequentItem_data)
{

    int subset_item[r];
    subset(arr, subset_item, 0, n - 1, 0, r,support_num,frequentItem_data);
}


subset_gen_function(int *arr,int k,int support_num,frequent_item_set_t *frequentItem_data)
{
	//printf("hi hi ");
	int i,number_of_items_in_subset;
	for(number_of_items_in_subset=1;number_of_items_in_subset<k;number_of_items_in_subset++)
	printsubset(arr, k, number_of_items_in_subset,support_num,frequentItem_data);
        return 0;

}
