/* ow_ui.c
 *
 * Copyright (c) 2011 The ottos_ui project.
 *
 * This work is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This work is distributed in the hope that it will be useful, but without
 * any warranty; without even the implied warranty of merchantability or
 * fitness for a particular purpose. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 *
 *  Created on: 25.01.2012
 *      Author: Florian Gopp (go.goflo@gmail.com)
 */

#include "ow_ui.h"

#include <api/graphics.h>
#include <api/bitmap.h>
#include <api/colors.h>

#include <ottos/kernel.h>
#include <stdlib.h>


int bmp_size = 1094;
uint8_t pic[] = {
 0x42, 0x4D, 0x46, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x04, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0x00, 0xC0, 0xDC, 0xC0, 0x00, 0xF0, 0xCA, 0xA6, 0x00, 0x00, 0x20, 0x40, 0x00, 0x00, 0x20, 0x60, 0x00, 0x00, 0x20, 0x80, 0x00, 0x00, 0x20, 0xA0, 0x00, 0x00, 0x20, 0xC0, 0x00, 0x00, 0x20, 0xE0, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x20, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x40, 0x60, 0x00, 0x00, 0x40, 0x80, 0x00, 0x00, 0x40, 0xA0, 0x00, 0x00, 0x40, 0xC0, 0x00, 0x00, 0x40, 0xE0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x20, 0x00, 0x00, 0x60, 0x40, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x60, 0x80, 0x00, 0x00, 0x60, 0xA0, 0x00, 0x00, 0x60, 0xC0, 0x00, 0x00, 0x60, 0xE0, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x20, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x80, 0x60, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0xA0, 0x00, 0x00, 0x80, 0xC0, 0x00, 0x00, 0x80, 0xE0, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x00, 0xA0, 0x20, 0x00, 0x00, 0xA0, 0x40, 0x00, 0x00, 0xA0, 0x60, 0x00, 0x00, 0xA0, 0x80, 0x00, 0x00, 0xA0, 0xA0, 0x00, 0x00, 0xA0, 0xC0, 0x00, 0x00, 0xA0, 0xE0, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0x20, 0x00, 0x00, 0xC0, 0x40, 0x00, 0x00, 0xC0, 0x60, 0x00, 0x00, 0xC0, 0x80, 0x00, 0x00, 0xC0, 0xA0, 0x00, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0xE0, 0x20, 0x00, 0x00, 0xE0, 0x40, 0x00, 0x00, 0xE0, 0x60, 0x00, 0x00, 0xE0, 0x80, 0x00, 0x00, 0xE0, 0xA0, 0x00, 0x00, 0xE0, 0xC0, 0x00, 0x00, 0xE0, 0xE0, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x20, 0x00, 0x40, 0x00, 0x40, 0x00, 0x40, 0x00, 0x60, 0x00, 0x40, 0x00, 0x80, 0x00, 0x40, 0x00, 0xA0, 0x00, 0x40, 0x00, 0xC0, 0x00, 0x40, 0x00, 0xE0, 0x00, 0x40, 0x20, 0x00, 0x00, 0x40, 0x20, 0x20, 0x00, 0x40, 0x20, 0x40, 0x00, 0x40, 0x20, 0x60, 0x00, 0x40, 0x20, 0x80, 0x00, 0x40, 0x20, 0xA0, 0x00, 0x40, 0x20, 0xC0, 0x00, 0x40, 0x20, 0xE0, 0x00, 0x40, 0x40, 0x00, 0x00, 0x40, 0x40, 0x20, 0x00, 0x40, 0x40, 0x40, 0x00, 0x40, 0x40, 0x60, 0x00, 0x40, 0x40, 0x80, 0x00, 0x40, 0x40, 0xA0, 0x00, 0x40, 0x40, 0xC0, 0x00, 0x40, 0x40, 0xE0, 0x00, 0x40, 0x60, 0x00, 0x00, 0x40, 0x60, 0x20, 0x00, 0x40, 0x60, 0x40, 0x00, 0x40, 0x60, 0x60, 0x00, 0x40, 0x60, 0x80, 0x00, 0x40, 0x60, 0xA0, 0x00, 0x40, 0x60, 0xC0, 0x00, 0x40, 0x60, 0xE0, 0x00, 0x40, 0x80, 0x00, 0x00, 0x40, 0x80, 0x20, 0x00, 0x40, 0x80, 0x40, 0x00, 0x40, 0x80, 0x60, 0x00, 0x40, 0x80, 0x80, 0x00, 0x40, 0x80, 0xA0, 0x00, 0x40, 0x80, 0xC0, 0x00, 0x40, 0x80, 0xE0, 0x00, 0x40, 0xA0, 0x00, 0x00, 0x40, 0xA0, 0x20, 0x00, 0x40, 0xA0, 0x40, 0x00, 0x40, 0xA0, 0x60, 0x00, 0x40, 0xA0, 0x80, 0x00, 0x40, 0xA0, 0xA0, 0x00, 0x40, 0xA0, 0xC0, 0x00, 0x40, 0xA0, 0xE0, 0x00, 0x40, 0xC0, 0x00, 0x00, 0x40, 0xC0, 0x20, 0x00, 0x40, 0xC0, 0x40, 0x00, 0x40, 0xC0, 0x60, 0x00, 0x40, 0xC0, 0x80, 0x00, 0x40, 0xC0, 0xA0, 0x00, 0x40, 0xC0, 0xC0, 0x00, 0x40, 0xC0, 0xE0, 0x00, 0x40, 0xE0, 0x00, 0x00, 0x40, 0xE0, 0x20, 0x00, 0x40, 0xE0, 0x40, 0x00, 0x40, 0xE0, 0x60, 0x00, 0x40, 0xE0, 0x80, 0x00, 0x40, 0xE0, 0xA0, 0x00, 0x40, 0xE0, 0xC0, 0x00, 0x40, 0xE0, 0xE0, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 0x80, 0x00, 0x40, 0x00, 0x80, 0x00, 0x60, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0xA0, 0x00, 0x80, 0x00, 0xC0, 0x00, 0x80, 0x00, 0xE0, 0x00, 0x80, 0x20, 0x00, 0x00, 0x80, 0x20, 0x20, 0x00, 0x80, 0x20, 0x40, 0x00, 0x80, 0x20, 0x60, 0x00, 0x80, 0x20, 0x80, 0x00, 0x80, 0x20, 0xA0, 0x00, 0x80, 0x20, 0xC0, 0x00, 0x80, 0x20, 0xE0, 0x00, 0x80, 0x40, 0x00, 0x00, 0x80, 0x40, 0x20, 0x00, 0x80, 0x40, 0x40, 0x00, 0x80, 0x40, 0x60, 0x00, 0x80, 0x40, 0x80, 0x00, 0x80, 0x40, 0xA0, 0x00, 0x80, 0x40, 0xC0, 0x00, 0x80, 0x40, 0xE0, 0x00, 0x80, 0x60, 0x00, 0x00, 0x80, 0x60, 0x20, 0x00, 0x80, 0x60, 0x40, 0x00, 0x80, 0x60, 0x60, 0x00, 0x80, 0x60, 0x80, 0x00, 0x80, 0x60, 0xA0, 0x00, 0x80, 0x60, 0xC0, 0x00, 0x80, 0x60, 0xE0, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x80, 0x20, 0x00, 0x80, 0x80, 0x40, 0x00, 0x80, 0x80, 0x60, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0xA0, 0x00, 0x80, 0x80, 0xC0, 0x00, 0x80, 0x80, 0xE0, 0x00, 0x80, 0xA0, 0x00, 0x00, 0x80, 0xA0, 0x20, 0x00, 0x80, 0xA0, 0x40, 0x00, 0x80, 0xA0, 0x60, 0x00, 0x80, 0xA0, 0x80, 0x00, 0x80, 0xA0, 0xA0, 0x00, 0x80, 0xA0, 0xC0, 0x00, 0x80, 0xA0, 0xE0, 0x00, 0x80, 0xC0, 0x00, 0x00, 0x80, 0xC0, 0x20, 0x00, 0x80, 0xC0, 0x40, 0x00, 0x80, 0xC0, 0x60, 0x00, 0x80, 0xC0, 0x80, 0x00, 0x80, 0xC0, 0xA0, 0x00, 0x80, 0xC0, 0xC0, 0x00, 0x80, 0xC0, 0xE0, 0x00, 0x80, 0xE0, 0x00, 0x00, 0x80, 0xE0, 0x20, 0x00, 0x80, 0xE0, 0x40, 0x00, 0x80, 0xE0, 0x60, 0x00, 0x80, 0xE0, 0x80, 0x00, 0x80, 0xE0, 0xA0, 0x00, 0x80, 0xE0, 0xC0, 0x00, 0x80, 0xE0, 0xE0, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x20, 0x00, 0xC0, 0x00, 0x40, 0x00, 0xC0, 0x00, 0x60, 0x00, 0xC0, 0x00, 0x80, 0x00, 0xC0, 0x00, 0xA0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xC0, 0x00, 0xE0, 0x00, 0xC0, 0x20, 0x00, 0x00, 0xC0, 0x20, 0x20, 0x00, 0xC0, 0x20, 0x40, 0x00, 0xC0, 0x20, 0x60, 0x00, 0xC0, 0x20, 0x80, 0x00, 0xC0, 0x20, 0xA0, 0x00, 0xC0, 0x20, 0xC0, 0x00, 0xC0, 0x20, 0xE0, 0x00, 0xC0, 0x40, 0x00, 0x00, 0xC0, 0x40, 0x20, 0x00, 0xC0, 0x40, 0x40, 0x00, 0xC0, 0x40, 0x60, 0x00, 0xC0, 0x40, 0x80, 0x00, 0xC0, 0x40, 0xA0, 0x00, 0xC0, 0x40, 0xC0, 0x00, 0xC0, 0x40, 0xE0, 0x00, 0xC0, 0x60, 0x00, 0x00, 0xC0, 0x60, 0x20, 0x00, 0xC0, 0x60, 0x40, 0x00, 0xC0, 0x60, 0x60, 0x00, 0xC0, 0x60, 0x80, 0x00, 0xC0, 0x60, 0xA0, 0x00, 0xC0, 0x60, 0xC0, 0x00, 0xC0, 0x60, 0xE0, 0x00, 0xC0, 0x80, 0x00, 0x00, 0xC0, 0x80, 0x20, 0x00, 0xC0, 0x80, 0x40, 0x00, 0xC0, 0x80, 0x60, 0x00, 0xC0, 0x80, 0x80, 0x00, 0xC0, 0x80, 0xA0, 0x00, 0xC0, 0x80, 0xC0, 0x00, 0xC0, 0x80, 0xE0, 0x00, 0xC0, 0xA0, 0x00, 0x00, 0xC0, 0xA0, 0x20, 0x00, 0xC0, 0xA0, 0x40, 0x00, 0xC0, 0xA0, 0x60, 0x00, 0xC0, 0xA0, 0x80, 0x00, 0xC0, 0xA0, 0xA0, 0x00, 0xC0, 0xA0, 0xC0, 0x00, 0xC0, 0xA0, 0xE0, 0x00, 0xC0, 0xC0, 0x00, 0x00, 0xC0, 0xC0, 0x20, 0x00, 0xC0, 0xC0, 0x40, 0x00, 0xC0, 0xC0, 0x60, 0x00, 0xC0, 0xC0, 0x80, 0x00, 0xC0, 0xC0, 0xA0, 0x00, 0xF0, 0xFB, 0xFF, 0x00, 0xA4, 0xA0, 0xA0, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFC, 0xFC, 0xFF, 0xFF, 0xFC, 0xFC, 0xF9, 0xF9, 0xFF, 0xFF, 0xF9, 0xF9, 0xFF, 0xFF
};

/*
void video_bmp_test_array() {
  void* framebuffer = malloc(3200000);  // ~ 3MB for the frame buffer (1024 * 768 * 4)
  RastPort *rp;

  // bitmap stuff
  RGBA* bmp;
  BITMAP_FILEHEADER* bmpFileHeader = (BITMAP_FILEHEADER*)malloc(sizeof(BITMAP_FILEHEADER));
  BITMAP_HEADER* bmpHeader = (BITMAP_HEADER*)malloc(sizeof(BITMAP_HEADER));

  // init video
  video_init(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
  rp = graphics_init(framebuffer, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, BM_RGB16);
  video_attach_framebuffer(0, rp->drawable.bitmap);

  graphics_move_to(rp, 0, 0);
  graphics_set_color(rp, 0x3e31a2);
  graphics_draw_rect(rp, WIDTH, HEIGHT);

  bmp = graphics_parse_bmp_picture_array(&pic, bmp_size, bmpFileHeader, bmpHeader);
  graphics_draw_picture(200, 200, bmpHeader, bmp);
}

void video_bmp_test_file() {
  // filesystem & fat stuff
  void* framebuffer = malloc(3200000);  // ~ 3MB for the frame buffer (1024 * 768 * 4)
  void* file;
  RastPort *rp;

  // bitmap stuff
  RGBA* bmp;
  BITMAP_FILEHEADER* bmpFileHeader = (BITMAP_FILEHEADER*)malloc(sizeof(BITMAP_FILEHEADER));
  BITMAP_HEADER* bmpHeader = (BITMAP_HEADER*)malloc(sizeof(BITMAP_HEADER));

  int file_length = 0;
  char* file_content = NULL;
  int i = 0;

  // load bmp file: sun.bmp | katze.bmp | katze_.bmp
  //fs_init();
  file = fl_fopen("/test8.bmp", "r");

  fl_fseek(file, 0, SEEK_END);
  file_length = fl_ftell(file);
  fl_fseek(file, 0, SEEK_SET);

  file_content = malloc(sizeof(char) * file_length);
  fl_fread(file_content, sizeof(char), file_length, file);

  fl_fclose(file);
  for(i = 0; i < file_length; i++) {
    char output[2] = {'\0'};
    sprintf(output, "%c\0", file_content[i]);
    kernel_print(output);
    if(i % 50 == 0) {
      kernel_print("\r\n");
    }
  }

  // init video
  video_init(RESOLUTION_WIDTH, RESOLUTION_HEIGHT);
  rp = graphics_init(framebuffer, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, BM_RGB16);
  video_attach_framebuffer(0, rp->drawable.bitmap);

  graphics_move_to(rp, 0, 0);
  graphics_set_color(rp, 0x3e31a2);
  graphics_draw_rect(rp, WIDTH, HEIGHT);

  //bmp = graphics_parse_bmp_picture(file, bmpFileHeader, bmpHeader);
  bmp = graphics_parse_bmp_picture_array(file_content, file_length, bmpFileHeader, bmpHeader);
  graphics_draw_picture(200, 200, bmpHeader, bmp);
}
*/

void video_test() {
  int i = 0;
  int x, y, u;
  RastPort *rp;
  void* framebuffer = malloc(3200000);
  GRAPH_DATA graph_data[20];


  // init
  rp = graphics_init(framebuffer, RESOLUTION_WIDTH , RESOLUTION_HEIGHT, BM_RGB16);
  //video_attach_framebuffer(0, rp->drawable.bitmap);

  // also set it to the tv out (top-left corner of same data)
  //video_attach_framebuffer(VID_VID2 | VID_TVOUT, rp->drawable.bitmap);

  // set background
  graphics_move_to(rp, 0, 0);
  graphics_set_color(rp, COLOR_LightCyan);
  graphics_draw_rect(rp, RESOLUTION_WIDTH, RESOLUTION_HEIGHT);

  // set heading
  graphics_set_color(rp, COLOR_DarkSlateGray);
  graphics_move_to(rp, 20, 70);
  graphics_draw_string(rp, "Weatterstation powered by OttOS", 3);

  // set temperature
  graphics_move_to(rp, 20, 160);
  graphics_draw_string(rp, "24.5 �C", 3);

  // draw temperature graph
  graphics_move_to(rp, 160, 80);
  graphics_set_color(rp, COLOR_LemonChiffon);
  graphics_draw_rect(rp, 600, 200);
  graphics_set_color(rp, COLOR_Black);
  graphics_draw_line(rp, 165, 225, 795, 225, 1);
  graphics_draw_line(rp, 165, 225, 165, 35, 1);
  graphics_set_color(rp, COLOR_Red);
  graphics_draw_line(rp, 166, 160, 490, 100, 1);
  graphics_draw_line(rp, 390, 100, 790, 130, 1);

  for (i = 0; i < 20; i++) {
    graph_data[i].data = i - 4;
    graph_data[i].timestamp.hour = 10;
    graph_data[i].timestamp.minute = i;
    graph_data[i].timestamp.second = 0;
  }

  graphics_draw_graph(rp, graph_data, 20, 1, 400, 680, COLOR_Lime, COLOR_Red);

  // set humanity
  graphics_move_to(rp, 10, 300);
  graphics_draw_string(rp, "60 %", 6);
  graphics_redraw(rp);

/*

  graphics_set_color(rp, 0x00ffff);
  graphics_move_to(rp, 20, 20);
  graphics_draw_string(rp, "Hello this weather station is powered by OttOS!",1);
  graphics_set_color(rp, 0xffff00);
  graphics_move_to(rp, 80, 40);
  graphics_draw_string(rp, "Hello this weather station is powered by OttOS!",3);
  graphics_set_color(rp, 0xff00ff);
  graphics_move_to(rp, 500, 300);
  graphics_draw_string(rp, "...:: OttOS ::...",4);

  // draw line
  graphics_draw_line(rp, 300, 300, 400, 600, 1);
  graphics_draw_line(rp, 600, 300, 400, 100, 1);
  graphics_draw_line(rp, 400, 300, 200, 600, 1);

  graphics_set_color(rp, COLOR_Gold);

  // draw circle
  graphics_draw_ellipse(rp, 200, 200, 60, 60*GRAPHICS_RESOLUTION_CORRECTION_FACTOR);
  graphics_move_to(rp, 10, 10);
  graphics_draw_rect(rp, 200, 200);
*/

  /*
  // write 'HELLO' with rectangles
  x = 80;
  y = 200;
  u = 10;
  graphics_set_color(rp, 0xffffff);

  // write H
  graphics_move_to(rp, x, y);
  graphics_draw_rect(rp, u, 5*u);
  graphics_move_to(rp, x+3*u, y);
  graphics_draw_rect(rp, u, 5*u);
  graphics_move_to(rp, x+u, y+2*u);
  graphics_draw_rect(rp, 2*u, u);

  x += 5*u;
  // write E
  graphics_move_to(rp, x, y);
  graphics_draw_rect(rp, u, 5*u);
  graphics_move_to(rp, x+u, y);
  graphics_draw_rect(rp, 3*u, u);
  graphics_move_to(rp, x+u, y+2*u);
  graphics_draw_rect(rp, 2*u, u);
  graphics_move_to(rp, x+u, y+4*u);
  graphics_draw_rect(rp, 3*u, u);

  x += 5*u;
  // write L
  graphics_move_to(rp, x, y);
  graphics_draw_rect(rp, u, 5*u);
  graphics_move_to(rp, x+u, y+4*u);
  graphics_draw_rect(rp, 3*u, u);

  x += 5*u;
  // write L
  graphics_move_to(rp, x, y);
  graphics_draw_rect(rp, u, 5*u);
  graphics_move_to(rp, x+u, y+4*u);
  graphics_draw_rect(rp, 3*u, u);

  x += 5*u;
  // write O
  graphics_move_to(rp, x, y);
  graphics_draw_rect(rp, u, 5*u);
  graphics_move_to(rp, x+3*u, y);
  graphics_draw_rect(rp, u, 5*u);
  graphics_move_to(rp, x+u, y);
  graphics_draw_rect(rp, 2*u, u);
  graphics_move_to(rp, x+u, y+4*u);
  graphics_draw_rect(rp, 2*u, u);

  x += 5*u;
  // write !
  graphics_move_to(rp, x, y);
  graphics_draw_rect(rp, u, 3*u);
  graphics_move_to(rp, x, y+4*u);
  graphics_draw_rect(rp, u, u);
  */

  return;
}

