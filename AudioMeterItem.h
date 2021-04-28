/**************************************************************************
**   Created by TemetNosce 2020/10/9
**************************************************************************/

#pragma once
#include <QGraphicsItem>
#include <QTime>

class AudioMeterItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    AudioMeterItem();
    ~AudioMeterItem();
    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
 void setChannels(int value);
public:
    Qt::Orientation getOrientation() const;
    void setOrientation(const Qt::Orientation &value);

    void setBoundingRect(const QRectF &boundingRect);

public slots:
    void reset();
    void levelChanged(qreal rmsLevel, qreal peakLevel, int numSamples);

private slots:
    void redrawTimerExpired();

private:
    QRectF mBoundingRect;
    int channels = 0;
    // Constants
    const int RedrawInterval = 100; // ms
    const qreal PeakDecayRate = 0.001;
    const int PeakHoldLevelDuration = 2000; // ms
    /**
     * Height of RMS level bar.
     * Range 0.0 - 1.0.
     */
    qreal m_rmsLevel = 0.0;

    /**
     * Most recent peak level.
     * Range 0.0 - 1.0.
     */
    qreal m_peakLevel = 0.0;

    /**
     * Height of peak level bar.
     * This is calculated by decaying m_peakLevel depending on the
     * elapsed time since m_peakLevelChanged, and the value of m_decayRate.
     */
    qreal m_decayedPeakLevel = 0.0;

    /**
     * Time at which m_peakLevel was last changed.
     */
    QTime m_peakLevelChanged;

    /**
     * Rate at which peak level bar decays.
     * Expressed in level units / millisecond.
     */
    qreal m_peakDecayRate = PeakDecayRate;

    /**
     * High watermark of peak level.
     * Range 0.0 - 1.0.
     */
    qreal m_peakHoldLevel = 0.0;

    /**
     * Time at which m_peakHoldLevel was last changed.
     */
    QTime m_peakHoldLevelChanged;

    QTimer *m_redrawTimer;

    QColor m_rmsColor = Qt::red;
    QColor m_peakColor{255, 200, 200, 255};
    Qt::Orientation orientation = Qt::Horizontal;
};
