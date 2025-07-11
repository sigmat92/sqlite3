#include "waveformwidget.h"
#include <QPainter>
#include <QtMath>
#include <QDebug>

WaveformWidget::WaveformWidget(QWidget *parent)
	    : QWidget(parent), currentWave(SINE), running(false) {
		        timer = new QTimer(this);
			    connect(timer, &QTimer::timeout, this, &WaveformWidget::updateWave);
	    }

void WaveformWidget::setWaveType(WaveType type) {
	    currentWave = type;
	        update();  /* Trigger immediate redraw */
}

void WaveformWidget::start() {
	    if (!running) {
		            running = true;
			            timer->start(50);  /* ~20fps */
				        }
}

void WaveformWidget::stop() {
	    if (running) {
		            running = false;
			            timer->stop();
				            update();  /* Clear waveform */
					        }
}

void WaveformWidget::updateWave() {
	    update();  /* Request repaint */
}

void WaveformWidget::paintEvent(QPaintEvent *event) {
	    Q_UNUSED(event);
	        QPainter p(this);
		    p.setRenderHint(QPainter::Antialiasing);
		        p.fillRect(rect(), Qt::white);

			    int w = width();
			        int h = height();
				    if (w <= 0 || h <= 0) return;

				        /* Draw border */
				        p.setPen(Qt::gray);
					    p.drawRect(0, 0, w - 1, h - 1);

					        /* Draw label */
					        p.setPen(Qt::black);
						    p.drawText(10, 20, "Waveform: " + waveTypeToString(currentWave));

						        if (!running) return;

							    p.setPen(QPen(Qt::blue, 2));
							        QVector<QPointF> points;
								    for (int x = 0; x < w; ++x) {
									            float t = static_cast<float>(x) / w;
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

QString WaveformWidget::waveTypeToString(WaveType type) const {
	    switch (type) {
		        case SINE: return "Sine";
				       case SQUARE: return "Square";
						        case TRIANGLE: return "Triangle";
								           case PULSE: return "Pulse";
										           default: return "Unknown";
												        }
}

