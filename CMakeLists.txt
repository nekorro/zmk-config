# Keymap behaviors run only on the central device of a split keyboard.
if((NOT CONFIG_ZMK_SPLIT) OR CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
  target_sources(app PRIVATE src/behavior_layer_alt_tab.c)
endif()
