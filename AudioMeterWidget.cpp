#include "AudioMeterWidget.h"

#include <QPaintEvent>
#include <QPainter>

AudioMeterWidget::AudioMeterWidget(QWidget *parent) : QWidget(parent) {
    m_redrawTimer = new QTimer();
    connect(m_redrawTimer, SIGNAL(timeout()), this, SLOT(redrawTimerExpired()));
    m_redrawTimer->start(RedrawInterval);
}

AudioMeterWidget::~AudioMeterWidget() {
    m_redrawTimer->stop();
    delete m_redrawTimer;
}

void AudioMeterWidget::reset() {
    m_rmsLevel = 0.0;
    m_peakLevel = 0.0;
    update();
}

void AudioMeterWidget::levelChanged(qreal rmsLevel, qreal peakLevel, int numSamples) {
    // Smooth the RMS signal
    const qreal smooth = pow(qreal(0.9),
                             static_cast<qreal>(numSamples) / 256); // TODO: remove this magic number
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

void AudioMeterWidget::redrawTimerExpired() {
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

void AudioMeterWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(rect(), QColor("#252525"));
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect bar = rect();
    qreal rms = m_decayedPeakLevel ;
    int index = 0;

}
