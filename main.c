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

int col = 0, row = 0, dx, dy;

void main() {
    *dma_flags = DMA_NMI | DMA_CPU_TO_VRAM | DMA_IRQ;
    for(row = 0; row < 128; row++) {
        for(col = 0; col < 128; col++) {
            vram[(row << 7) | col] = col^row;
        }
    }
    *dma_flags = DMA_NMI | DMA_ENABLE | DMA_IRQ;
    dx = 1;
    dy = 1;
    row = 10;
    col = 10;
    while(1) {
        vram[VX] = col;
        vram[VY] = row;
        vram[GX] = 128;
        vram[GY] = 0;
        vram[WIDTH] = 8;
        vram[HEIGHT] = 8;
        vram[COLOR] = row^col;
        vram[START] = 1;
        asm wai;
        col += dx;
        row += dy;
        if(col == 0) {
            dx = 1;
        } else if(col == 100) {
            dx = -1;
        }
        if(row == 0) {
            dy = 1;
        } else if(row == 90) {
            dy = -1;
        }
        asm wai;
        asm wai;
    }
}