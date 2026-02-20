#include "settingscontroller.h"
#include <QMessageBox>

SettingsController::SettingsController(SettingsView* v,
                                       SettingsService* s,
                                       SettingsModel* m,
                                       QObject* parent)
    : QObject(parent)
{
    connect(v,&SettingsView::saveRequested,
            s,&SettingsService::save);

    connect(v,&SettingsView::scanWifiRequested,
            s,&SettingsService::scanWifi);

    connect(v,&SettingsView::testConnectionRequested,
            s,&SettingsService::testConnection);
            
    connect(s,&SettingsService::wifiListReady,
        v,&SettingsView::updateWifiList);

    //connect(s,&SettingsService::wifiListReady,
    //        v,[=](QStringList list){
    //            v->ssidCombo->clear();
    //            v->ssidCombo->addItems(list);
    //        });

    connect(s,&SettingsService::connectivityResult,
            v,[=](bool ok){
                QMessageBox::information(
                    v,"Connectivity",
                    ok?"Internet OK":"No Connection");
            });

    connect(v,&SettingsView::exitRequested,
            v,&QWidget::close);
}

