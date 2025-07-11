#ifndef WAVEFORMWIDGET_H
#define WAVEFORMWIDGET_H

#include <QWidget>
#include <QTimer>

enum WaveType {
	    SINE,
	        SQUARE,
		    TRIANGLE,
		        PULSE
};

class WaveformWidget : public QWidget {
	    Q_OBJECT

	public:
		        explicit WaveformWidget(QWidget *parent = nullptr);
			    void setWaveType(WaveType type);
			        void start();
				    void stop();

	protected:
				        void paintEvent(QPaintEvent *event) override;

					private slots:
						    void updateWave();

	private:
					    WaveType currentWave;
					        bool running;
						    QTimer *timer;

						        QString waveTypeToString(WaveType type) const;  //  Declare here
													};
													//
													 #endif // WAVEFORMWIDGET_H
													//
