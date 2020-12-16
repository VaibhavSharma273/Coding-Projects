//Name: Vaibhav Sharma
//NetID: vs432
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
int opt (int[], int, int[], int, int, int, int, int, int, int);
int main(int argc, char *argv[])
{
	if (argc==1) {
		printf("Error\n");
		exit(0);
	}

	for (int i=0; argv[1][i]!='\0'; i++) {
		if (!isdigit(argv[1][i])) {
			printf("Error\n");
			exit(0);
		}
	}

	int BinSize = atoi(argv[1]);

	if(BinSize==0)
	{
		printf("Error\n");
				exit(0);
	}


	int BinItems[argc]; 

	//loop to intialize the one containing the bin items to -1
	for (int k=0; k < argc; k++)
    {
    	BinItems[k] =-1;
    }

    //loop to assign bin items to an array
    int i=2, ArrSize=0;

    while (i<argc&&isdigit(argv[i][0]))
    {
    	for(int j=0; argv[i][j]!='\0'; j++)
			if(!isdigit(argv[i][j]))
			{
				printf("Error\n");
				exit(0);
			}
    	BinItems[i-2]=atoi(argv[i]);
    	if(BinItems[i-2]>BinSize)
    	{
    		printf("Error\n");
    		exit(0);
    	}
    	if(BinItems[i-2]==0)
    	{
    		printf("Error\n");
    		exit(0);
    	}
    	i++;
    	ArrSize++;
    }
    ArrSize--;


    //We cannot create an array for flags; stick to argv. Now, we loop through the remaining argv and check the flags
    if(i==argc)
    	{
    		exit(0);
    	}


    while (i<argc)
    { 
    	//loop to intialize bin
    	int Bin[ArrSize+1];
    	for (int k=0; k<=ArrSize; k++)
	    {
	    	Bin[k]=0;
	    	//printf("%d %d\n", Bin[k], BinSize);
	    }

//ff
    	if(!strcmp(argv[i], "-ff"))
    	{
    		for(int p=0; BinItems[p]!=-1; p++)
    		{
    			for (int q=0; q<=ArrSize; q++)
    			{
    				if (Bin[q]+BinItems[p]<=BinSize)
    					{
    						Bin[q]+=BinItems[p];
    						break;
    					}
    				else if (BinItems[p]>BinSize)
    					{
    						printf("Error");
    						exit(0);
    					}
    			}
    		}
    		int cntr=0;
    		for(int i=0; i<=ArrSize; i++)
    		{
    			if (Bin[i]!=0)
    				cntr++;
    		}
    		printf("-ff  %d\n", cntr);
    	
    	i++;
    	}

//ffd
    	else if(!strcmp(argv[i], "-ffd"))
    	{

    		

    		int BinItemsD[ArrSize+1];
    		//CopyArray(BinItemsD, BinItems);
    		for (int i=0; i<=ArrSize; i++)
    		{
    			BinItemsD[i]=BinItems[i];
    		}

            /*for(int i=0; i<=ArrSize; i++)
            {
                if (Bin[i]!=0) {
                    printf("%d ", Bin[i]);
                }
            }*/ 
            // Lowest member gets placed into the first bin of Bins after sorting for no reason: memory overwrite?

            
    		//Sorting using insertion sort
    		for (int p=1; p<=ArrSize; p++)
    		{
    			int large=BinItemsD[p];
    			int j=p-1;
    				while(BinItemsD[j]<large && j>=0)
    					{
    						BinItemsD[j+1]=BinItemsD[j];
    						j--;
    					}
    			BinItemsD[j+1]=large;
    		}

    		//Applying first fit
    		for(int p=0; p<=ArrSize; p++)
    		{
    			for (int q=0; q<=ArrSize; q++)
    			{
    				if (Bin[q]+BinItemsD[p]<=BinSize)
    					{
    						Bin[q]+=BinItemsD[p];
    						break;
    					}
    				else if (BinItemsD[p]>BinSize)
    					{
    						printf("Error");
    						exit(0);
    					}
    			}
    		}

    		int cntr=0;
    		for(int i=0; i<=ArrSize; i++)
    		{
    			if (Bin[i]!=0) {
    				cntr++;
                }
    		}
    		printf("-ffd %d\n", cntr);
    	
    	i++;
    	}

//bf
    
        else if (!strcmp(argv[i], "-bf"))
        {

        	int CheckBF[ArrSize+1];
        	for (int p=0; p<=ArrSize; p++)
        	{
        		if(BinItems[p]<=BinSize)
        		{
	        		for(int q=0; q<=ArrSize; q++)
	        		{
	        			CheckBF[q]=BinSize-(Bin[q]+BinItems[p]);
	        			if(CheckBF[q]<0)
	        			CheckBF[q]=BinSize+1;
	        		}
	        		int min=0;
	        		for(int s=0; s<=ArrSize; s++)
	        		{
	        			if(CheckBF[s]<CheckBF[min])
	        				min=s;
	        		}
	        		Bin[min]+=BinItems[p];
	        	}
	        	else if (BinItems[p]>BinSize)
    					{
    						printf("Error");
    						exit(0);
    					}
        		
        	}

    		int cntr=0;
    		for(int i=0; i<=ArrSize; i++)
    		{
    			if (Bin[i]!=0)
    				cntr++;
    		}
    		printf("-bf  %d\n", cntr);
    	
    	i++;

        }

//bfd
        else if (!strcmp(argv[i], "-bfd"))
        {

    		int BinItemsD[ArrSize+1];
    		//CopyArray(BinItemsD, BinItems);
    		for (int i=0; i<=ArrSize; i++)
    		{
    			BinItemsD[i]=BinItems[i];
    		}

    		//Sorting using insertion sort

        	for (int p=1; p<=ArrSize; p++)
    		{
    			int large=BinItemsD[p];
    			int j=p-1;
    				while(BinItemsD[j]<large && j>=0)
    					{
    						BinItemsD[j+1]=BinItemsD[j];
    						j--;
    					}
    			BinItemsD[j+1]=large;
    		}

    		//Applying best fit

        	int CheckBF[ArrSize+1];
        	for (int p=0; p<=ArrSize; p++)
        	{
        		if(BinItemsD[p]<=BinSize)
        		{
	        		for(int q=0; q<=ArrSize; q++)
	        		{
	        			CheckBF[q]=BinSize-(Bin[q]+BinItemsD[p]);
	        			if(CheckBF[q]<0)
	        			CheckBF[q]=BinSize+1;
	        		}
	        		int min=0;
	        		for(int s=0; s<=ArrSize; s++)
	        		{
	        			if(CheckBF[s]<CheckBF[min])
	        				min=s;
	        		}
	        		Bin[min]+=BinItemsD[p];
	        	}
	        	else if (BinItemsD[p]>BinSize)
    					{
    						printf("Error");
    						exit(0);
    					}
        		
        	}

    		int cntr=0;
    		for(int i=0; i<=ArrSize; i++)
    		{
    			if (Bin[i]!=0)
    				cntr++;
    		}
    		printf("-bfd %d\n", cntr);
    	
    	i++;

        }

//opt
        else if (!strcmp (argv[i], "-opt"))
        {
        	
        	//for(int p=0; p<=ArrSize; p++)
    		//	printf("%d %d\n", Bin[p], BinSize);
        	int BinItemsD[ArrSize+1];
        	float TotalSize=0;
    		for (int i=0; i<=ArrSize; i++)
    		{
    			BinItemsD[i]=BinItems[i];
    			TotalSize+=BinItems[i];
    		}

    		//Sorting using insertion sort
    		//for(int p=0; p<=ArrSize; p++)
    			//printf("%d %d\n", Bin[p], BinSize);

        	for (int p=1; p<=ArrSize; p++)
    		{
    			int large=BinItemsD[p];
    			int j=p-1;
    				while(BinItemsD[j]<large && j>=0)
    					{
    						BinItemsD[j+1]=BinItemsD[j];
    						j--;
    					}
    			BinItemsD[j+1]=large;
    		}

    		//for(int p=0; p<=ArrSize; p++)
    		//	printf("%d %d\n", Bin[p], BinSize);

    		/*int Bin[ArrSize+1];
		    for (int k=0; k<=ArrSize; k++)
			    {
			    	Bin[k]=0;
			    	//printf("%d %d\n", Bin[k], BinSize);
			    }*/

    		//Finding lower bound
    		float cap_f=TotalSize/BinSize;
    		int cap_d=cap_f;
    		int cap=0;
    		if((cap_f-cap_d) > 0 )
    			 cap=cap_d+1;
    		else
    			 cap=cap_d;
    		
    		printf("-opt %d\n", opt (Bin, BinSize, BinItemsD, 0, ArrSize+1, ArrSize, cap, 0, ArrSize+1, 0));

    	
        i++;
        }
      
      	else 
	       	{
	       		printf("Error\n") ;
	       		exit(0);
	       	}
    }
    
    return 0;
}


int opt (int Bins [], int BinSize, int BinItems[], int curl, int ArrSize, int OAS, int lb, int start, int BestMin, int BinsUsed)
{
	
	int cntr=BinsUsed;
	if (ArrSize==0){
        for (int i=0; i<=OAS; i++)
                printf("%d ", Bins[i]);
        printf("%d\n", cntr);
        return cntr;
    }
	
// to keep track : if at any point cntr goes below min, reject
	//int empty=0;
	int min=BestMin;
	

	for (int x=start; x<=OAS; x++)
	{
		int doneB=0;
		for(int i=0; i<=x-1;i++)
		{
			if(Bins[x]==Bins[i])
			{
				doneB=1;
				break;
			}
		}
		if(doneB) {
			continue;
		}
		
		
		
		if (Bins[x]+BinItems[curl]<=BinSize)
		{

			if(Bins[x]==0)
				BinsUsed++;
			if(BinsUsed>=BestMin)
			 return BestMin;

			Bins[x]+=BinItems[curl];
			int m=0;
			if (BinItems[curl]==BinItems[curl+1])
				m= opt (Bins, BinSize, BinItems, curl+1, ArrSize-1, OAS, lb, x, min, BinsUsed);
			else
				m= opt (Bins, BinSize, BinItems, curl+1, ArrSize-1, OAS, lb, 0, min, BinsUsed);
			if (m<BestMin){
				min=m;
            }
	
			if (min==lb) 
				return min;
				
			Bins[x]-=BinItems[curl];
		}
		
		
	}
	
  return min;
}


