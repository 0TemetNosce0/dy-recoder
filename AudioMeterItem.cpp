/**************************************************************************
**   Created by TemetNosce 2020/10/9
**************************************************************************/
#include "AudioMeterItem.h"

#include <QPainter>
#include <QTimer>

AudioMeterItem::AudioMeterItem()
{
    m_redrawTimer = new QTimer();
    //    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    //    setMinimumWidth(20);

    setFlag(ItemClipsToShape);
    connect(m_redrawTimer, SIGNAL(timeout()), this, SLOT(redrawTimerExpired()));
    m_redrawTimer->start(RedrawInterval);
}

AudioMeterItem::~AudioMeterItem()
{
    m_redrawTimer->stop();
    delete m_redrawTimer;
}

QRectF AudioMeterItem::boundingRect() const { return mBoundingRect; }

void AudioMeterItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // NOTE:总声道，就两个
    channels = 2;
    painter->fillRect(boundingRect(), QColor("#252525"));
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);
    QRectF bar = boundingRect();
    if (orientation == Qt::Horizontal) {
        QLinearGradient linearGradient(0, 0, boundingRect().width(), 0);
        linearGradient.setColorAt(0.0, QColor(QRgb(0x4fe8ec)));
        linearGradient.setColorAt(0.5, QColor(QRgb(0x5b69e8)));
        linearGradient.setColorAt(1.0, QColor(QRgb(0x59adfb)));
        painter->setBrush(QBrush(linearGradient));

        qreal rms = m_decayedPeakLevel * 13;
        qreal h = boundingRect().height() / channels;
        qreal leftMargin = 9;
        qreal rightMargin = 9;
        qreal topMargin = 9+2;
        qreal buttomMargin = 9;

        qreal circleWidth = 5;
        qreal circleSpace = 3;

        for (int channel = 0; channel < channels; channel++) {
            int index = 0;
            for (; index < rms; index++) {
                painter->drawEllipse(leftMargin + index * circleWidth + circleSpace * index,
                                     topMargin + circleWidth * channel + (channel - 1) * circleSpace, circleWidth,
                                     circleWidth);
            }
            painter->save();
            painter->setBrush(QColor("#1a1a1a"));
            for (; index < 13; index++) {
                painter->drawEllipse(leftMargin + index * circleWidth + circleSpace * index,
                                     topMargin + circleWidth * channel + (channel - 1) * circleSpace, circleWidth,
                                     circleWidth);
            }
            painter->restore();
        }

    } else {
        //        bar.setTop(boundingRect().top() + (1.0 - m_peakHoldLevel) * boundingRect().height());
        //        bar.setBottom(bar.top() + 1);
        //        painter->fillRect(bar, m_rmsColor);

        //        bar.setBottom(boundingRect().bottom());
        //        bar.setTop(boundingRect().top() + (1.0 - m_decayedPeakLevel) * boundingRect().height());
        //        painter->fillRect(bar, m_peakColor);

        //        bar.setTop(boundingRect().top() + (1.0 - m_rmsLevel) * boundingRect().height());
        //        painter->fillRect(bar, m_rmsColor);
    }

    painter->setPen(QColor("#171717"));
    painter->drawLine(QPointF(0, 0), QPointF(boundingRect().width(), 0));
}

void AudioMeterItem::setChannels(int value) { channels = value; }

void AudioMeterItem::reset()
{
    m_rmsLevel = 0.0;
    m_peakLevel = 0.0;
    update();
}

void AudioMeterItem::levelChanged(qreal rmsLevel, qreal peakLevel, int numSamples)
{

    // Smooth the RMS signal
    const qreal smooth = pow(qreal(0.9), static_cast<qreal>(numSamples) / 256); // TODO: remove this magic number
    m_rmsLevel = (m_rmsLevel * smooth) + (rmsLevel * (1.0 - smooth));

    if (peakLevel > m_decayedPeakLevel) {
        m_peakLevel = peakLevel;
        m_decayedPeakLevel = peakLevel;
        m_peakLevelChanged.start();
    }

    if (peakLevel > m_peakHoldLevel) {
        m_peakHoldLevel = peakLevel;
        m_peakHoldLevelChanged.start();
    }

    update();
}

void AudioMeterItem::redrawTimerExpired()
{
    // Decay the peak signal
    const int elapsedMs = m_peakLevelChanged.elapsed();
    const qreal decayAmount = m_peakDecayRate * elapsedMs;
    if (decayAmount < m_peakLevel)
        m_decayedPeakLevel = m_peakLevel - decayAmount;
    else
        m_decayedPeakLevel = 0.0;

    // Check whether to clear the peak hold level
    if (m_peakHoldLevelChanged.elapsed() > PeakHoldLevelDuration)
        m_peakHoldLevel = 0.0;

    update();
}

void AudioMeterItem::setBoundingRect(const QRectF &boundingRect) { mBoundingRect = boundingRect; }

Qt::Orientation AudioMeterItem::getOrientation() const { return orientation; }

void AudioMeterItem::setOrientation(const Qt::Orientation &value) { orientation = value; }
