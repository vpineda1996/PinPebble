#include <pebble.h>

#define WIDTH 144
#define HEIGHT 168

#define MENU 1
#define GAME 2
#define PAUSE 3
#define STOP 4

static int game_state = MENU;
static Window *game_window;

static void game_init();
static void start_game();
static void pause_game();
static void resume_game();
static void stop_game();

// -----------------------------------------------------------------------------------------
// Menu Window

static Window *window;
static TextLayer *text_layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
  game_init();
  start_game();
  game_state = GAME;
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
}


static void pause_handler(ClickRecognizerRef recognizer, void *context) {
  if (game_state == GAME) {
    text_layer_set_text(text_layer, "PAUSE");
    game_state = PAUSE;
  }
}
static void resume_handler(ClickRecognizerRef recognizer, void *context) {
  if (game_state == PAUSE) {
    text_layer_set_text(text_layer, "RESUME");
    game_state = GAME;
  }
}

static void stop_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "BACK TO MENU");
  if (game_state == GAME) {
    stop_game();
    window_stack_pop(game_window);
    game_state = MENU;
  }
}

static void menu_click(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}
static void game_click(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, stop_handler);
  window_single_click_subscribe(BUTTON_ID_UP, pause_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, resume_handler);
}


static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create(GRect(0, 72, bounds.size.w, 20));
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}
static void game_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  text_layer = text_layer_create(GRect(0, 72, bounds.size.w, 20));
  text_layer_set_text(text_layer, "Press a button");
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));
}

static void gane_window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, menu_click);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

// Game Window

static void game_init(void) {

  game_window = window_create();
  window_set_click_config_provider(game_window, game_click);
  window_set_window_handlers(game_window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(game_window, animated);
}

static void start_game() {
   APP_LOG(APP_LOG_LEVEL_DEBUG, "start game");
}

static void pause_game() {
  game_state = PAUSE;
   APP_LOG(APP_LOG_LEVEL_DEBUG, "pause game");
}

static void resume_game() {
  game_state = GAME;
   APP_LOG(APP_LOG_LEVEL_DEBUG, "resume game");
}

static void stop_game() {
   APP_LOG(APP_LOG_LEVEL_DEBUG, "stop game");
}

static void game_deinit(void) {
  window_destroy(game_window);
}


int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
static void tick() {

}

static void render() {

}
