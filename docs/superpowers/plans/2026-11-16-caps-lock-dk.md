# Caps Lock D+K Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a layer-safe `D+K` Caps Lock chord to the EN and RU typing layers.

**Architecture:** Define one ZMK combo over physical positions 12 and 17, filtered to the two base typing layers. Exercise the real keymap through ZMK's native mock scanner.

**Tech Stack:** ZMK v0.3.0 devicetree, Zephyr `native_posix_64` tests

**Spec:** `docs/superpowers/specs/2026-11-16-caps-lock-dk-design.md`

## Global Constraints

- The combo timeout is 50 ms.
- The chord works on EN and RU only.
- The Fn Caps Lock binding remains unchanged.

## Review Focus

- Both EN and RU base layers emit exactly one Caps Lock press/release.
- The physical positions do not emit their home-row modifiers when the combo resolves.
- Game keeps the ordinary bindings at positions 12 and 17.
- Existing home-row-mod, Russian input, and Nav Alt+Tab behavior remains unchanged.
- The production firmware devicetree compiles for the dongle target.

---

### Task 1: Caps Lock chord

**Files:**
- Create: `tests/caps-lock-combo/native_posix_64.keymap`
- Create: `tests/caps-lock-combo/events.patterns`
- Create: `tests/caps-lock-combo/keycode_events.snapshot`
- Modify: `config/totem.keymap`
- Modify: `tests/README.md`
- Modify: `docs/typing.md`

**Interfaces:**
- Consumes: `LAYER_EN`, `LAYER_RU`, and the 38-position Totem keymap.
- Produces: a Caps Lock combo on physical positions 12 and 17, limited to layers 0 and 1.

- [ ] **Step 1: Write the failing native test**

Add scenarios for the EN combo, switching to RU and using the same combo, and entering Game where positions 12 and 17 must retain their ordinary bindings.

- [ ] **Step 2: Run the focused test to verify it fails**

Run: `wsl -d Ubuntu -- bash work/build-native.sh caps-lock-combo`

Expected: FAIL because the real keymap emits `D`/`K` instead of Caps Lock.

- [ ] **Step 3: Add the ZMK combo and update user-facing documentation**

Define one `zmk,combos` child with `bindings = <&kp CAPSLOCK>`, `key-positions = <12 17>`, `timeout-ms = <50>`, and `layers = <LAYER_EN LAYER_RU>`.

- [ ] **Step 4: Run the focused test and all existing native fixtures**

Run each fixture through `work/build-native.sh`: `caps-lock-combo`, `home-row-mods`, `nav-alt-tab`, and `ru-input`.

Expected: all four commands exit 0 with no snapshot diff.

- [ ] **Step 5: Build the dongle firmware configuration**

Run the repository's existing firmware build workflow or its equivalent local build for `xiao_ble//zmk` with `totem_dongle dongle_screen`.

Expected: the devicetree and firmware build complete successfully.

- [ ] **Step 6: Commit and push**

Commit the implementation, tests, spec, plan, and documentation, then push `HEAD` to `origin/ruen-hm-opt` using the authenticated GitHub CLI credential helper.

