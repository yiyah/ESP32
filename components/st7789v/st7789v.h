#ifndef __ST7789V_H
#define __ST7789V_H

#include <stdint.h>


typedef enum
{                             /*             MV MX MY */
    ST7789V_SCAN_LRUD = 0,    /* NORMAL:     0  0  0 */
    ST7789V_SCAN_RLUD,        /* X-mirror:   0  1  0 */
    ST7789V_SCAN_LRDU,        /* Y-mirror:   0  0  1 */
    ST7789V_SCAN_RLDU,        /* XY-mirror:  0  1  1 */
} ST7789V_SCAN_DIRECTION;

#define CMD_SWRESET     0x01u
#define CMD_SLPOUT      0x11u       /* Sleep out */
#define CMD_NORON       0x13u       /* Normal Display Mode On */
#define CMD_INVOFF      0x20u       /* Display Inversion Off */
#define CMD_INVON       0x21u       /* Display Inversion On */
#define CMD_CASET       0x2Au       /* Column Address Set */
#define CMD_RASET       0x2Bu       /* Row Address Set */
#define CMD_RAMWR       0x2Cu       /* Memory Write */
#define CMD_DISPON      0x29u       /* Display On */
#define CMD_MADCTL      0x36u       /* Memory Data Access Control */
#define CMD_COLMOD      0x3Au       /* Interface Pixel Format */

/**
 *  Params for CMD_COLMOD
 */
#define COLMOD_65K_16BIT    0x65u       /* 65K color, 16-bit/pixel */

void ST7789V_Init(void);
uint8_t u8ST7789V_Write_CMD(uint8_t cmd);
uint8_t u8ST7789V_Write_DATA(uint8_t *pu8data, uint16_t u16len);
uint8_t u8ST7789V_SetScanDirection(ST7789V_SCAN_DIRECTION dir, uint8_t u8XY_Exchange);


#endif
