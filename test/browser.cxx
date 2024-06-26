//
// "$Id$"
//
// Browser test program for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2010 by Bill Spitzak and others.
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

/*
This is a test of how the browser draws lines.
This is a second line.
This is a third.

That was a blank line above this.

@r@_Right justify
@c@_Center justify
@_Left justify

@bBold text
@iItalic text
@b@iBold Italic
@fFixed width
@f@bBold Fixed
@f@iItalic Fixed
@f@i@bBold Italic Fixed
@lLarge
@l@bLarge bold
@sSmall
@s@bSmall bold
@s@iSmall italic
@s@i@bSmall italic bold
@uunderscore
@C1RED
@C2Green
@C4Blue

	You should try different browser types:
	Fl_Browser
	Fl_Select_Browser
	Fl_Hold_Browser
	Fl_Multi_Browser
*/

#include <FL/Fl.H>
#include <FL/Fl_Select_Browser.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/fl_ask.H>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

Fl_Select_Browser *browser;
Fl_Button	*top,
		*bottom,
		*middle,
		*visible,
		*swap,
		*sort;
Fl_Choice       *btype;
Fl_Choice       *wtype;
Fl_Int_Input	*field;

typedef struct {
  const char *name;
  Fl_When wvalue;
} WhenItem;

// FL_WHEN chooser..
WhenItem when_items[] = {
  { "FL_WHEN_NEVER",             FL_WHEN_NEVER },
  { "FL_WHEN_CHANGED",           FL_WHEN_CHANGED },
  { "FL_WHEN_NOT_CHANGED",       FL_WHEN_NOT_CHANGED },
  { "FL_WHEN_RELEASE",           FL_WHEN_RELEASE },
  { "FL_WHEN_RELEASE_ALWAYS",    FL_WHEN_RELEASE_ALWAYS },
  { "FL_WHEN_ENTER_KEY",         FL_WHEN_ENTER_KEY },
  { "FL_WHEN_ENTER_KEY_ALWAYS",  FL_WHEN_ENTER_KEY_ALWAYS },
  { "FL_WHEN_ENTER_KEY_CHANGED", FL_WHEN_ENTER_KEY_CHANGED },
  { "FL_WHEN_ENTER_KEY + FL_WHEN_RELEASE_ALWAYS", Fl_When(int(FL_WHEN_ENTER_KEY_CHANGED)+int(FL_WHEN_RELEASE_ALWAYS)) }
  // TODO: Perhaps other FL_WHEN_* combos are relevant
};

void b_cb(Fl_Widget* o, void*) {
  printf("callback, selection = %d, event_clicks = %d\n",
	 ((Fl_Browser*)o)->value(), Fl::event_clicks());
}

void show_cb(Fl_Widget *o, void *) {
  int line = atoi(field->value());

  if (!line) {
    fl_alert("Please enter a number in the text field\n"
             "before clicking on the buttons.");
    return;
  }

  if (o == top)
    browser->topline(line);
  else if (o == bottom)
    browser->bottomline(line);
  else if (o == middle)
    browser->middleline(line);
  else
    browser->make_visible(line);
}

void swap_cb(Fl_Widget *, void *) {
  int a = -1, b = -1;
  for ( int t=0; t<browser->size(); t++ ) {	// find two selected items
    if ( browser->selected(t) ) {
      if ( a < 0 )
	{ a = t; }
      else 
	{ b = t; break; }
    }
  }
  browser->swap(a, b);				// swap them
}

void sort_cb(Fl_Widget *, void *) {
  browser->sort(FL_SORT_ASCENDING);
}

void btype_cb(Fl_Widget *, void *) {
  for ( int t=1; t<=browser->size(); t++ ) browser->select(t,0);
  browser->select(1,0);		// leave focus box on first line
       if ( strcmp(btype->text(),"Normal")==0) browser->type(FL_NORMAL_BROWSER);
  else if ( strcmp(btype->text(),"Select")==0) browser->type(FL_SELECT_BROWSER);
  else if ( strcmp(btype->text(),"Hold"  )==0) browser->type(FL_HOLD_BROWSER);
  else if ( strcmp(btype->text(),"Multi" )==0) browser->type(FL_MULTI_BROWSER);
  browser->redraw();
}

void wtype_cb(Fl_Widget *, void *) {
  if ( wtype->value() < 0 ) return;
  browser->when( when_items[wtype->value()].wvalue );	// when value based on array
}

int main(int argc, char **argv) {
  int i;
  if (!Fl::args(argc,argv,i)) Fl::fatal(Fl::help);
  const char* fname = (i < argc) ? argv[i] : "browser.cxx";
  Fl_Double_Window window(720,400,fname);
  browser = new Fl_Select_Browser(0,0,window.w(),350,0);
  browser->type(FL_MULTI_BROWSER);
  //browser->type(FL_HOLD_BROWSER);
  //browser->color(42);
  browser->callback(b_cb);
  // browser->scrollbar_right();
  //browser->has_scrollbar(Fl_Browser::BOTH_ALWAYS);
  if (!browser->load(fname)) {
    int done = 0;
#ifdef _MSC_VER
    // if 'browser' was started from the VisualC environment in Win32, 
    // the current directory is set to the environment itself, 
    // so we need to correct the browser file path
    if ( i == argc ) 
    {
      fname = "../test/browser.cxx";
      done = browser->load(fname);
    }
#elif defined(__APPLE__)
    char buf[2048];
    strcpy(buf, argv[0]);
    char *slash = strrchr(buf, '/');
    if (slash) {
      strcpy(slash, "/../../../browser.cxx");
    }
    done = browser->load(buf);
#endif
    if ( !done )
    {
      fl_message("Can't load %s, %s\n", fname, strerror(errno));
      exit(1);
    }
  }
  browser->position(0);

  field = new Fl_Int_Input(55, 350, window.w()-55, 25, "Line #:");
  field->callback(show_cb);

  top = new Fl_Button(0, 375, 80, 25, "Top");
  top->callback(show_cb);

  bottom = new Fl_Button(80, 375, 80, 25, "Bottom");
  bottom->callback(show_cb);

  middle = new Fl_Button(160, 375, 80, 25, "Middle");
  middle->callback(show_cb);

  visible = new Fl_Button(240, 375, 80, 25, "Make Vis.");
  visible->callback(show_cb);

  swap = new Fl_Button(320, 375, 80, 25, "Swap");
  swap->callback(swap_cb);
  swap->tooltip("Swaps two selected lines\n(Use CTRL-click to select two lines)");

  sort = new Fl_Button(400, 375, 80, 25, "Sort");
  sort->callback(sort_cb);

  btype = new Fl_Choice(480, 375, 80, 25);
  btype->add("Normal");
  btype->add("Select");
  btype->add("Hold");
  btype->add("Multi");
  btype->callback(btype_cb);
  btype->value(3);
  btype->tooltip("Changes the browser type()");

  wtype = new Fl_Choice(560, 375, 160, 25);
  wtype->textsize(8);
  // Append items from when_items[] array
  {
    int len = sizeof(when_items) / sizeof(WhenItem);
    for ( int i=0; i<len; i++ )
      wtype->add(when_items[i].name);
  }
  wtype->callback(wtype_cb);
  wtype->value(4);                          // FL_WHEN_RELEASE_ALWAYS is Fl_Browser's default

  window.resizable(browser);
  window.show(argc,argv);
  return Fl::run();
}

//
// End of "$Id$".
//

