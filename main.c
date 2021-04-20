#include "gametank.h"

char frameflag = 0;
char frameflip = DMA_PAGE_OUT;
char cursorX = 0, cursorY = 0;

void draw_ball(int x, int y) {
    *dma_flags = DMA_NMI | DMA_ENABLE | DMA_IRQ | frameflip;
    vram[VX] = x;
    vram[VY] = y;
    vram[GX] = 0x20;
    vram[GY] = 0x40;
    vram[WIDTH] = 16;
    vram[HEIGHT] = 16;
    vram[START] = 1;
    asm wai;
    return;
}

void print(char* str) {
    while(*str != 0) {
        if(*str >= '0' && *str <= '9') {
            vram[GX] = (*str - '0') << 3;
            vram[GY] = 0x60;
        } else if(*str >= 'a' && *str <= 'f') {
            vram[GX] = ((*str - 'a') << 3) + 0x50;
            vram[GY] = 0x60;
        } else if(*str >= 'g' && *str <= 'v') {
            vram[GX] = (*str - 'g') << 3;
            vram[GY] = 0x68;
        } else if(*str >= 'w' && *str <= 'z') {
            vram[GX] = (*str - 'w') << 3;
            vram[GY] = 0x70;
        } else {
            vram[GX] = 0x70;
            vram[GY] = 0x70;
        }
        if(*str == '\n') {
            cursorX = 0;
            cursorY += 8;
        } else {
            vram[VX] = cursorX;
            vram[VY] = cursorY;
            vram[WIDTH] = 8;
            vram[HEIGHT] = 8;
            vram[START] = 1;
            asm wai;
            cursorX += 8;
        }
        str++;
        if(cursorX >= 128) {
            cursorX = 0;
            cursorY += 8;
        }
        if(cursorY >= 128) {
            cursorX = 0;
            cursorY = 0;
        }
    }
}

void main() {
    char col = 0, row = 0;
    unsigned char tr, tc, talt;
    int dx = 1, dy = 1;
    asm sei;
    *dma_flags = DMA_NMI | DMA_IRQ;
    asm {
        xref GameSprites
        xref InflateParams
        xref Inflate
        LDA #<GameSprites
        STA InflateParams
        LDA #>GameSprites
        STA InflateParams+1
        LDA #$00
        STA InflateParams+2
        LDA #$40
        STA InflateParams+3
        JSR Inflate
    };

    
    row = 10;
    col = 20;
    while(1) {
        *dma_flags = DMA_NMI | DMA_ENABLE | DMA_IRQ | DMA_TRANS | frameflip;
        frameflag = 1;
        talt = 0;
        vram[GY] = 24;
        vram[WIDTH] = 8;
        vram[HEIGHT] = 8;
        for(tr = 0; tr < 128; tr += 8) {
            for(tc = 0; tc < 128; tc += 8) {
                vram[VX] = tc;
                vram[VY] = tr;
                vram[GX] = talt;
                *vram_START = 1;
                asm wai;
                talt += 8;
                talt &= 8;
            }
            talt += 8;
            talt &= 8;
        }
        cursorX = 0;
        cursorY = 0;
        print("hello world\n\nthis program\nwas written\nin c");

        draw_ball(col, row);

        col += dx;
        row += dy;
        if(col == 1) {
            dx = 1;
        } else if(col == 111) {
            dx = -1;
        }
        if(row == 1) {
            dy = 1;
        } else if(row == 100) {
            dy = -1;
        }
        while(frameflag) {} 
        frameflip ^= DMA_PAGE_OUT | DMA_VRAM_PAGE;
    }
}

void IRQHandler() {

}

void NMIHandler() {
    frameflag = 0;
}