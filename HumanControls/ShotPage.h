#ifndef SHOT_PAGE_H
#define SHOT_PAGE_H

#include "Page.h"

class ShotPage : public Page
{
public:
    ShotPage(int increment, int min, int max);
    void paint(DisplayController &display, bool isActivated);
};

#endif