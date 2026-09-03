# Nav Alt+Tab regression test

This test includes the actual `config/totem.keymap` and exercises eight scenarios
using ZMK's native mock scanner. The expected keycode events are written explicitly
in `keycode_events.snapshot`.

It checks ordinary navigation without Alt, repeated switching, releasing MO4
before Tab, both existing Tab keys, an intervening Fn layer, ownership of a
separately held Alt, an unused MO4 with physical Alt, and the Russian base layer.

Run with a ZMK v0.3.0 development environment, from `zmk/app`:

```sh
ZMK_EXTRA_MODULES=/absolute/path/to/zmk-config \
  ./run-test.sh /absolute/path/to/zmk-config/tests/nav-alt-tab
```

This verifies firmware events. Checking the host's window picker still requires
flashing the keyboard's central device and trying it on the target computer.
