#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <QObject>
//#include "view/homeview.h"



class InputService;
class NavigationManager;
class HomeView;

class InputController : public QObject
{
    Q_OBJECT

public:
    InputController(InputService* service,
                NavigationManager* navigation,
                HomeView* homeView,
                QObject* parent = nullptr);
                
private slots:
    void onFocusNext();
    void onFocusPrevious();
    void onActivate();

    void onMute();
    void onNibp();
    void onFreeze();
    void onPrint();
    void onMenu();

private:
    InputService* m_service;
    //NavigationManager* m_navigation;
    //HomeView* m_homeView;
    
    NavigationManager* m_navigation = nullptr;
    HomeView* m_homeView = nullptr;
};

#endif // INPUTCONTROLLER_H
