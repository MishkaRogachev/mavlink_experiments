#include "uav_model.h"

// Qt
#include <QDateTime>

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
    m_pitch(::randNum(-500, 500) * 0.1),
    m_roll(::randNum(-50, 500) * 0.1),
    m_yaw(::randNum(0, 360)),
    m_velocity(::randNum(100, 250) * 0.1),
    m_position(55.9837, 37.2088)
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    this->startTimer(::interval);
}

void UavModel::timerEvent(QTimerEvent* event)
{
    Q_UNUSED(event)

    double distance = m_velocity / ::timeFactor;
    double distanceUp = m_pitch * distance;

    m_position = m_position.atDistanceAndAzimuth(distance, m_yaw, distanceUp);

    m_velocity += ::randNum(-25, 25) * 0.1;

    if (m_velocity < 0) m_velocity *= -1;

    m_pitch = formatPitchRoll(m_pitch + ::randNum(-500, 500) * 0.01);
    m_roll = formatPitchRoll(m_roll + ::randNum(-500, 500) * 0.01);
    m_yaw = formatYaw(m_yaw + ::randNum(-250, 250) * 0.01);
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
