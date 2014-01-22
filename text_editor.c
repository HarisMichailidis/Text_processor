#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
FILE *create_file(char file_name[25]);
FILE *open_file(char file_name[25]);
int Search_in_File(FILE *fp, char *str);
int Find_once(FILE *fp, char *str);
void Delete_rows(int starting_row, int numb_of_rows);
void replace_n_store(
   char starting_string[30], char ending_string[30],  
   FILE *source_file,FILE *destination_file);
void replace_with_comma(char input_line[512],FILE *output_file);
char *str_replace(char *orig, char *rep, char *with);

int main()
{
   char ch;
   FILE *fs,*fb,*fo;
   char mark_rep[]="Market report",new_lots[]="New lots";


   fs=open_file("test.txt");   //test.txt"); //firmA4_1008-2016.txt
   fo=create_file("others.csv");
   fb=create_file("bids.csv");

   char buf[512];
   int counter=0;
   int others_begin,others_end;

   replace_n_store(mark_rep,new_lots,fs,fo);

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

void replace_n_store(
   char starting_string[30], char ending_string[30], 
   FILE *source_file,FILE *destination_file)
{
   int line_num = 1;
   char temp[512];

  // int others_begin=Find_once(source_file, starting_string)+1;
  // printf("Others.csv will begin on line: %d\n",others_begin);

   Find_once(source_file, starting_string);
   while(fgets(temp, 512, source_file) != NULL) {
      if((strstr(temp, ending_string)) != NULL) {
         //found the end
         printf("done with the first part\n");
         break;
      }else{ 

         //printf("%s\n",temp);
         replace_with_comma(temp,destination_file);
      }
   
   }

}


void replace_with_comma(char input_line[512],FILE *output_file){

   char output[512];
   char string1[30];

   int i=0;
   while(input_line[i]!='\n'){

      //code for replacing spaces with commas




      printf("%c",input_line[i]);
      i++;
   }
   //printf("\n");
}

// You must free the result if result is non-NULL.
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep
    int len_with; // length of with
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    if (!orig)
        return NULL;
    if (!rep)
        rep = "";
    len_rep = strlen(rep);
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
