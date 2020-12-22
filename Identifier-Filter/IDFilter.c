#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define ungetchar(c) ungetc(c,stdin)
int CheckSplice (char);

int main() 
{
	int n=1;
    int c;
    while ((c=getchar())!=EOF) {   
    	int t=0;
    	int splice=0;

    	if (isalpha(c)||c=='_'||(c=='&'&&(isalpha(c=getchar())||c=='_'))) {   
    		int x=1;
    		if (c!='&') {
    			t=1;
    			putchar(c);
    		}
    		else {
    			while (c=='&')
    				c=getchar();
    			
    		}

    		while ((c=getchar())!=' ' && c!=EOF && c!='\n') { 
    			if (isalnum(c)||c=='_') {
    					t=1;
    					putchar(c);
    					x++;
    				}
    			
    			else if (c==')'||c=='(') {	
  					break;
    			}

           		else if (c=='\\') {
           			if ((c=getchar())=='\n') {
           				splice++;
           				continue;
           			}
           			else {
                    ungetchar(c);
                    break;
                  }
           		}
    		
    			else if (c=='+'||c=='-'||c=='='||c==';'||c=='?'||c==','||c=='*'||c=='/'||c=='<'||c=='>'||c=='%'||c=='!'||c=='&'||c=='|'||c=='!'||c=='$'||c=='.'||'['||']'){
    		    		break;
    			}
    			

    		    else if (c==';'){
    		    	if ((c=getchar())=='\n')
    		    		break;
    		    	else ungetchar(c);
    		    }
             	

             	else if (c=='"') {
	             		while ((c=getchar())!='"'&&c!=EOF) {	                 		
	                 		if (c=='\n')
	    						n++;
	    					if (c=='\\') { 
	    						c=getchar();
	    						if (c=='"')
	    							continue;
	    						else ungetchar(c);
	    					}
	                 	}               
	           		}

           		else { 

             		t=0;
             		for (int i=x;i>0;i--) {
             			printf ("\b");
             		}
         		}
             }
         }

			if (t==1)
            	printf(":%d\n", n);
    		
    		if (isdigit(c)) {
    				while (isalnum(c)) {
                      		c=getchar();
                      	}

                  if (c!='\n')
                    ungetchar(c);
                }
             
			
			else if (c=='\'')
	             	{	
	             		while ((c=getchar())!='\''&&c!=EOF)
	                 	{
	                 		if (c=='\n')
	    						n++;
	    					
	    					else if (c=='\\')
	    					{ 
	    						c=getchar();
	    						if (c=='\\')
	    							continue;
	    						else if (c=='\'')
	    							continue;
	    						else ungetchar(c);
	    					}	
	                 	}	                
	           		}
	           		


             else if (c=='"')
             	{
             		while ((c=getchar())!='"'&&c!=EOF)
                 	{
                 		if (c=='\n')
    						{
    							n++;	
    						}
    					if (c=='\\')
    					{ 
    						c=getchar();
    						if (c=='"')
    							continue;
    						else if (c=='\n')
    							n++;
    						
    					}

                 	}
                
           		}
             
             

          else if (c=='/')
    			{
    				c=getchar();
    				 if(c=='\\')
           				{
							while (c!=EOF)
							{
								c=getchar();
								if(c=='\n')
								{
									n++;
									c=getchar();
									if (c=='\\')
										continue;
									else
									{
										ungetchar(c);
										break;
									}	
								}

							}

           			}

           		 if(c=='*')
    				{
    						while (c!=EOF)
    						{  
    							c=getchar();
    							if (c=='\n')
    								n++;
    							if (c=='*')
    							{
    								c=getchar();
    								if (c=='/')
    									break;
    								else 
    									ungetchar(c);
    							}   							
    						}
    				}

    				else if (c=='/')
    				{
    					while (c!='\n')
    					{
    						c=getchar();
    						if (c=='\\')
    							{
    								c=getchar();
    								if (c=='\n')
    								{
    								 n++;
    								 c=getchar();
    								 continue;
    								}
    						}
    					}	
    				}

    				else if (c!='\n')
              ungetchar(c);
    			}
            if (c=='\n')
               n++;
           n+=splice;
       }     
return 0;
}

int CheckSplice(char x)
{
 int c; 
 int splice=0;
 while (c!=x&&c!=EOF)
 {
 	c=getchar();
 	if (c=='\n')
 		splice++;
 	else if(c=='\\')
 	{
 		c=getchar();
 		if(c=='\n')
 			splice++;
 	}
 }
 return splice;
}
