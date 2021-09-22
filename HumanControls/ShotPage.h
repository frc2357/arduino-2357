#ifndef SHOT_PAGE_H
#define SHOT_PAGE_H

#include "Page.h"
#include "Arduino.h"
#include <JsonEl.h>

class ShotPage : public Page
{
public:
    ShotPage(int increment, int min, int max);
    void paint(DisplayController &display, bool isActivated, JsonState &state);
    void clockwise(JsonState &state);
    void counterClockwise(JsonState &state);

private:
    int m_min, m_max, m_increment;
};

#endif