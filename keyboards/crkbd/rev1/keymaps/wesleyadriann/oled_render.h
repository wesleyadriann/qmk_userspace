#ifndef OLED_RENDER_H
#define OLED_RENDER_H

void oled_render_layer_state(void);
void oled_render_capslock(void);
void oled_render_keylog(void);
void oled_render_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);

#endif // OLED_RENDER_H
