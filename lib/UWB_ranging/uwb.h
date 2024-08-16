#ifndef UWB_H
#define UWB_H
#include "DW1000Ranging.h"
#include "DW1000.h"

//------------------UWB------------------------
// #define SPI_SCK     18
// #define SPI_MISO    19
// #define SPI_MOSI    23
// #define DW_CS       4
// #define PIN_RST     27 // reset pin
// #define PIN_IRQ     34 // irq pin
// #define PIN_SS      4   // spi select pin

// #define LED         33
// #define RED         14 //<- descomentar

#define SPI_SCK             12
#define SPI_MISO            13
#define SPI_MOSI            11
#define DW_CS               10
#define PIN_RST             8
#define PIN_IRQ             6
#define PIN_SS              10

#define LED         5
#define RED         2 //<- descomentar

// TAG antenna delay defaults to 16384
// leftmost two bytes below will become the "short address"
extern char tag_addr[]; 
extern float range_phase; 
extern float range_from_selection; 
extern uint16_t short_add; 
extern uint16_t mesh_port_num;
extern uint8_t flag_state_machine;
extern uint8_t min_range;
extern bool flag_deletedev;

extern unsigned long tiempoActual; // Define el tiempo del sistema. Se actualiza cosntantemente
extern unsigned long tiempoInicio;
extern unsigned long tiempoEspera;

struct dist{
    //uint16_t address;
    float distancia;
};

extern int devices_active;

// prototypes
void newRange();
void newDevice(DW1000Device *device);
void inactiveDevice(DW1000Device *device);
void init_UWB();
void uwb_main(uint8_t state);
//uint16_t getCloserDevice(uint16_t short_address, float range);

#endif