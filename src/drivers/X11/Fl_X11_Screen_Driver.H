//
// "$Id$"
//
// Definition of X11 Screen interface
// for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010-2017 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

/**
 \file Fl_X11_Screen_Driver.H
 \brief Definition of X11 Screen interface
 */

#ifndef FL_X11_SCREEN_DRIVER_H
#define FL_X11_SCREEN_DRIVER_H

#include <FL/Fl_Screen_Driver.H>


class Fl_Window;


class FL_EXPORT Fl_X11_Screen_Driver : public Fl_Screen_Driver 
{
    friend class Fl_Screen_Driver;
protected:
  typedef struct {
    short x_org;
    short y_org;
    short width;
    short height;
#if USE_XFT
    float scale;
#endif
  } FLScreenInfo;
  FLScreenInfo screens[MAX_SCREENS];
  float dpi[MAX_SCREENS][2];
  int poll_or_select();
  int poll_or_select_with_delay(double time_to_wait);
  int get_mouse_unscaled(int &xx, int &yy);

public:
#if USE_XFT // scaling does not work without Xft
  float current_xft_dpi; // current value of the Xft.dpi X resource
  virtual APP_SCALING_CAPABILITY rescalable() { return PER_SCREEN_APP_SCALING; }
  virtual float scale(int n) {return screens[n].scale;}
  virtual void scale(int n, float f) { screens[n].scale = f;}
  virtual float desktop_scale_factor();
  int screen_num_unscaled(int x, int y);
#endif
  
  static int ewmh_supported();
  static void copy_image(const unsigned char* data, int W, int H, int destination);
  // --- display management
  virtual void display(const char *disp);
  virtual int visual(int flags);
  // --- screen configuration
  void init_workarea();
  virtual void init();
  virtual int x();
  virtual int y();
  virtual int w();
  virtual int h();
  virtual void screen_xywh(int &X, int &Y, int &W, int &H, int n);
  virtual void screen_dpi(float &h, float &v, int n=0);
  virtual void screen_work_area(int &X, int &Y, int &W, int &H, int n);
  // --- audible output
  virtual void beep(int type);
  // --- global events
  virtual void flush();
  virtual double wait(double time_to_wait);
  virtual int ready();
  virtual void grab(Fl_Window* win);
  // --- global colors
  virtual int parse_color(const char* p, uchar& r, uchar& g, uchar& b);
  virtual void get_system_colors();
  virtual const char *get_system_scheme();
  // --- global timers
  virtual void add_timeout(double time, Fl_Timeout_Handler cb, void *argp);
  virtual void repeat_timeout(double time, Fl_Timeout_Handler cb, void *argp);
  virtual int has_timeout(Fl_Timeout_Handler cb, void *argp);
  virtual void remove_timeout(Fl_Timeout_Handler cb, void *argp);
  virtual int dnd(int unused);
  virtual int compose(int &del);
  virtual void compose_reset();
  virtual int text_display_can_leak();
  virtual Fl_RGB_Image *read_win_rectangle(uchar *p, int X, int Y, int w, int h, int alpha);
  virtual int get_mouse(int &x, int &y);
  virtual void enable_im();
  virtual void disable_im();
  virtual void open_display_platform();
  virtual void close_display();
  // --- compute dimensions of an Fl_Offscreen
  virtual void offscreen_size(Fl_Offscreen o, int &width, int &height);
};


#endif // FL_X11_SCREEN_DRIVER_H

//
// End of "$Id$".
//
