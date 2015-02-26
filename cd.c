#include<stdio.h>
#include<ctype.h>
#include<string.h>
FILE *fp,*fpp;
struct Tokens{
	char type[100];
	char value[50];
};
typedef struct Tokens tokens;
void write(tokens token){  /**Write to File**/
	fprintf(fpp,"< %s,%s > ",token.type,token.value);
}
main(int argc,char *argv[])
{
        FILE *fp;
        int i=0,j=0,l,lineno=1;
        char str[200],id[20];
        fp=fopen(argv[1],"r");/**Read the input File**/
	fpp=fopen("output.txt","w");/**Create your new File**/
        
	while(fgets(str,sizeof(str),fp)){ /**Read the file line by line**/	
		l=strlen(str);
		str[l-1]='\0';
		for(i=0;i<l;i++){
			j=0;
			if(isalpha(str[i])||str[i]=='_'){ /**Check for a valid identifier**/
				tokens token;
				token.value[j]=str[i];
				i++;
				while(isalnum(str[i])||str[i]=='_'){
					j++;
					token.value[j]=str[i];
					i++;
				}
				token.value[j+1]='\0';
				strcpy(token.type,"identifier");
				write(token);
			}
			if(isdigit(str[i])){ /**Checking if identifier is int or float**/
				tokens token;			
				token.value[j]=str[i];
				i++;
				while(isdigit(str[i])){
					j++;
					token.value[j]=str[i];
					i++;
				}
				if(str[i]=='.'){
					strcpy(token.type,"float");
					token.value[j]=str[i];					
					i++;					
					while(isdigit(str[i])){
						j++;
						token.value[j]=str[i];
						i++;
					}
				}
				else 	
				strcpy(token.type,"int");				
				token.value[j+1]='\0';
				write(token);
			}
			
			if(str[i]!='\0'){
				tokens token;		
				switch(str[i]){ /**Checking for operator**/
					case '+':
						if(str[i+1]=='+'&& !(isalnum(str[i+2]))){
							strcpy(token.type,"increment operator");
							strcpy(token.value,"++");
							write(token);
							i++;
						}
						else if(str[i+1]=='+' && isalnum(str[i+2])){
							printf("Error:%d:Invalid operator\n",lineno);
							i++;
						}
						else{
							strcpy(token.type,"addition operator");
							strcpy(token.value,"+");
							write(token);
						}
						break;
					case '-':
	                        	        strcpy(token.type,"subtraction operator");
	                        	        strcpy(token.value,"+");
						write(token);
	                        	        break;
					case '*':
	                        	        strcpy(token.type,"multiply operator");
	                        	        strcpy(token.value,"*");
						write(token);
	                        	        break;
					case '/':
	                        	        strcpy(token.type,"division operator");
	                        	        strcpy(token.value,"/");
						write(token);
	                        	        break;
					case '%':
	                        	        strcpy(token.type,"modulus operator");
	                        	        strcpy(token.value,"%");
						write(token);
	                        	        break;
					case '=':
						if(str[i+1] == '='){
							strcpy(token.type,"equality operator");
	   	                	                strcpy(token.value,"==");
							i++;
						}
	                        	        else{
							strcpy(token.type,"assignment operator");
	 		        	                strcpy(token.value,"=");
						}
						write(token);						
	                        	        break;
					case '!':
	                        	        strcpy(token.type," inequality operator");
	                        	        strcpy(token.value,"!=");
						i++;
						write(token);
	                        	        break;
					case '>': 
						if(str[i+1] == '='){
							strcpy(token.type,"greater than or equal operator");
	                        	        	strcpy(token.value,">=");
							i++;
						}
	                        	        else{
	                        	        	strcpy(token.type,"greater than operator");
	                        	        	strcpy(token.value,">");
						}                              
						write(token);	
						break;
					case '<':
						if(str[i+1]=='='){
							strcpy(token.type,"less than or equal operator");
	                        	        	strcpy(token.value,"<=");
							i++;
						}
	                        	        else{
							strcpy(token.type,"less than operator");
	                        	        	strcpy(token.value,"<");
						}
						write(token);				               
						break;
					case '^':
						strcpy(token.type,"exponential operator");
						strcpy(token.value,"^");
						write(token);						
						break;
					case '&':
						if(str[i+1]=='&'){
                                                         strcpy(token.type,"logical AND");
							 strcpy(token.value,"&&");
							 i++;
						}
						else{
							strcpy(token.type,"logical operator bitwise AND");
							strcpy(token.value,"&");
						}
						write(token);						
						break;
					case '|':
						if(str[i+1]=='|'){
							strcpy(token.type,"logical OR");
							strcpy(token.value,"||");
							i++;
						}
						else{
							strcpy(token.type,"logical operator bitwise OR");
							strcpy(token.value,"|");
						}
						write(token);						
						break;
					default:
						printf("\n Error:%d:Undefined symbol",lineno);
						break;
				}
			}
			
		}
		fprintf(fpp,"\n");
		lineno++;
	}
	fclose(fp);
	fclose(fpp);
}
