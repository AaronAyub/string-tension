/* A menu bar at the top of the main window. */
#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>

class Menubar : public Fl_Menu_Bar {
    public:
        Menubar (int x, int y, int w, int h);
};

static void quit_cb(Fl_Widget*, void*);