#pragma once
#include <QObject>
#include <QString>
#include <QTimer>
class SystemBridge : public QObject {
 Q_OBJECT
 Q_PROPERTY(QString clock READ clock NOTIFY changed)
 Q_PROPERTY(QString date READ date NOTIFY changed)
 Q_PROPERTY(int battery READ battery NOTIFY changed)
 Q_PROPERTY(bool charging READ charging NOTIFY changed)
 Q_PROPERTY(QString platform READ platform CONSTANT)
public:
 explicit SystemBridge(QObject *parent=nullptr);
 QString clock() const {return m_clock;}
 QString date() const {return m_date;}
 int battery() const {return m_battery;}
 bool charging() const {return m_charging;}
 QString platform() const;
 Q_INVOKABLE void openSettings();
 Q_INVOKABLE void openExplorer();
 Q_INVOKABLE void openTerminal();
 Q_INVOKABLE void openStartMenu();
 Q_INVOKABLE void quitShell();
signals: void changed();
private:
 void refresh();
 QString m_clock, m_date;
 int m_battery=-1;
 bool m_charging=false;
 QTimer m_timer;
};
