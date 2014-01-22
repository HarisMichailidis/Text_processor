#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
FILE *create_file(char file_name[25]);
FILE *open_file(char file_name[25]);
int Search_in_File(FILE *fp, char *str);
int Find_once(FILE *fp, char *str);
void Delete_rows(int starting_row, int numb_of_rows);
void copy_n_replace(
   char starting_string[30], char ending_string[30],  
   FILE *source_file,FILE *destination_file);

int main()
{
   char ch;
   FILE *fs,*fb,*fo;
   char mark_rep[]="MARKET",new_lots[]="New lots";


   fs=open_file("test.txt");   //test.txt"); //firmA4_1008-2016.txt
   fo=create_file("others.csv");
   fb=create_file("bids.csv");

   char buf[512];
   int counter=0;
   int others_begin,others_end;

   copy_n_replace(mark_rep,new_lots,fs,fo);

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
      printf("The file created corectly\n\n");
   }
 
   return fp;
}

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


int Find_once(FILE *fp, char *str) {
  
   int line_num = 1;
   char temp[512];

   while(fgets(temp, 512, fp) != NULL) {
     
      if((strstr(temp, str)) != NULL) {
         return(line_num);
      }
      line_num++;
   }
   return(0);
}

void copy_n_replace(
   char starting_string[30], char ending_string[30], 
   FILE *source_file,FILE *destination_file)
{
   int line_num = 1;
   char temp[512];

  // int others_begin=Find_once(source_file, starting_string)+1;
  // printf("Others.csv will begin on line: %d\n",others_begin);

   Find_once(source_file, starting_string);
   while(fgets(temp, 512, source_file) != NULL) {
      printf("%s\n",temp);
  /*    if((strstr(temp, str)) != NULL) {
         printf("A match found on line: %d\n", line_num);
         printf("\n%s\n", temp);
         find_result++;
      }
    */
   }








//   int others_end=others_begin+Find_once(source_file, ending_string)-2;
//   printf("Others.csv will end on line: %d\n",others_end);



}
