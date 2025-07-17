/*
 * main.c
 * ----------------------------------------------------------------------------
 * Ejemplo de uso de la librería PmodCLP para controlar un LCD conectado al
 * PMOD CLP en la Zybo Z7-10 mediante AXI GPIO.
 *
 * Autor: Lucía Alba Torres
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "PmodCLP.h"

int main() {

	init_platform();
	xil_printf("Iniciando programa...\n\r");

	PmodCLP lcd;
	if (PmodCLP_Initialize(&lcd, XPAR_AXI_GPIO_0_DEVICE_ID) != XST_SUCCESS) {
		xil_printf("Error al inicializar AXI GPIO.\n\r");
		return XST_FAILURE;
	}

	xil_printf("GPIO inicializado correctamente.\n\r");

	PmodCLP_Init(&lcd);
	xil_printf("LCD inicializada correctamente.\n\r");

	PmodCLP_WriteString(&lcd, "Hola Zybo! :)");
	xil_printf("Mensaje enviado a LCD.\n\r");

	while (1); //Loop infinito

	return 0;
}

