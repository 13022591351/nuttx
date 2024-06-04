#include <nuttx/config.h>

#include <sys/types.h>
#include <assert.h>
#include <debug.h>
#include <inttypes.h>

#include <nuttx/board.h>
#include <nuttx/leds/userled.h>

#include "fmu_v1.h"

/****************************************************************************
 * Private Function Prototypes
 ****************************************************************************/

static userled_set_t userled_supported(FAR const struct userled_lowerhalf_s *lower);
static void userled_setled(FAR const struct userled_lowerhalf_s *lower, int led, bool ledon);
static void userled_setall(FAR const struct userled_lowerhalf_s *lower, userled_set_t ledset);
#ifdef CONFIG_USERLED_LOWER_READSTATE
    static void userled_getall(FAR const struct userled_lowerhalf_s *lower, userled_set_t *ledset);
#endif

/****************************************************************************
 * Private Data
 ****************************************************************************/

static uint32_t g_lednum;

/* This is the user LED lower half driver interface */

static const struct userled_lowerhalf_s g_userled_lower = {
    userled_supported,    /* ll_supported */
    userled_setled,       /* ll_setled */
    userled_setall        /* ll_setall */
#ifdef CONFIG_USERLED_LOWER_READSTATE
    , userled_getall      /* ll_getall */
#endif
};

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Name: userled_supported
 *
 * Description:
 *   Return the set of LEDs supported by the board
 *
 ****************************************************************************/

static userled_set_t userled_supported(FAR const struct userled_lowerhalf_s *lower) {
    ledinfo("BOARD_NLEDS: %02" PRIx32 "\n", g_lednum);
    return (userled_set_t)((1 << g_lednum) - 1);
}

/****************************************************************************
 * Name: userled_setled
 *
 * Description:
 *   Set the current state of one LED
 *
 ****************************************************************************/

static void userled_setled(FAR const struct userled_lowerhalf_s *lower, int led, bool ledon) {
    board_userled(led, ledon);
}

/****************************************************************************
 * Name: userled_setall
 *
 * Description:
 *   Set the state of all LEDs
 *
 ****************************************************************************/

static void userled_setall(FAR const struct userled_lowerhalf_s *lower, userled_set_t ledset) {
    board_userled_all(ledset);
}

#ifdef CONFIG_USERLED_LOWER_READSTATE
/****************************************************************************
 * Name: userled_getall
 *
 * Description:
 *   Get the state of all LEDs
 *
 ****************************************************************************/

static void userled_getall(FAR const struct userled_lowerhalf_s *lower, userled_set_t *ledset) {
    board_userled_getall(ledset);
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: userled_lower_initialize
 *
 * Description:
 *   Initialize the generic LED lower half driver, bind it and register
 *   it with the upper half LED driver as devname.
 *
 ****************************************************************************/

int userled_lower_initialize(FAR const char *devname) {
    g_lednum = board_userled_initialize();
    return userled_register(devname, &g_userled_lower);
}
