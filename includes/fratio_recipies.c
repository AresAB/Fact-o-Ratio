#include "fratio_recipies.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

fraction fract_mult(fraction a, fraction b) {
    fraction c = {a.num * b.num, a.den * b.den};
    for(unsigned int i = (c.num > c.den) ? c.den : c.num; i > 1; i--) {
        if (c.num % i == 0 && c.den % i == 0) {
            c.num = c.num / i;
            c.den = c.den / i;
            break;
        }
    }
    return c;
}

fraction fract_mult_2ui(fraction a, unsigned int num, unsigned int den) {
    fraction c = {a.num * num, a.den * den};
    for(unsigned int i = (c.num > c.den) ? c.den : c.num; i > 1; i--) {
        if (c.num % i == 0 && c.den % i == 0) {
            c.num = c.num / i;
            c.den = c.den / i;
            break;
        }
    }
    return c;
}

fraction fract_mult_4ui(unsigned int num1, unsigned int den1, unsigned int num2, unsigned int den2) {
    fraction c = {num1 * num2, den1 * den2};
    for(unsigned int i = (c.num > c.den) ? c.den : c.num; i > 1; i--) {
        if (c.num % i == 0 && c.den % i == 0) {
            c.num = c.num / i;
            c.den = c.den / i;
            break;
        }
    }
    return c;
}

void recipe_gear_print(fraction quantity, char *buffer) {
    quantity = fract_mult_2ui(quantity, 1, 2);
    printf("%u/%u gear assemblers\n", quantity.num, quantity.den);
    quantity = fract_mult_2ui(quantity, 4, 1);
    printf(buffer); printf("|- %u/%u iron plates\n", quantity.num, quantity.den);
}

void recipe_pipe_print(fraction quantity, char *buffer) {
    quantity = fract_mult_2ui(quantity, 1, 2);
    printf("%u/%u pipe assemblers\n", quantity.num, quantity.den);
    quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|- %u/%u iron plates\n", quantity.num, quantity.den);
}

void recipe_engine_unit_print(fraction quantity, char *buffer) {
    char *next_buffer = (char *) malloc(strlen(buffer) + 3);
    strcpy(next_buffer, buffer);
    strcat(next_buffer, "|  ");

    fraction item_quantity = fract_mult_2ui(quantity, 10, 1);
    printf("%u/%u engine unit assemblers\n", item_quantity.num, item_quantity.den);
    printf(buffer); printf("|- %u/%u steel plates\n", quantity.num, quantity.den);
    printf(buffer); printf("|\n");
    item_quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|- "); recipe_pipe_print(item_quantity, next_buffer);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_gear_print(quantity, next_buffer);
    free(next_buffer);
}

void recipe_copper_wire_print(fraction quantity, char *buffer) {
    quantity = fract_mult_2ui(quantity, 1, 4);
    printf("%u/%u copper wire assemblers\n", quantity.num, quantity.den);
    quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|- %u/%u copper plates\n", quantity.num, quantity.den);
}

void recipe_electronic_circuit_print(fraction quantity, char *buffer) {
    quantity = fract_mult_2ui(quantity, 1, 2);
    char *next_buffer = (char *) malloc(strlen(buffer) + 3);
    strcpy(next_buffer, buffer);
    strcat(next_buffer, "|  ");

    printf("%u/%u electronic circuit assemblers\n", quantity.num, quantity.den);
    fraction item_quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|- %u/%u iron plates\n", item_quantity.num, item_quantity.den);
    item_quantity = fract_mult_2ui(quantity, 6, 1);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_copper_wire_print(item_quantity, next_buffer);
}

void recipe_advanced_circuit_print(fraction quantity, char *buffer) {
    char *next_buffer = (char *) malloc(strlen(buffer) + 3);
    strcpy(next_buffer, buffer);
    strcat(next_buffer, "|  ");

    fraction item_quantity = fract_mult_2ui(quantity, 6, 1);
    printf("%u/%u advanced circuit assemblers\n", item_quantity.num, item_quantity.den);
    item_quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|- %u/%u plastic\n", item_quantity.num, item_quantity.den);
    printf(buffer); printf("|\n");
    item_quantity = fract_mult_2ui(quantity, 4, 1);
    printf(buffer); printf("|- "); recipe_copper_wire_print(item_quantity, next_buffer);
    item_quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_electronic_circuit_print(item_quantity, next_buffer);
}

void recipe_chemical_science_print(fraction quantity, char *buffer) {
    quantity = fract_mult_2ui(quantity, 1, 2);
    char *next_buffer = (char *) malloc(strlen(buffer) + 3);
    strcpy(next_buffer, buffer);
    strcat(next_buffer, "|  ");

    fraction item_quantity = fract_mult_2ui(quantity, 24, 1);
    printf(buffer); printf("%u/%u chemical science assemblers\n", item_quantity.num, item_quantity.den);
    printf(buffer); printf("|- %u/%u sulfer\n", quantity.num, quantity.den);
    item_quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_engine_unit_print(item_quantity, next_buffer);
    item_quantity = fract_mult_2ui(quantity, 3, 1);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_advanced_circuit_print(item_quantity, next_buffer);
}