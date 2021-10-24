#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <Arduino.h>
#include <JsonElement.h>
#include "Page.h"
#include "DashPage.h"
#include "ElevatorPage.h"
#include "ShotPage.h"
#include "ValvePage.h"
#include "DebugPage.h"
#include "RotaryKnobController.h"
#include "DisplayController.h"
#include "FireController.h"

class MenuController
{
public:
    MenuController(unsigned int encoderPinClk,
                   unsigned int encoderPinDt,
                   unsigned int displayAddress,
                   unsigned int displayLen,
                   unsigned int displayWidth,
                   unsigned int angleIncrement,
                   unsigned int angleMin,
                   unsigned int angleMax,
                   unsigned int pressureIncrement,
                   unsigned int pressureMin,
                   unsigned int pressureMax,
                   unsigned int durationIncrement,
                   unsigned int durationMin,
                   unsigned int durationMax,
                   unsigned int hangTimerDuration,
                   unsigned int downArrow,
                   unsigned int upArrow,
                   unsigned int robotBatChar,
                   unsigned int controllerBatChar);
    void init(JsonState &state, unsigned int downArrow, unsigned int upArrow);
    void menuUpdate(JsonState &state, bool isEnabled);
    void menuRefresh(JsonState &state);
    void menuPress(JsonState &state, bool isEnabled);

private:
    RotaryKnobController m_rotaryKnob;
    DisplayController m_display;
    int m_rotation, m_hangTimerDuration;
    long m_time;
    bool m_isActive;
    Page *m_currentPage;
    DashPage m_dashPage;
    ElevatorPage m_elevatorPage;
    ShotPage m_shotPage;
    DebugPage m_debugPage;
    ValvePage m_valvePage;
};
#endif