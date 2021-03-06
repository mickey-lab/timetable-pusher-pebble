#include <pebble.h>
#include "win_loading.h"

static Window *s_loading_window;
static TextLayer *s_text_layer;
static StatusBarLayer *s_status_bar;

static void window_load(Window* window);
static void window_unload(Window* window);

void win_loading_create(void) {
    s_loading_window = window_create();
    window_set_background_color(s_loading_window, PBL_IF_COLOR_ELSE(GColorJaegerGreen, GColorWhite));
    window_set_window_handlers(s_loading_window, (WindowHandlers) {
        .load = window_load,
        .unload = window_unload,
    });
    window_stack_push(s_loading_window, true);
}

void win_loading_destroy(void) {
    window_destroy(s_loading_window);
}

Window* get_loading_window(void) {
    return s_loading_window;
}

// -------------------------------------------------------------- //

static void window_load(Window *window) {  
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    s_status_bar = status_bar_layer_create();
    status_bar_layer_set_colors(s_status_bar, 
                                PBL_IF_COLOR_ELSE(GColorJaegerGreen, GColorWhite),
                                PBL_IF_COLOR_ELSE(GColorWhite, GColorBlack));
    status_bar_layer_set_separator_mode(s_status_bar, StatusBarLayerSeparatorModeDotted);
    layer_add_child(window_layer, status_bar_layer_get_layer(s_status_bar));

    s_text_layer = text_layer_create(GRect(0, PBL_IF_RECT_ELSE(68, 78), bounds.size.w, 32));
    text_layer_set_text(s_text_layer, "Loading...");
    text_layer_set_text_color(s_text_layer, PBL_IF_COLOR_ELSE(GColorWhite, GColorBlack));
    text_layer_set_background_color(s_text_layer, GColorClear);
    text_layer_set_font(s_text_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
    text_layer_set_text_alignment(s_text_layer, GTextAlignmentCenter);
    layer_add_child(window_layer, text_layer_get_layer(s_text_layer));
}

static void window_unload(Window *window) {
    status_bar_layer_destroy(s_status_bar);
    text_layer_destroy(s_text_layer);
}