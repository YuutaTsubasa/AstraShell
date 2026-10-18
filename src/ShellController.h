#pragma once
#include <QObject>
#include <QWindow>

class ShellController : public QObject {
 Q_OBJECT
 Q_PROPERTY(bool immersive READ immersive NOTIFY immersiveChanged)
 Q_PROPERTY(bool taskbarHidden READ taskbarHidden NOTIFY immersiveChanged)
public:
 explicit ShellController(QObject *parent=nullptr);
 ~ShellController() override;
 bool immersive() const { return m_immersive; }
 bool taskbarHidden() const { return m_taskbarHidden; }
 Q_INVOKABLE void setImmersive(bool enabled);
 Q_INVOKABLE void restoreTaskbar();
 Q_INVOKABLE void configureDesktop(QWindow *window);
 Q_INVOKABLE void configurePanel(QWindow *window);
signals:
 void immersiveChanged();
private:
 bool m_immersive=false;
 bool m_taskbarHidden=false;
};
