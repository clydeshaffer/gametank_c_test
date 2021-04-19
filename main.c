#define dma_flags ((volatile char *) 0x2007)
#define vram ((volatile char *) 0x4000)
#define DMA_ENABLE 1
#define DMA_PAGE_OUT 2
#define DMA_NMI 4
#define DMA_GRAM_PAGE 8
#define DMA_VRAM_PAGE 16
#define DMA_CPU_TO_VRAM 32
#define DMA_IRQ 64
#define DMA_TRANS 128

#define VX 0
#define VY 1
#define GX 2
#define GY 3
#define WIDTH 4
#define HEIGHT 5
#define START 6
#define COLOR 7

void draw_ball(int x, int y, int col) {
    vram[VX] = x;
    vram[VY] = y;
    vram[GX] = 128;
    vram[GY] = 0;
    vram[WIDTH] = 8;
    vram[HEIGHT] = 8;
    vram[COLOR] = col;
    vram[START] = 1;
    asm wai;
    return;
}

void main() {
    char col = 0, row = 0, color = 0;
    int dx = 1, dy = 1;
    *dma_flags = DMA_NMI | DMA_IRQ;
    for(row = 0; row < 128; row++) {
        for(col = 0; col < 128; col++) {
            vram[(row << 7) | col] = col^row;
        }
    }
    *dma_flags = DMA_NMI | DMA_ENABLE | DMA_IRQ | DMA_TRANS;
    row = 10;
    col = 20;
    while(1) {
        vram[VX] = 0;
        vram[VY] = 0;
        vram[GX] = 0;
        vram[GY] = 0;
        vram[WIDTH] = 127;
        vram[HEIGHT] = 110;
        vram[START] = 1;
        asm wai;

        draw_ball(col, row, color++);

        col += dx;
        row += dy;
        if(col == 1) {
            dx = 1;
        } else if(col == 119) {
            dx = -1;
        }
        if(row == 1) {
            dy = 1;
        } else if(row == 100) {
            dy = -1;
        }
        asm wai;
    }
}

void IRQHandler() {

}