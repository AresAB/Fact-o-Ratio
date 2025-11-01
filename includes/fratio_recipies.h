#pragma once

typedef struct fraction {
    unsigned int num;
    unsigned int den;
} fraction;

#define BASE_MATERIAL_DICT_SIZE 5

typedef struct base_material_dict {
    char materials[BASE_MATERIAL_DICT_SIZE][13];
    fraction quantities[BASE_MATERIAL_DICT_SIZE];
} base_material_dict;

base_material_dict base_material_dict_gen();

void recipe_gear_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_pipe_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_engine_unit_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_advanced_circuit_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_electronic_circuit_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_copper_wire_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_chemical_science_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);