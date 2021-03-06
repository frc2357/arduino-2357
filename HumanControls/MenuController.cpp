#include "MenuController.h"

MenuController::MenuController(unsigned int encoderPinClk,
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
                               unsigned int controllerBatChar)
    : m_rotaryKnob(encoderPinClk, encoderPinDt), m_display(displayAddress, displayLen, displayWidth),
      m_dashPage(downArrow, upArrow, robotBatChar, controllerBatChar),
      m_elevatorPage(angleIncrement, angleMin, angleMax, downArrow, upArrow, robotBatChar,
                     controllerBatChar),
      m_shotPage(pressureIncrement, pressureMin, pressureMax, downArrow, upArrow, robotBatChar,
                 controllerBatChar),
      m_valvePage(durationIncrement, durationMin, durationMax, downArrow, upArrow, robotBatChar,
                  controllerBatChar),
      m_debugPage(downArrow, upArrow, robotBatChar, controllerBatChar)
{
    this->m_isActive = false;

    this->m_rotation = 0;

    // Set previous pages
    m_dashPage.setPreviousPage(m_debugPage);
    m_elevatorPage.setPreviousPage(m_dashPage);
    m_shotPage.setPreviousPage(m_elevatorPage);
    m_valvePage.setPreviousPage(m_shotPage);
    m_debugPage.setPreviousPage(m_valvePage);

    // Set next pages
    m_dashPage.setNextPage(m_elevatorPage);
    m_elevatorPage.setNextPage(m_shotPage);
    m_shotPage.setNextPage(m_valvePage);
    m_valvePage.setNextPage(m_debugPage);
    m_debugPage.setNextPage(m_dashPage);

    m_currentPage = &m_dashPage;

    this->m_hangTimerDuration = hangTimerDuration;
    this->m_time = millis();
}

void MenuController::init(TShirtCannonPayload &payload, unsigned int downArrow, unsigned int upArrow)
{
    Serial.println("Menu Init");
    this->m_display.init(downArrow, upArrow);
    payload.setFiringTime(this->m_valvePage.rangeFilter(payload.getFiringTime()));
    payload.setAngle(this->m_elevatorPage.rangeFilter(payload.getAngle()));
    payload.setFiringPressure(this->m_shotPage.rangeFilter(payload.getFiringPressure()));
    this->m_currentPage->paint(m_display, this->m_isActive, payload);
}

void MenuController::menuRefresh(TShirtCannonPayload &payload)
{
    if (this->m_currentPage->getName() != this->m_dashPage.getName())
    {
        m_isActive = false;
    }
    this->m_currentPage->paint(m_display, m_isActive, payload);
}

void MenuController::menuUpdate(TShirtCannonPayload &payload, bool isEnabled)
{
    this->m_rotation = this->m_rotaryKnob.getValue();

    if (m_isActive && isEnabled)
    {
        if (this->m_rotation == 1)
        {
            this->m_currentPage->clockwise(payload);
        }

        if (this->m_rotation == -1)
        {
            this->m_currentPage->counterClockwise(payload);
        }
    }
    else
    {
        if (this->m_rotation == 1)
        {
            this->m_currentPage = this->m_currentPage->getNextPage();
        }

        if (this->m_rotation == -1)
        {
            this->m_currentPage = this->m_currentPage->getPreviousPage();
        }
    }

    if (this->m_rotation != 0)
    {
        this->m_time = millis();
        this->m_currentPage->cleanUp(m_display);
        this->m_currentPage->paint(m_display, m_isActive, payload);
    }

    if (this->m_currentPage->applyHang() && millis() > (this->m_time + this->m_hangTimerDuration))
    {
        this->m_currentPage = &m_dashPage;
        this->m_isActive = false;
        this->m_currentPage->cleanUp(m_display);
        this->m_currentPage->paint(m_display, m_isActive, payload);
    }
}

void MenuController::menuPress(TShirtCannonPayload &payload, bool isEnabled)
{
    if ((isEnabled && m_currentPage->canActivate()) || this->m_currentPage->getName() == this->m_dashPage.getName())
    {
        this->m_isActive = !this->m_isActive;
        this->m_time = millis();
    }
    else
    {
        this->m_isActive = false;
    }
    this->m_currentPage->paint(m_display, m_isActive, payload);
}