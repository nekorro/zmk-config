#pragma once

/* Keep these indices in the same order as the keymap's layer nodes. */
#define LAYER_EN 0
#define LAYER_RU 1
#define LAYER_SYM 2
#define LAYER_RU_SYM 3
#define LAYER_NAV_DIG 4
#define LAYER_FN 5
#define LAYER_GAME 6
#define LAYER_GAME_EXTRA 7

#define HRM_TAPPING_TERM_MS 280
/* A deliberate hold must work after typing or tapping the same key. */
#define HRM_REQUIRE_PRIOR_IDLE_MS 0
#define HRM_QUICK_TAP_MS 0

/* Physical positions, including the three thumb keys on each hand. */
#define LEFT_HAND_POSITIONS 0 1 2 3 4 10 11 12 13 14 20 21 22 23 24 25 32 33 34
#define RIGHT_HAND_POSITIONS 5 6 7 8 9 15 16 17 18 19 26 27 28 29 30 31 35 36 37

#define HRM_COMMON_PROPERTIES \
    flavor = "balanced"; \
    tapping-term-ms = <HRM_TAPPING_TERM_MS>; \
    require-prior-idle-ms = <HRM_REQUIRE_PRIOR_IDLE_MS>; \
    quick-tap-ms = <HRM_QUICK_TAP_MS>; \
    hold-trigger-on-release;
