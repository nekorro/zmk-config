# Caps Lock D+K Design

## Intent

Enable Caps Lock with a simultaneous press of the physical `D` and `K` keys, so it is available from the home row without reaching for the Fn layer.

## Behavior

- On the EN layer, pressing positions 12 (`D`) and 17 (`K`) within 50 ms sends one Caps Lock key press and release.
- On the RU layer, the same physical positions (`В` and `Л`) provide the same chord.
- The chord is disabled on Sym, RU Sym, Nav Dig, Fn, Game, and Game+.
- The existing Caps Lock key on Fn remains available.

## Approach

Use a ZMK combo with `key-positions = <12 17>`, the default 50 ms timeout, and `layers = <LAYER_EN LAYER_RU>`. A global combo was rejected because those positions have unrelated meanings on other layers; separate EN and RU combos were rejected as unnecessary duplication.

