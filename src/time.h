#ifndef TIME_H
#define TIME_H

#ifdef __cplusplus
extern          "C" {
#endif
#include <inttypes.h>
#include <stdlib.h>


/**
* @brief Represents the number of clock ticks since an implementation-defined
*        reference point.
*/
typedef uint32_t clock_t;
/**
* @brief Represents the number of seconds elapsed since the Epoch.
*/
typedef uint32_t time_t;

/**
 * @brief Macro defining the number of clock ticks per second.
 *
 * If the macro F_CPU is defined (for example, for AVR/delay), this value is set
 * to F_CPU. Otherwise, it is set to -1, adhering to the ISO default when the
 * value is unknown.
 */
#ifdef F_CPU
#define CLOCKS_PER_SEC (F_CPU)
#else
#define CLOCKS_PER_SEC ((clock_t)-1)
#endif

/**
 * @brief Structure representing the broken-down time.
 *
 * This structure holds various components of calendar time broken down into its
 * components.
 */
struct tm {
    uint8_t  tm_sec;    /**< Seconds [0,59] */
    uint8_t  tm_min;    /**< Minutes [0,59] */
    uint8_t  tm_hour;   /**< Hours [0,23] */
    uint8_t  tm_mday;   /**< Day of the month [1,31] */
    uint8_t  tm_wday;   /**< Day of the week [0,6] (Sunday = 0) not used */
    uint8_t  tm_mon;    /**< Month [1,12] */
    uint16_t tm_year;   /**< Year */
    uint16_t tm_yday;   /**< Day of the year [0,365] not used */
    uint8_t  tm_isdst;  /**< Daylight Saving Time flag, used as:
                             - 0 for UTC
                             - 1 for CET (Central European Time)
                             - 2 for CEST (Central European Summer Time) */
};
/**
 * @brief Returns the processor time used by the program.
 *
 * @return (clock_t) -1 because per default unknown in a environment without rtc.
 */
clock_t         clock(void);

/**
 * @brief Computes the difference between two calendar times.
 *
 * It return a integer because of mcu environment and dont comply the iso norm here, that returns a double here
 *
 * @param time1 The first time value.
 * @param time0 The second time value.
 * @return The difference between time1 and time0 in seconds.
 */
int32_t         difftime(time_t time1, time_t time0);

/**
 * @brief Converts a `struct tm` object to calendar time.
 *
 * @param timeptr Pointer to the `struct tm` object representing the time in UTC.
 * @return The calendar time value.
 */
time_t          mktime(struct tm * timeptr);

/**
 * @brief Returns the time as value read from a pointer.
 *
 * @param timer Pointer to a time_t object where the time is stored.
 * @return The value of the object as time_t.
 */
time_t          time(const time_t *timer);
/**
 * @brief Converts a `struct tm` object to a string representation.
 *
 * @param timeptr Pointer to the `struct tm` object representing the time.
 * @return A string representing the time.
 */
char            *asctime(const struct tm * timeptr);
/**
 * @brief Converts a calendar time value to a string representation in localtime
 *
 * Identically to asctime(localtime(uint32_t epochTime)).
 *
 * @param timer Pointer to the calendar time value.
 * @return A string representing the calendar time.
 */
char            *ctime (const time_t *timer);

/**
 * @brief Converts a calendar time value to a UTC-based `struct tm` object.
 *
 * @param timer Pointer to the calendar time value.
 * @return Pointer to a `struct tm` object representing the time in UTC.
 */
struct tm       *gmtime(const time_t * timer);

/**
 * @brief Converts a calendar time value to a local time-based `struct tm` object.
 *
 * @param timer Pointer to the calendar time value.
 * @return Pointer to a `struct tm` object representing the local time.
 */
struct tm       *localtime(const time_t * timer);

/**
 * @brief Formats a time as a string according to a format string.
 *
 * This function is a stub in this implementation; the returned size_t is always zero.
 *
 * @param s        Buffer where the formatted string will be stored.
 * @param maxsize  Maximum number of characters to be stored in the buffer.
 * @param format   Format string specifying the format of the output.
 * @param timeptr  Pointer to the `struct tm` object representing the time.
 * @return Always returns zero in this implementation
 */
size_t          strftime(char *s, size_t maxsize, const char *format, const struct tm *timeptr);

/* @} */
#ifdef __cplusplus
}
#endif

#endif              /* TIME_H  */
