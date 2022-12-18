#include <FL/Fl.H>
#include <FL/Fl_Choice.H>

#include "./TuningSelector.h"
#include "SetSelector.h"
#include "StringView.h"

TuningSelector::TuningSelector(int x, int y, int w, int h, const char* label): Fl_Choice(x,y,w,h,0) {
    this->add("Standard Tuning");
    this->add("Perfect Fourths");
    this->add("Drop Tuning");
    this->when(FL_WHEN_CHANGED);
    this->label("Tuning:");
    this->align(FL_ALIGN_TOP);
}

void TuningSelector::init(SetSelector* setSelector) {
    this->callback(tuningSelector_cb,setSelector);
}

static void tuningSelector_cb(Fl_Widget* w, void* v) {
    SetSelector* setSelector = static_cast<SetSelector*>(v);
    setSelector->do_callback();
}