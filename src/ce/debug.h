/**
 * @file
 * @author Matt "MateoConLechuga" Waltz
 * @brief Contains debugging features for use with a compatible debugger
 */

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NDEBUG

#define dbgout ((volatile char*)0xFB0000) /**< Standard debug output */
#define dbgerr ((volatile char*)0xFC0000) /**< Error debug output */

#define DBG_WATCHPOINT_READ (1 << 0)  /**< Break on read. */
#define DBG_WATCHPOINT_WRITE (1 << 1)  /**< Break on write. */
#define DBG_WATCHPOINT_RW ((1 << 0) | (1 << 1))  /**< Break on read or write. */

/**
 * Used to print to the emulator console.
 *
 * See the syntax for 'printf' for more information.
 * @param ... Uses printf-formated specifier string.
 */
#define dbg_printf(...) sprintf(dbgout, ##__VA_ARGS__)

/**
 * Used to print to the emulator console.
 *
 * See the syntax for 'printf' for more information.
 * @param out Can be dbgout (black) or dbgerr (red).
 * @param ... Uses printf-formated specifier string.
 */
#define dbg_sprintf(out, ...) sprintf(out, ##__VA_ARGS__)

/**
 * Clears the emulation console
 */
#define dbg_ClearConsole() \
do { \
    *(volatile unsigned char*)0xFD0000 = 1; \
} while (0)

/**
 * Opens the emulator's debugger.
 */
#define dbg_Debugger() \
do { \
    *(volatile unsigned char*)0xFFFFFF = (unsigned char)~0; \
} while (0)

/**
 * Sets an emulated breakpoint.
 *
 * @param address Breakpoint address to set.
 */
#define dbg_SetBreakpoint(address) \
do { \
    *(volatile unsigned int*)0xFFFFF0 = (unsigned int)(address); \
    *(volatile unsigned char*)0xFFFFFF = 1; \
} while (0)

/**
 * Removes an emulated breakpoint.
 *
 * @param address Breakpoint address to remove.
 */
#define dbg_RemoveBreakpoint(address) \
do { \
    *(volatile unsigned int*)0xFFFFF0 = (address); \
    *(volatile unsigned char*)0xFFFFFF = 2; \
} while (0)

/**
 * Sets an emulated watchpoint.
 *
 * @param address Watchpoint address to set.
 * @param length The size of the data at the address.
 * @param flags DBG_WATCHPOINT_READ, DBG_WATCHPOINT_WRITE, or
 *              DBG_WATCHPOINT_RW. (or 0 to disable).
 */
#define dbg_SetWatchpoint(address_low, length, flags) \
do { \
    *(volatile unsigned int*)0xFFFFF0 = (unsigned int)(address_low); \
    *(volatile unsigned int*)0xFFFFF4 = ((unsigned int)(address_low) + (length)); \
    *(volatile unsigned char*)0xFFFFF8 = (unsigned char)(flags); \
    *(volatile unsigned char*)0xFFFFFF = 3; \
} while (0)

/**
 * Removes an emulated watchpoint.
 *
 * @param address Watchpoint address to remove.
 */
#define dbg_RemoveWatchpoint(address) \
do { \
    *(volatile unsigned int*)0xFFFFF0 = (unsigned int)(address); \
    *(volatile unsigned char*)0xFFFFFF = 4; \
} while (0)

/**
 * Removes all emulated breakpoints.
 */
#define dbg_RemoveAllBreakpoints() \
do { \
    *(volatile unsigned char*)0xFFFFFF = 6; \
} while (0)

/**
 * Removes all emulated watchpoints.
 */
#define dbg_RemoveAllWatchpoints() \
do { \
    *(volatile unsigned char*)0xFFFFFF = 5; \
} while (0)

#else
#define dbg_printf(...) ((void)0)
#define dbg_sprintf(...) ((void)0)
#define dbg_ClearConsole(...) ((void)0)
#define dbg_Debugger(...) ((void)0)
#define dbg_SetBreakpoint(...) ((void)0)
#define dbg_RemoveBreakpoint(...) ((void)0)
#define dbg_SetWatchpoint(...) ((void)0)
#define dbg_RemoveWatchpoint(...) ((void)0)
#define dbg_RemoveAllBreakpoints(...) ((void)0)
#define dbg_RemoveAllWatchpoints(...) ((void)0)
#endif

#ifdef __cplusplus
}
#endif
