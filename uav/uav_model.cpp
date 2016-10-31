#include "uav_model.h"

namespace
{
    const int interval = 40; // 25 Hz
    const int timeFactor = 1000 / ::interval;

    int randNum(int min, int max)
    {
        return min + qrand() % (max - min);
    }
}

using namespace domain;

UavModel::UavModel(QObject* parent):
    QObject(parent),
    m_pitch(::randNum(-100, 100) * 0.1),
    m_roll(::randNum(-100, 100) * 0.1),
    m_yaw(::randNum(0, 360)),
    m_velocity(::randNum(0, 250) * 0.1),
    m_position(55.9837, 37.2088)
{
    this->startTimer(::interval);
}

void UavModel::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    double distance = m_velocity / ::timeFactor;
    double distanceUp = m_pitch * distance;

    m_position = m_position.atDistanceAndAzimuth(distance, m_yaw, distanceUp);

    m_velocity += ::randNum(-10, 10) * 0.1;

    m_yaw += ::randNum(-100, 100) * 0.1;
    m_pitch += ::randNum(-100, 100) * 0.1;
    m_roll += ::randNum(-100, 100) * 0.1;
}

QGeoCoordinate UavModel::position() const
{
    return m_position;
}

float UavModel::velocity() const
{
    return m_velocity;
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
