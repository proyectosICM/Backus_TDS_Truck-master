#include "eepromManager.h"

// Direcciones en la memoria EEPROM
const int mesh_port_address = 0;
const int flag_state_address = 2;
const int mesh_prefix_address = 3;

// Guardar los datos en la EEPROM
void save2EEPROM(uint16_t puerto_mesh, char *prefijo_mesh)
{
    EEPROM.writeUShort(mesh_port_address, puerto_mesh);
    Serial.println(EEPROM.readUShort(mesh_port_address));
    EEPROM.writeString(mesh_prefix_address, prefijo_mesh);
    Serial.println(EEPROM.readString(mesh_prefix_address));
    EEPROM.commit();
}
 