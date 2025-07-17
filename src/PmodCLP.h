/*
 * PmodCLP.h
 * ----------------------------------------------------------------------------
 * Biblioteca personalizada para controlar el módulo PMOD CLP (LCD HD44780)
 * usando AXI GPIO en la plataforma Zybo Z7-10.
 *
 * Autor: Lucía Alba Torres
 * Fecha: 16/07/2025
 * ----------------------------------------------------------------------------
 * Información de conexión física:
 *
 * El módulo PMOD CLP está conectado a los conectores:
 *   - **JC (data)**    Datos del LCD (D0-D7)
 *   - **JD (control)**  Pines de control: RS, RW, E
 *
 * Las conexiones específicas en el archivo de constraints (`.xdc`) son:
 *
 * ## Pmod Header JC (Datos LCD D0-D7)
 * set_property -dict { PACKAGE_PIN V15 IOSTANDARD LVCMOS33 } [get_ports { data_tri_o[0] }];
 * set_property -dict { PACKAGE_PIN W15 IOSTANDARD LVCMOS33 } [get_ports { data_tri_o[1] }];
 * set_property -dict { PACKAGE_PIN T11 IOSTANDARD LVCMOS33 } [get_ports { data_tri_o[2] }];
 * set_property -dict { PACKAGE_PIN T10 IOSTANDARD LVCMOS33 } [get_ports { data_tri_o[3] }];
 * set_property -dict { PACKAGE_PIN W14 IOSTANDARD LVCMOS33 } [get_ports { data_tri_o[4] }];
 * set_property -dict { PACKAGE_PIN Y14 IOSTANDARD LVCMOS33 } [get_ports { data_tri_o[5] }];
 * set_property -dict { PACKAGE_PIN T12 IOSTANDARD LVCMOS33 } [get_ports { data_tri_o[6] }];
 * set_property -dict { PACKAGE_PIN U12 IOSTANDARD LVCMOS33 } [get_ports { data_tri_o[7] }];
 *
 * ## Pmod Header JD (Control LCD RS, RW, E)
 * set_property -dict { PACKAGE_PIN U14 IOSTANDARD LVCMOS33 } [get_ports { control_tri_o[0] }]; #RS
 * set_property -dict { PACKAGE_PIN U15 IOSTANDARD LVCMOS33 } [get_ports { control_tri_o[1] }]; #RW
 * set_property -dict { PACKAGE_PIN V17 IOSTANDARD LVCMOS33 } [get_ports { control_tri_o[2] }]; #E

 *
 * Asegúrate de usar un IP AXI GPIO con dos canales configurados como salida:
 *   - Canal 1: para datos (8 bits)
 *   - Canal 2: para control (3 bits: RS, RW, E)
 * ----------------------------------------------------------------------------
 */

#ifndef PMODCLP_H
#define PMODCLP_H

#include "xgpio.h"

// Pines de control (canal 2 del AXI GPIO)
#define RS_BIT 0x01  // Bit 0
#define RW_BIT 0x02  // Bit 1
#define E_BIT  0x04  // Bit 2

// Estructura del controlador LCD
typedef struct {
	XGpio gpio;
	u16 device_id;
} PmodCLP;

// Prototipos de funciones
int  PmodCLP_Initialize(PmodCLP* lcd, u16 device_id);
void PmodCLP_Init(PmodCLP* lcd);
void PmodCLP_WriteCommand(PmodCLP* lcd, u8 cmd);
void PmodCLP_WriteData(PmodCLP* lcd, u8 data);
void PmodCLP_WriteString(PmodCLP* lcd, const char* str);

#endif
