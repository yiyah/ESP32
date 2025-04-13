#ifndef __LCD_FONT_H
#define __LCD_FONT_H

#include "stdint.h"

typedef struct {
    const uint8_t h;
    const uint8_t w;
    const uint8_t *chars;
} ASCIIFont;

/**
 * @brief 字体结构体
 * @note  字库前4字节存储utf8编码 剩余字节存储字模数据
 * @note 字库数据可以使用波特律动LED取模助手生成(https://led.baud-dance.com)
 */
typedef struct {
    const uint8_t h;            // 字高度
    const uint8_t w;            // 字宽度
    const uint8_t *chars;       // 字库 字库前4字节存储utf8编码 剩余字节存储字模数据
    const uint8_t len;          // 字库长度 超过256则请改为uint16_t
    const ASCIIFont *ascii;     // 缺省ASCII字体 当字库中没有对应字符且需要显示ASCII字符时使用
} Font;

extern const ASCIIFont afont16x8;
extern const Font font24x32;
extern const Font font16x16;


#endif /* __LCD_FONT_H */
