#ifndef X86_ASM_INLINE_H
#define X86_ASM_INLINE_H

static inline void outb(uint8_t v, uint16_t port)
{
    asm volatile ("outb %0,%1" : : "a" (v), "d" (port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t v;
    asm volatile ("inb %1,%0" : "=a" (v) : "d" (port));
    return v;
}

static inline void outw(uint16_t v, uint16_t port)
{
    asm volatile ("outw %0,%1" : : "a" (v), "d" (port));
}

static inline uint16_t inw(uint16_t port)
{
    uint16_t v;
    asm volatile ("inw %1,%0" : "=a" (v) : "d" (port));
    return v;
}

#endif
