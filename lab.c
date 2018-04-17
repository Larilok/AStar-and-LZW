#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#define EOL '\n'

struct nations {
  char name[15];
  int score;
  int pointsToCounntry[20];
};


// ALL THE WORK ON ARRAY //--//
// SCORE += ...

// 















int main() {
  FILE * file;
  file = fopen("eurovision.csv", "r");
  struct nations country[];

int workArray[20];

for(unsigned j = 0; j < n; ++j) {

  for(unsigned i = 0; i < n; ++i) {
    workArray[i] = country[i].pointsToCounntry[0];
  }
}


  char* string = (char*) calloc(1, sizeof(char));
  int size = 1;
  while (!feof(file)) {
    string[size - 1] = getc(file);
    string = (char*) realloc(string, ++size);
  }
  fclose(file);
  //Данные считаны

  char* countOfCountriesStr = strtok(string, "\n");
  int countOfCountries;
  for (int SymbCounter = 0; SymbCounter < strlen(countOfCountriesStr); SymbCounter++) {
    float sss = strlen(countOfCountriesStr) - SymbCounter - 1;
    countOfCountries = (countOfCountriesStr[SymbCounter] - 48) * pow10f(sss);
  }
   printf("MEGA%i", countOfCountries);
  char aa[] = "asdasd\nsdff";
  char* nn1 = strtok(aa, "\n");
  char* nnn = strtok(NULL, "\n");
  
  // printf("%s\n\n", ii);
  printf("%s\n\n", nn1);
  printf("%s\n\n", nnn);
  printf("%s", string);
  struct nations {
    char name[15];
    int score;
    int pointsToCounntry[20];
  };
  struct nations country[10];

/*/
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
return 0;
}