#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
FILE *create_file(char file_name[25]);
FILE *open_file(char file_name[25]);
int Search_in_File(FILE *fp, char *str);
int Find_once(FILE *input_file,FILE *destination_file, char *str);
void replace_n_store(
   char starting_string[30], char ending_string[30],  
   FILE *source_file,FILE *destination_file);
void replace_with_comma(char input_line[512],FILE *output_file);

int main()
{
   
   FILE *fs,*fb,*fo;
   char mark_rep[]="Market report",new_lots[]="New lots";


   fs=open_file("firmA4_1008-2016.txt");   //test.txt  firmA4_1008-2016.txt
   fo=create_file("others.csv");
   fb=create_file("bids.csv");

   replace_n_store(mark_rep,new_lots,fs,fo);
   printf("Done with file: %s !\n\n","others.csv" );

   replace_n_store("\n","You wont find this",fs,fb);
   printf("Done with file: %s !\n\n","bids.csv" );
 
   fclose(fs);
   fclose(fb);
   fclose(fo);

   system("pause");
   return 0;
}

FILE *open_file(char file_name[25]){
   
   printf("Name of file to open: %s\n",file_name);
   
   FILE *fp;
   fp = fopen(file_name,"r"); // read mode
 
   if( fp == NULL )
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }else{
      printf("The file opened corectly\n\n");
   }
 
   return fp;
}

FILE *create_file(char file_name[25]){
   
   printf("Name of file to create: %s\n",file_name);
   
   FILE *fp;
   fp = fopen(file_name,"w"); // write mode
 
   if( fp == NULL )
   {
      perror("Error while creating the file.\n");
      exit(EXIT_FAILURE);
   }else{
      printf("The file created correctly\n\n");
   }
 
   return fp;
}

//Search_in_File is not used but is very helpfull
// for other text processing programs
int Search_in_File(FILE *fp, char *str) {
  
   int line_num = 1;
   int find_result = 0;
   char temp[512];

   while(fgets(temp, 512, fp) != NULL) {
     
      if((strstr(temp, str)) != NULL) {
         printf("A match found on line: %d\n", line_num);
         printf("\n%s\n", temp);
         find_result++;
      }
      line_num++;
   }

   if(find_result == 0) {
      printf("\nSorry, couldn't find a match.\n");
   }

   printf("Lines read: %d\n",line_num);
  
   //Close the file if still open.
   return(0);
}


int Find_once(FILE *input_file,FILE *destination_file, char *str) {
  
   int line_num = 1;
   char temp[512];

   while(fgets(temp, 512, input_file) != NULL) {
     
      if((strstr(temp, str)) != NULL) {
      	replace_with_comma(temp,destination_file);  //output the line that key was found
        return(line_num);
      }
      line_num++;
   }
   return(0);
}

void replace_n_store(
   char starting_string[30], char ending_string[30], 
   FILE *source_file,FILE *destination_file)
{
   int line_num = 1;
   char temp[512];

   Find_once(source_file,destination_file, starting_string);
   while(fgets(temp, 512, source_file) != NULL) {
      if((strstr(temp, ending_string)) != NULL) {
         //found the ending_string in this line
         break;
      }else{ 
         replace_with_comma(temp,destination_file);
      }
   
   }

}


void replace_with_comma(char input_line[512],FILE *output_file){

   char output[512]="";

   int i=0;
   int j=0;


	while(input_line[i]!='\n' && input_line[i]!='\0' ){
		
		if(input_line[i]==','){
			output[j]=' ';
			j++;
		}else
		if(input_line[i]==' '){

			if(input_line[i+1]==' '){
				if(output[j-1]!=','){
					output[j]=',';
					j++;
				}
			}else
			if(input_line[i+1]=='u'){
				output[j]=',';
				j++;
			}else{
				output[j]=' ';
				j++;	
			}
		}else{
			output[j]=input_line[i];
			j++;
		}
		i++;
	}

   output[i]='\0';
   fprintf(output_file, "%s\n",output);  //write to file the processed line.
}
