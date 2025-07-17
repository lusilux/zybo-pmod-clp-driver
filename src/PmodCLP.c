/*
 * PmodCLP.c
 * ----------------------------------------------------------------------------
 * Implementación de funciones para el control del módulo PMOD CLP (LCD HD44780)
 * mediante AXI GPIO en la plataforma Zybo Z7-10.
 *
 * Autor: Lucía Alba Torres
 * ----------------------------------------------------------------------------
 */

#include "PmodCLP.h"
#include "sleep.h"

static void pulse_enable(PmodCLP* lcd, u8 ctrl) {
	XGpio_DiscreteWrite(&lcd->gpio, 2, ctrl | E_BIT); // E=1
	usleep(1);
	XGpio_DiscreteWrite(&lcd->gpio, 2, ctrl);         // E=0
	usleep(50);
}

int PmodCLP_Initialize(PmodCLP* lcd, u16 device_id) {
	lcd->device_id = device_id;
	int status = XGpio_Initialize(&lcd->gpio, lcd->device_id);
	if (status != XST_SUCCESS) return XST_FAILURE;

	XGpio_SetDataDirection(&lcd->gpio, 1, 0x00); // Canal 1: datos -> salida
	XGpio_SetDataDirection(&lcd->gpio, 2, 0x00); // Canal 2: control -> salida

	return XST_SUCCESS;
}

void PmodCLP_WriteCommand(PmodCLP* lcd, u8 cmd) {
	u8 ctrl = 0; // RS=0, RW=0
	XGpio_DiscreteWrite(&lcd->gpio, 2, ctrl);
	XGpio_DiscreteWrite(&lcd->gpio, 1, cmd);
	pulse_enable(lcd, ctrl);
}

void PmodCLP_WriteData(PmodCLP* lcd, u8 data) {
	u8 ctrl = RS_BIT; // RS=1, RW=0
	XGpio_DiscreteWrite(&lcd->gpio, 2, ctrl);
	XGpio_DiscreteWrite(&lcd->gpio, 1, data);
	pulse_enable(lcd, ctrl);
}

void PmodCLP_Init(PmodCLP* lcd) {
	usleep(30000); // Espera inicial

	PmodCLP_WriteCommand(lcd, 0x30);
	usleep(6000);
	PmodCLP_WriteCommand(lcd, 0x30);
	usleep(500);
	PmodCLP_WriteCommand(lcd, 0x30);
	usleep(500);
	PmodCLP_WriteCommand(lcd, 0x38); // 8-bit mode
	usleep(80);

	PmodCLP_WriteCommand(lcd, 0x38); // 2 líneas, 5x8
	usleep(50);

	PmodCLP_WriteCommand(lcd, 0x0C); // Display ON, Cursor OFF
	usleep(50);

	PmodCLP_WriteCommand(lcd, 0x01); // Clear display
	usleep(3000);

	PmodCLP_WriteCommand(lcd, 0x06); // Entry mode
	usleep(50);
}

void PmodCLP_WriteString(PmodCLP* lcd, const char* str) {
	while (*str) {
		PmodCLP_WriteData(lcd, (u8)(*str));
		str++;
	}
}
