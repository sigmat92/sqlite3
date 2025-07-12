#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waveformwidget.h"

MainWindow::MainWindow(QWidget *parent)
	    : QMainWindow(parent)
	          , ui(new Ui::MainWindow)
{
	    ui->setupUi(this);

	        /* Cast ui->waveWidget to your custom class */
	        WaveformWidget* waveform = qobject_cast<WaveformWidget*>(ui->waveWidget);

		    connect(ui->btnStart, &QPushButton::clicked, this, [=]() {
				            if (waveform) waveform->start();
					        });

		        connect(ui->btnStop, &QPushButton::clicked, this, [=]() {
					        if (waveform) waveform->stop();
						    });

			    connect(ui->comboWaveType, &QComboBox::currentIndexChanged, this, [=](int index) {
					            if (waveform) waveform->setWaveType(static_cast<WaveType>(index));
						        });
}

MainWindow::~MainWindow()
{
	    delete ui;
}

