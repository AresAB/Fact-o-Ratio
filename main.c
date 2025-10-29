#include <fratio_recipies.h>
#include <stdio.h>
#include <ctype.h>

void lowercase(char *str);
unsigned int str_trim_cmp(char *long_str, char *short_str);

void main() {
    printf("------------------------------------------\n");
    printf("|       Welcome to Fact-O-Ratio          |\n");
    printf("------------------------------------------\n");
    printf("|***  all numbers are casted as ints  ***|\n");
    printf("------------------------------------------\n");
    printf("|- What item are you looking to produce?\n");
    printf("|> ");
    char item[30];
    fgets(item, 30, stdin);
    printf("|- Please define # of item per _ second(s)\n");
    printf("|-- How much of the item do you want? (#)\n");
    printf("|> ");
    unsigned int num;
    scanf("%u", &num);
    printf("|-- Over how many seconds? (_)\n");
    printf("|> ");
    unsigned int den;
    scanf("%u", &den);
    printf("----------------------------------------\n");
    printf("|               RESULTS                |\n");
    printf("----------------------------------------\n");

    fraction quantity = {num, den};
    lowercase(item);
    if(str_trim_cmp(item, "chemical science") || str_trim_cmp(item, "blue science")) {
        recipe_chemical_science_print(quantity, "");
    }
    else if(str_trim_cmp(item, "engine")) {
        recipe_engine_unit_print(quantity, "");
    }
    else if(str_trim_cmp(item, "advanced circuit") || str_trim_cmp(item, "red circuit")) {
        recipe_advanced_circuit_print(quantity, "");
    }
    else if(str_trim_cmp(item, "electronic circuit") || str_trim_cmp(item, "green circuit")) {
        recipe_electronic_circuit_print(quantity, "");
    }
}

// - figure out how to keep track of base quantities?
// - put in every recipe
// - figure out permanent compiler

void lowercase(char *str) {
    unsigned int i = 0;
    while(str[i] != '\0') {
        str[i] = tolower(str[i]);
        i++;
    }
}

unsigned int str_trim_cmp(char *long_str, char *short_str) {
    unsigned int i = 0;
    while(short_str[i] != '\0') {
        if(long_str[i] != short_str[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}