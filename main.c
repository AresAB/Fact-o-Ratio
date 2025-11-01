#include <fratio_recipies.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

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
    printf("|- What is your highest level of assembly?\n");
    printf("|  -- (1 for lvl 1, 2 for lvl 2, etc.) --\n");
    printf("|> ");
    unsigned int lvl;
    scanf("%u", &lvl);

    printf("----------------------------------------\n");
    printf("|               RESULTS                |\n");
    printf("----------------------------------------\n\n");

    fraction quantity = {num, den};
    base_material_dict output = base_material_dict_gen();
    lowercase(item);
    if(str_trim_cmp(item, "chemical science") || str_trim_cmp(item, "blue science")) {
        recipe_chemical_science_print(quantity, lvl, "", &output);
    }
    else if(str_trim_cmp(item, "engine")) {
        recipe_engine_unit_print(quantity, lvl, "", &output);
    }
    else if(str_trim_cmp(item, "advanced circuit") || str_trim_cmp(item, "red circuit")) {
        recipe_advanced_circuit_print(quantity, lvl, "", &output);
    }
    else if(str_trim_cmp(item, "electronic circuit") || str_trim_cmp(item, "green circuit")) {
        recipe_electronic_circuit_print(quantity, lvl, "", &output);
    }
    else if(str_trim_cmp(item, "gear")) {
        recipe_gear_print(quantity, lvl, "", &output);
    }

    printf("\n------------------------------\n");
    printf("| Total Base Cost Per Second |\n");
    printf("------------------------------\n\n");

    for(int i = 0; i < BASE_MATERIAL_DICT_SIZE; i++) {
        unsigned int num = output.quantities[i].num;
        if(num > 0) {
            unsigned int den = output.quantities[i].den;
            printf("%u %u/%u %s\n", num/den , num % den, den, output.materials[i]);
        }
    }
}

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
