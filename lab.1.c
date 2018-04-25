#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// #include "sumPoints.h"
#define EOL '\n'

struct nations {
  char name[25];
  int score = 0;
  int pointsToCountry[20];
};

void Sort(struct nations* country)
{
    int temp,
        item;
    char tempN[25];
    for (int num = 1; num < 20; num++)
    {
        temp = country[num].score;
        strcpy(tempN ,country[num].name);
        item = num-1; 
        while(item >= 0 && country[item].score < temp) 
        {
            country[item+1].score = country[item].score; 
            strcpy(country[item+1].name ,country[item].name);
            country[item].score = temp;
            strcpy(country[item].name ,tempN);
            item--;
        }
    }
 }



void writeOut(struct nations* country){
  FILE *pFile;
  pFile = fopen("results.csv", "w");
  // char* result;
  // char buffer[10];
  // for (int i = 0; i < 10; i++){
  //   result = country[i].name;
  //   sprintf(buffer, "%d",country[i].score);
  //   result[strlen(result)] = ' ';
  //   strcat(result, buffer);
  //   result[strlen(result)] = '\n';
  //   fputs(result, pFile);
  //   printf("%s  \n"),buffer[i];
  // }
  int i = 0;
  while (i<10) {
		fprintf(pFile, "%s %d \n", country[i].name, country[i].score); 
		i++;
	}
}

void sumPoints(struct nations* country){
  for (size_t i = 0; i < 20; i++)
  {   
      int counter = 10; 
      int max = country[i].pointsToCountry[0];
      for (size_t j = 1; j < 20; j++)
      {
          int comp = country[j].pointsToCountry[i];
          if( comp > max){
              max = comp;
              if(counter == 10){
                  country[j].score += 12;
                  counter--;
              }
              else if(counter == 9){
                  country[j].score += 10;
                  counter--;
              }
                  else if(counter > 0) {
                    country[j].score +=counter;
                    counter--;
                  }
              country[j].pointsToCountry[i] = 0;
          }
          else {
              if(counter == 10){
                  country[i].score += 12;
                  counter--;
              }
              else if(counter == 9){
                  country[i].score += 10;
                  counter--;
              }
                  else if(counter > 0) {
                    country[i].score +=counter;
                    counter--;
                  }
                  
              country[i].pointsToCountry[0] = 0;
          }
      }
  }
}

void Parse(struct nations* country, char* buf, int c){
  char * ptr1 = strtok(buf, ",");
  char * ptr2 = ptr1;
  // printf(" RULLLEZ %s %p \n",ptr2,ptr1);

  if (ptr1 != NULL) {
    ptr1 = strtok(NULL, ",");
    strncpy(country[c].name, ptr2, ptr1 - ptr2);
  }
  char *substr = new char[10];
  for (int i = 0 ; i < 20 ; i++) {
#ifdef DEBAG
    if(i >17){
    printf(" RULLLEZs %s %s %d \n",ptr1,ptr2, ptr1-ptr2);
    }
#endif   

        ptr2 = ptr1;
        ptr1 = strtok(NULL, ",") ;
#ifdef DEBAG      
    if(i >17){
    printf(" RULLLEZs %s %s %d \n",ptr1,ptr2, ptr1-ptr2);
    }
#endif
        if(i<19)
        strncpy(substr, ptr2, ptr1 - ptr2);
        else strcpy(substr, ptr2);
        int value; sscanf(substr, "%d", &value);
        country[c].pointsToCountry[i] = value;
        // if((*ptr1) != '\0') break;
  // printf(" RULLLEZ %i %i\n",country[c].pointsToCountry[i],i);
        
  }
}



int main() {
  FILE * file;
  file = fopen("eurovision.csv", "r");
  int count;
  char buf[160];
  fgets(buf,160,(FILE*)file);
  printf("buf: %s " , buf);

  
  char *ptr;
  count = strtod(buf, &ptr);
  struct nations country[count];

  for (size_t i = 0; i < count; i++)
  {
    fgets(buf,160,(FILE*)file);
  // printf("buf: %s " , buf);
    Parse(country,buf,i);
    
  }
  fclose(file);
   printf("Country : %s \n",country[1].name);
   printf("Country : %i \n",country[1].pointsToCountry[2]);
  sumPoints(country);
  for (size_t i = 0; i < 20; i++)
  {
   printf("Score : %i \n",country[i].score);
  }

 Sort(country);
 writeOut(country);



#ifdef DEB    
get how many countries we have (read first line)-> n
struct countries country[n];
while(file != EOF)
  read until comma -> x
    char value;
    while((value = getc(file)) != ',') {
          
    }
  strcpy(country[0].name, x);
  wile(file != EOL)
    read until comma -> y
    counrty[i].score += y;
  printf("%s\n", country[n].name);
  printf("%i\n", country[n].score);
//*/
// printf("%c", EOL);
#endif 
return 0;
}