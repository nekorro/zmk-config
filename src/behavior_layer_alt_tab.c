/* SPDX-License-Identifier: MIT */

#define DT_DRV_COMPAT zmk_behavior_layer_alt_tab

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <dt-bindings/zmk/keys.h>
#include <zmk/behavior.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/keymap.h>

#if DT_HAS_COMPAT_STATUS_OKAY(DT_DRV_COMPAT)

struct layer_alt_tab_config {
    zmk_keymap_layer_id_t release_layer;
};

struct layer_alt_tab_data {
    bool alt_pressed;
};

static int on_pressed(struct zmk_behavior_binding *binding,
                      struct zmk_behavior_binding_event event) {
    const struct device *dev = zmk_behavior_get_binding(binding->behavior_dev);
    const struct layer_alt_tab_config *config = dev->config;
    struct layer_alt_tab_data *data = dev->data;

    /* Own exactly one Alt press per layer activation, even if another Alt is held. */
    if (!data->alt_pressed && zmk_keymap_layer_active(config->release_layer)) {
        data->alt_pressed = true;
        raise_zmk_keycode_state_changed_from_encoded(LALT, true, event.timestamp);
    }

    return raise_zmk_keycode_state_changed_from_encoded(TAB, true, event.timestamp);
}

static int on_released(struct zmk_behavior_binding *binding,
                       struct zmk_behavior_binding_event event) {
    /* Alt belongs to the layer session; this physical key owns only Tab. */
    return raise_zmk_keycode_state_changed_from_encoded(TAB, false, event.timestamp);
}

static const struct behavior_driver_api layer_alt_tab_driver_api = {
    .binding_pressed = on_pressed,
    .binding_released = on_released,
#if IS_ENABLED(CONFIG_ZMK_BEHAVIOR_METADATA)
    .get_parameter_metadata = zmk_behavior_get_empty_param_metadata,
#endif
};

#define ALT_TAB_INST(n)                                                                            \
    BUILD_ASSERT(DT_INST_PROP(n, release_layer) < ZMK_KEYMAP_LAYERS_LEN, "Invalid release layer");   \
    static const struct layer_alt_tab_config config_##n = {                                       \
        .release_layer = DT_INST_PROP(n, release_layer),                                           \
    };                                                                                            \
    static struct layer_alt_tab_data data_##n;                                                     \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, &data_##n, &config_##n, POST_KERNEL,                      \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &layer_alt_tab_driver_api);

DT_INST_FOREACH_STATUS_OKAY(ALT_TAB_INST)

#define GET_DEV(n) DEVICE_DT_INST_GET(n),
static const struct device *const devices[] = {DT_INST_FOREACH_STATUS_OKAY(GET_DEV)};

static int layer_state_changed_listener(const zmk_event_t *eh) {
    const struct zmk_layer_state_changed *event = as_zmk_layer_state_changed(eh);
    if (event == NULL || event->state) {
        return ZMK_EV_EVENT_BUBBLE;
    }

    for (size_t i = 0; i < ARRAY_SIZE(devices); i++) {
        const struct layer_alt_tab_config *config = devices[i]->config;
        struct layer_alt_tab_data *data = devices[i]->data;

        if (data->alt_pressed && event->layer == config->release_layer) {
            data->alt_pressed = false;
            raise_zmk_keycode_state_changed_from_encoded(LALT, false, event->timestamp);
        }
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(layer_alt_tab, layer_state_changed_listener);
ZMK_SUBSCRIPTION(layer_alt_tab, zmk_layer_state_changed);

#endif
