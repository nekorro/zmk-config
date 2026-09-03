# Native keymap regression tests

All fixtures include the real `config/totem.keymap` and drive ZMK's mock scanner
with the keyboard's 38 physical positions. Snapshots specify the expected HID
events, rather than a second implementation of the behaviors.

- `nav-alt-tab`: layer lifetime, repeated Tabs, early layer release, other layers,
  and ownership of a separately held Alt (eight scenarios).
- `home-row-mods`: intentional holds immediately after typing and after tapping
  the same key, all three home-row definitions, same-hand and opposite-hand rolls,
  a fast Shift chord, and Game's Shift+A without a Caps Lock combo.
- `ru-input`: opposite-hand Alt chords for ё/щ/ъ, uppercase Ё with Shift preserved
  while Alt is masked, a deliberate same-hand Alt hold, native Russian punctuation,
  and the remaining English fallback for apostrophe and tilde.

From `zmk/app` in a ZMK v0.3.0 development workspace:

```sh
ZMK_EXTRA_MODULES=/absolute/path/to/zmk-config \
  ./run-test.sh /absolute/path/to/zmk-config/tests
```

The GitHub workflow runs these tests with the dependencies pinned in
`config/west.yml`, alongside the firmware builds. Native tests verify firmware
events. The target OS's language shortcuts, text output and window picker still
need a check after flashing the central device.
