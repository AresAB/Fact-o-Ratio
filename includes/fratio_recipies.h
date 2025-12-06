#pragma once

typedef struct fraction {
    unsigned int num;
    unsigned int den;
} fraction;

#define BASE_MATERIAL_DICT_SIZE 9

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
void recipe_electrical_engine_unit_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_flying_robot_frame_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_construction_robot_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_logistic_robot_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_transport_belt_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_fast_transport_belt_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_splitter_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_fast_splitter_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_electric_furnace_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);
void recipe_electric_mining_drill_print(fraction quantity, unsigned int assembler_level, char *buffer, base_material_dict *dict);