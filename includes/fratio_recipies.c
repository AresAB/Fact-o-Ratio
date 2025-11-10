#include "fratio_recipies.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

fraction fract_simplify(fraction a) {
    for(unsigned int i = (a.num > a.den) ? a.den : a.num; i > 1; i--) {
        if (a.num % i == 0 && a.den % i == 0) {
            a.num = a.num / i;
            a.den = a.den / i;
            break;
        }
    }
    return a;
}

fraction fract_mult_2ui(fraction a, unsigned int num, unsigned int den) {
    fraction c = {a.num * num, a.den * den};
    return c;
}

fraction fract_mult_4ui(unsigned int num1, unsigned int den1, unsigned int num2, unsigned int den2) {
    fraction c = {num1 * num2, den1 * den2};
    return c;
}

fraction fract_add(fraction a, fraction b) {
    fraction c = {a.num * b.den + b.num * a.den, a.den * b.den};
    return c;
}

fraction fract_add_2ui(fraction a, unsigned int num, unsigned int den) {
    fraction c = {a.num * den + num * a.den, a.den * den};
    return c;
}

fraction fract_subtract_2ui(fraction a, unsigned int num, unsigned int den) {
    fraction c = {a.num * den - num * a.den, a.den * den};
    return c;
}

unsigned int I_strcmp(char *str1, char *str2) {
    unsigned int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] != str2[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

base_material_dict base_material_dict_gen() {
    base_material_dict dict = {
        {"iron plate", "copper plate", "steel", "plastic", "sulfer"},
        {{0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}},
    };
    return dict;
}

void base_material_dict_increment(base_material_dict *dict, char *key, fraction quantity) {
    for(unsigned int i = 0; i < BASE_MATERIAL_DICT_SIZE; i++) {
        if(I_strcmp(dict->materials[i], key)) {
            dict->quantities[i] = fract_simplify(fract_add(dict->quantities[i], quantity));
            break;
        }
    }
}

void recipe_assembly_print(fraction q, unsigned int a_lvl, char *buffer, char *item) {
    if(a_lvl == 3) {
        fraction q3 = fract_mult_2ui(q, 2, 5);
        fraction q2 = fract_mult_2ui(q, 2, 3);
        fraction a_fract;
        unsigned int a;
        unsigned int a_max = q.num;
        unsigned int b_max = 0;
        unsigned int c_max = 0;
        for(unsigned int i = 0; i <= (float)q3.num / q3.den; i++) {
            if(i != 0) q2 = fract_subtract_2ui(q2, 5, 3);
            a_fract = fract_subtract_2ui(q, 5 * i, 2);
            for(unsigned int j = 0; j <= (float)q2.num / q2.den; j++) {
                if(j != 0) a_fract = fract_subtract_2ui(a_fract, 3, 2);
                a = ceil((float)a_fract.num / a_fract.den);
                if(a + j + i < a_max + b_max + c_max) {
                    a_max = a;
                    b_max = j;
                    c_max = i;
                }
            }
        }
        if(c_max != 0) {
            printf("%u %s III assemblers\n", c_max, item);
            printf(buffer);
        }
        if(b_max != 0) {
            printf("%u %s II assemblers\n", b_max, item);
            printf(buffer);
        }
        if(a_max != 0) {
            printf("%u %s I assemblers\n", a_max, item);
        }
    }
    else if(a_lvl == 2) {
        fraction q2 = fract_mult_2ui(q, 2, 3);
        fraction a_fract;
        unsigned int a;
        unsigned int a_max = ceil((float)q.num / q.den);
        unsigned int b_max = 0;
        for (unsigned int i = 1; i <= (float)q2.num / q2.den; i++) {
            a_fract = fract_subtract_2ui(q, 3 * i, 2);
            a = ceil((float)a_fract.num / a_fract.den);
            if(a + i < a_max + b_max) {
                a_max = a;
                b_max = i;
            }
        }
        if(b_max != 0) {
            printf("%u %s II assemblers\n", b_max, item);
            printf(buffer);
        }
        if(a_max != 0) printf("%u %s I assemblers\n", a_max, item);
    }
    else {
        printf("%u/%u %s I assemblers\n", q.num, q.den, item);
    }
}

void recipe_gear_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict) {
    quantity = fract_mult_2ui(quantity, 1, 2);
    recipe_assembly_print(quantity, assembler_level, buffer, "gear");

    quantity = fract_simplify(fract_mult_2ui(quantity, 4, 1));
    printf(buffer); printf("|- %u/%u iron plates\n", quantity.num, quantity.den);
    base_material_dict_increment(dict, "iron plate", quantity);
}

void recipe_pipe_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict) {
    quantity = fract_mult_2ui(quantity, 1, 2);
    recipe_assembly_print(quantity, assembler_level, buffer, "pipe");

    quantity = fract_simplify(fract_mult_2ui(quantity, 2, 1));
    printf(buffer); printf("|- %u/%u iron plates\n", quantity.num, quantity.den);
    base_material_dict_increment(dict, "iron plate", quantity);
}

void recipe_engine_unit_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict) {
    char *next_buffer = (char *) malloc(strlen(buffer) + 3);
    strcpy(next_buffer, buffer);
    strcat(next_buffer, "|  ");

    fraction item_quantity = fract_mult_2ui(quantity, 10, 1);
    recipe_assembly_print(item_quantity, assembler_level, buffer, "engine unit");

    quantity = fract_simplify(quantity);
    printf(buffer); printf("|- %u/%u steel plates\n", quantity.num, quantity.den);
    base_material_dict_increment(dict, "steel", quantity);
    printf(buffer); printf("|\n");
    item_quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|- "); recipe_pipe_print(item_quantity, assembler_level, next_buffer, dict);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_gear_print(quantity, assembler_level, next_buffer, dict);
    free(next_buffer);
}

void recipe_copper_wire_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict) {
    quantity = fract_mult_2ui(quantity, 1, 4);
    recipe_assembly_print(quantity, assembler_level, buffer, "copper wire");

    quantity = fract_simplify(fract_mult_2ui(quantity, 2, 1));
    printf(buffer); printf("|- %u/%u copper plates\n", quantity.num, quantity.den);
    base_material_dict_increment(dict, "copper plate", quantity);
}

void recipe_electronic_circuit_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict) {
    quantity = fract_mult_2ui(quantity, 1, 2);
    char *next_buffer = (char *) malloc(strlen(buffer) + 3);
    strcpy(next_buffer, buffer);
    strcat(next_buffer, "|  ");

    recipe_assembly_print(quantity, assembler_level, buffer, "electronic circuit");

    fraction item_quantity = fract_simplify(fract_mult_2ui(quantity, 2, 1));
    printf(buffer); printf("|- %u/%u iron plates\n", item_quantity.num, item_quantity.den);
    base_material_dict_increment(dict, "iron plate", item_quantity);
    item_quantity = fract_mult_2ui(quantity, 6, 1);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_copper_wire_print(item_quantity, assembler_level, next_buffer, dict);
}

void recipe_advanced_circuit_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict) {
    char *next_buffer = (char *) malloc(strlen(buffer) + 3);
    strcpy(next_buffer, buffer);
    strcat(next_buffer, "|  ");

    fraction item_quantity = fract_mult_2ui(quantity, 6, 1);
    recipe_assembly_print(item_quantity, assembler_level, buffer, "advanced circuit");

    item_quantity = fract_simplify(fract_mult_2ui(quantity, 2, 1));
    printf(buffer); printf("|- %u/%u plastic\n", item_quantity.num, item_quantity.den);
    base_material_dict_increment(dict, "plastic", item_quantity);
    printf(buffer); printf("|\n");
    item_quantity = fract_mult_2ui(quantity, 4, 1);
    printf(buffer); printf("|- "); recipe_copper_wire_print(item_quantity, assembler_level, next_buffer, dict);
    item_quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_electronic_circuit_print(item_quantity, assembler_level, next_buffer, dict);
}

void recipe_chemical_science_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict) {
    quantity = fract_mult_2ui(quantity, 1, 2);
    char *next_buffer = (char *) malloc(strlen(buffer) + 3);
    strcpy(next_buffer, buffer);
    strcat(next_buffer, "|  ");

    fraction item_quantity = fract_mult_2ui(quantity, 24, 1);
    recipe_assembly_print(item_quantity, assembler_level, buffer, "chemical science");

    quantity = fract_simplify(quantity);
    printf(buffer); printf("|- %u/%u sulfer\n", quantity.num, quantity.den);
    base_material_dict_increment(dict, "sulfer", quantity);
    item_quantity = fract_mult_2ui(quantity, 2, 1);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_engine_unit_print(item_quantity, assembler_level, next_buffer, dict);
    item_quantity = fract_mult_2ui(quantity, 3, 1);
    printf(buffer); printf("|\n");
    printf(buffer); printf("|- "); recipe_advanced_circuit_print(item_quantity, assembler_level, next_buffer, dict);
}
