#pragma once

typedef struct fraction {
    unsigned int num;
    unsigned int den;
} fraction;

fraction fract_mult(fraction a, fraction b);
fraction fract_mult_2ui(fraction a, unsigned int num, unsigned int den);
fraction fract_mult_4ui(unsigned int num1, unsigned int den1, unsigned int num2, unsigned int den2);

void recipe_gear_print(fraction quantity, char *buffer);
void recipe_pipe_print(fraction quantity, char *buffer);
void recipe_engine_unit_print(fraction quantity, char *buffer);
void recipe_advanced_circuit_print(fraction quantity, char *buffer);
void recipe_electronic_circuit_print(fraction quantity, char *buffer);
void recipe_copper_wire_print(fraction quantity, char *buffer);
void recipe_chemical_science_print(fraction quantity, char *buffer);