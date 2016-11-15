#include "uav_model.h"

// Qt
#include <QDateTime>
#include <QtMath>
#include <QDebug>

namespace
{
    const int interval = 40; // 25 Hz
    const int timeFactor = 1000 / ::interval;

    int randNum(int min, int max)
    {
        return min + qrand() % (max - min);
    }

    float formatYaw(float angle)
    {
        return angle > 360 ? angle - 360 : (angle < 0 ? angle + 360 : angle);
    }

    float formatPitchRoll(float angle)
    {
        return angle > 45 ? 45 : (angle < -45 ? -45 : angle);
    }
}

using namespace domain;

UavModel::UavModel(QObject* parent):
    QObject(parent),
    m_pitch(::randNum(0, 600) * 0.1),
    m_roll(::randNum(-50, 50) * 0.1),
    m_yaw(::randNum(0, 360)),
    m_airspeed(::randNum(150, 500) * 0.1),
    m_position(55.9837, 37.2088, 0)
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    this->startTimer(::interval);
}

void UavModel::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    m_climb = qSin(qDegreesToRadians(m_pitch)) * m_airspeed;

    double distance = m_airspeed / ::timeFactor;
    double distanceUp = m_climb / ::timeFactor;

    m_position = m_position.atDistanceAndAzimuth(distance, m_yaw, distanceUp);
    if (!m_homePosition.isValid()) m_homePosition = m_position;

    m_airspeed += ::randNum(-100, 100) * 0.001;

    if (m_airspeed < 0) m_airspeed *= -1;

    m_pitch = formatPitchRoll(m_pitch + ::randNum(-500, 500) * 0.01);
    m_roll = formatPitchRoll(m_roll + ::randNum(-500, 500) * 0.01);
    m_yaw = formatYaw(m_yaw + ::randNum(-250, 250) * 0.01);
}

QGeoCoordinate UavModel::position() const
{
    return m_position;
}

QGeoCoordinate UavModel::homePosition() const
{
    return m_homePosition;
}

void UavModel::setHomePosition(const QGeoCoordinate& homePosition)
{
    m_homePosition = homePosition;
}

float UavModel::airspeed() const
{
    return m_airspeed;
}

float UavModel::groundspeed() const
{
    return m_airspeed; // TODO: wind
}

float UavModel::climb() const
{
    return m_climb;
}

float UavModel::yaw() const
{
    return m_yaw;
}

float UavModel::roll() const
{
    return m_roll;
}

float UavModel::pitch() const
{
    return m_pitch;
}
