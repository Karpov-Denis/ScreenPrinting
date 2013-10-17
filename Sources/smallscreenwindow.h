#ifndef SMALLSCREENWINDOW_H
#define SMALLSCREENWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
    class SmallScreenWindow;
}

class SmallScreenWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit SmallScreenWindow(QWidget *parent = 0);
    SmallScreenWindow(bool isClose);
    ~SmallScreenWindow();

protected:
    // ������� �������� �����
    void closeEvent(QCloseEvent *event);

signals:

private slots:
    // �������� ������� ����
    void AnimationHideWindow();
    // ������� ����
    void on_ButtonClose_clicked();

private:
    Ui::SmallScreenWindow *ui;
//FUNCTION
    // ������������� ����������
    void InicializationVariable();
    // ������������� �����
    void InicializationWindow();
    // �������� ��������� ����
    void AnimationShowWindow();
    // ����� ������ ������
    void UpdateScreenShot();
    // ��������� ������ ������
    void SaveScreenShot();
//SETTINGS FUNCTION

//VARIABLE
    // ������ ������
    QPixmap screenShotDispaly;
    //
    bool isClose;
};

#endif // SMALLSCREENWINDOW_H
