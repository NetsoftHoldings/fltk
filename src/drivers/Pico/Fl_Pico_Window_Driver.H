//
// "$Id: Fl_Pico_Window_Driver.H 11017 2016-01-20 21:40:12Z matt $"
//
// Definition of Pico Window interface
// for the Fast Light Tool Kit (FLTK).
//
// Copyright 2010-2016 by Bill Spitzak and others.
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
 \file Fl_Pico_Window_Driver.H
 \brief Definition of Pico Window interface.
 */

#ifndef FL_PICO_WINDOW_DRIVER_H
#define FL_PICO_WINDOW_DRIVER_H

#include <FL/Fl_Window_Driver.H>


class FL_EXPORT Fl_Pico_Window_Driver : public Fl_Window_Driver
{
public:
  Fl_Pico_Window_Driver(Fl_Window *win);
  virtual ~Fl_Pico_Window_Driver();
};


#endif // FL_PICO_WINDOW_DRIVER_H

//
// End of "$Id: Fl_Pico_Window_Driver.H 11017 2016-01-20 21:40:12Z matt $".
//