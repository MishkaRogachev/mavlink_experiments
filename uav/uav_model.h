#ifndef UAV_MODEL_H
#define UAV_MODEL_H

#include <QObject>
#include <QGeoCoordinate>

namespace domain
{
    class UavModel : public QObject
    {
        Q_OBJECT

    public:
        explicit UavModel(QObject* parent = nullptr);

        float pitch() const;
        float roll() const;
        float yaw() const;

        float airspeed() const;
        float groundspeed() const;
        float climb() const;

        QGeoCoordinate position() const;
        QGeoCoordinate homePosition() const;

    public slots:
        void setHomePosition(const QGeoCoordinate& homePosition);

    protected:
        void timerEvent(QTimerEvent* event);

    private:
        float m_pitch;
        float m_roll;
        float m_yaw;

        float m_airspeed;
        float m_climb;

        QGeoCoordinate m_position;
        QGeoCoordinate m_homePosition;
    };
}

#endif // UAV_MODEL_H
