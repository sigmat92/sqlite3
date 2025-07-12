#include "waveformwidget.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>

WaveformWidget::WaveformWidget(QWidget *parent)
	    : QWidget(parent), currentWave(SINE), running(false), phase(0) {
		        timer = new QTimer(this);
			    connect(timer, &QTimer::timeout, this, &WaveformWidget::updateWave);
	    }

void WaveformWidget::setWaveType(WaveType type) {
	    currentWave = type;
	        update();
}

void WaveformWidget::start() {
	    if (!running) {
		            running = true;
			            timer->start(50);  /* 20 fps */
				        }
}

void WaveformWidget::stop() {
	    if (running) {
		            running = false;
			            timer->stop();
				            update();
					        }
}

void WaveformWidget::updateWave() {
	    phase += 5;  /* shift the phase for motion */
	        if (phase > 360) phase = 0;
		    update();  /* trigger repaint */
}

void WaveformWidget::paintEvent(QPaintEvent *event) {
	    Q_UNUSED(event);

	        QPainter p(this);
		    p.setRenderHint(QPainter::Antialiasing);
		        p.fillRect(rect(), Qt::white);

			    int w = width();
			        int h = height();

				    if (!running || w <= 0 || h <= 0) {
					            p.drawText(rect(), Qt::AlignCenter, "Waveform stopped");
						            return;
							        }

				        p.setPen(QPen(Qt::blue, 2));
					    QVector<QPointF> points;

					        for (int x = 0; x < w; ++x) {
							        float t = static_cast<float>(x + phase) / w;
								        float y = 0.0;

									        switch (currentWave) {
											        case SINE:
													            y = sin(2 * M_PI * t);
														                break;
																        case SQUARE:
																            y = sin(2 * M_PI * t) >= 0 ? 1 : -1;
																	                break;
																			        case TRIANGLE:
																			            y = 2 * fabs(2 * (t - floor(t + 0.5))) - 1;
																				                break;
																						        case PULSE:
																						            y = (fmod(t, 0.25) < 0.1) ? 1 : -1;
																							                break;
																									        }

										        float screenY = h / 2 - y * h * 0.4;
											        points.append(QPointF(x, screenY));
												    }

						    p.drawPolyline(points.data(), points.size());
}

