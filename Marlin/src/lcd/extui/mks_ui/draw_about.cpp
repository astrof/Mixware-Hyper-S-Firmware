/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "../../../inc/MarlinConfigPre.h"

#if HAS_TFT_LVGL_UI

#include "draw_ui.h"
#include <lv_conf.h>

#include "../../../inc/MarlinConfig.h"

extern lv_group_t *g;
static lv_obj_t *scr;
static lv_obj_t *fw_type, *board;

enum { ID_A_RETURN = 1 };

static void event_handler(lv_obj_t *obj, lv_event_t event) {
  if (event != LV_EVENT_RELEASED) return;
  switch (obj->mks_obj_id) {
    case ID_A_RETURN:
      clear_cur_ui();
      draw_return_ui();
      break;
  }
}

void lv_draw_about() {
  #if DISABLED(TFT_MIXWARE_LVGL_UI)
    scr = lv_screen_create(ABOUT_UI);

    lv_big_button_create(scr, "F:/bmp_return.bin", common_menu.text_back, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight, event_handler, ID_A_RETURN);
    fw_type = lv_label_create(scr, "Firmware: Marlin " SHORT_BUILD_VERSION);
  #else
    scr = lv_screen_create(ABOUT_UI, MTR.about);

    MUI.page_button_return(scr, event_handler, ID_A_RETURN);
    fw_type = lv_label_create(scr, "Firmware: Mixware Hyper S V1.1.08FU");
    lv_obj_t *fw_type_2 = lv_label_create(scr, "(Based on Marlin " SHORT_BUILD_VERSION ")");
    lv_obj_align(fw_type_2, nullptr, LV_ALIGN_CENTER, 0, -4);
  #endif

  lv_obj_align(fw_type, nullptr, LV_ALIGN_CENTER, 0, -20);

  board = lv_label_create(scr, "Board: " BOARD_INFO_NAME);
  lv_obj_align(board, nullptr, LV_ALIGN_CENTER, 0, -60);
}

void lv_clear_about() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI
