#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define EOL '\n'

struct nations {
  char name[25];
  int score;
  int pointsToCountry[20];
};

void ParseShip(struct nations* country, char* buf, int c){
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
    ParseShip(country,buf,i);
    
  }
  fclose(file);
   printf("Country : %s \n",country[1].name);
   printf("Country : %i \n",country[1].pointsToCountry[2]);



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