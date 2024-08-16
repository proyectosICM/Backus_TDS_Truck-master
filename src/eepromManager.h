#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <EEPROM.h>

// Declaraciones de variables globales
extern const int mesh_port_address;
extern const int flag_state_address;
extern const int mesh_prefix_address;

// Declaraciones de funciones
void save2EEPROM(uint16_t puerto_mesh, char* prefijo_mesh);

#endif // EEPROM_MANAGER_H
 