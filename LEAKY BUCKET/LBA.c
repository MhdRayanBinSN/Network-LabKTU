#include<stdio.h>
int main()
{
	int n,storage=0,out,psize,bsize,size_left;
	printf("Enter the No.of inputs:");
	scanf("%d",&n);
	printf("Enter the bucket size:");
	scanf("%d",&bsize);
	printf("Enter outgoing rate:");
	scanf("%d",&out);
	for(int i=0;i<n;i++)
	{
		printf("\nEnter incoming packet size:");
		scanf("%d",&psize);
		size_left=bsize-storage;
		if(psize<=size_left)
		{
			storage+=psize;
		}
		else
		{
			printf("Dropped %d no.of packets\n",psize-(bsize-storage));
			storage=bsize;
		}
		printf("\nBucket buffer size %d out of %d",storage,bsize);
		if(storage-out<0)
			storage=0;
		else
			storage-=out;
		printf("\nAfter outgoing %d packets %d packets left in buffer\n",out,storage);
	}
		return 0;
}
