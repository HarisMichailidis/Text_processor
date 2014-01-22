#include <stdio.h>
#include <stdlib.h>
 
FILE *create_file(char file_name[25]);
FILE *open_file(char file_name[25]);

int main()
{
   char ch;
   FILE *fs,*fb,*fo;

   fs=open_file("firmA4_1008-2016.txt");
   fo=create_file("others.csv");
   fb=create_file("bids.csv");




 
/*   while( ( ch = fgetc(fp) ) != EOF )
      printf("%c",ch);
 */
   fclose(fs);
   fclose(fb);
   fclose(fo);
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

