#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //
    void showEvent(QShowEvent *event);
    // ������� ��������� ������� �����
    void resizeEvent(QResizeEvent *event);
    // ������� �������
    void keyPressEvent(QKeyEvent *event);
    // ���������� �������
    void keyReleaseEvent(QKeyEvent *event);
    // �������� ������ �������
    bool event(QEvent *event);
    // ������� �������� �����
    void closeEvent(QCloseEvent *event);

public slots:
    void slotActivateWindow();

private slots:
    // ���������� ������ ������
    void slotUpdateScreenShot();
    // ���������� ������ ������ � "������ ������"
    void slotBlindSaveScreenShot();
    // �������� ������
    void slotDataBufferControl();
    //
    void slotShowHide();
    //
    void slotShowMessage();
    // ������� �����
    void on_ButtonNext_clicked();
    // ������� ������
    void on_ButtonCancel_clicked();
    // ������� ��������
    void on_ButtonUpdate_clicked();
    // ������� ������� ������ ������
    void on_rbNumberMonitor_clicked();
    // ��������� ������� �����
    void on_rbSizeRect_clicked();
    // ����� �����������
    void on_ButtonSetDirectory_clicked();
    // ���������� ��������
    void on_cbOrientation_currentIndexChanged(const QString &arg1);
    // �������� ����� ��������
    void on_cbColorMode_currentIndexChanged(const QString &arg1);
    // ������ ��������
    void on_cbPageSize_currentIndexChanged(const QString &arg1);
    // ������������ ����� ����������
    void on_cbFormatFile_currentIndexChanged(const QString &arg1);
    //
    void on_cbWindowStaysOnTopHint_clicked();
    //
    void on_cbWindowCenterDesktop_clicked();
    //
    void on_cbWindowOpacity_clicked();
    //
    void on_hsWindowOpacity_valueChanged(int );

private:
    Ui::MainWindow *ui;
//FUNCTION
    // ������������� ����������
    void InicializationVariable();
    // ��������� ���� ������� ����������
    void InicializationTrayMenu();
    // ������ �������� ����������
    void GetSettings();
    // ������ �������� ����������
    void SetSettings();
    // ���������� ������ ������
    bool SaveScreenShot();
//SETTINGS FUNCTION
    // ��������� �������� ������� ������ ������
    void SetEnabledWidgetSizeScreen();
    // ����������� ��������� ������ � ������� ����������
    void ChangeIcon();
    // ����������� ����� � ����� ����
    void WindowsCenterDesktop();
    // ������������ �����
    void WindowOpacity();
    // ������������ ������ ���� ����
    void WindowStaysOnTop();
//VARIABLE
    QVector<QByteArray> encodedString;
    QTextCodec *codec;
    QVector<QString> appendText;
    // ������ ��� ��������� �����
    QString full_file_name;
    // ������ ������
    QPixmap screenShotDispaly;
    // ���������� ��������
    QPrinter::Orientation page_orientation;
    // �������� ����� ��������
    QPrinter::ColorMode page_color;
    // ������ ��������
    QPrinter::PageSize page_size;
    // ����� �������
    int key;
    // ���� ��������: �������� ���������/��������� �����
    bool isAnimation;
    // ������, ������� ������������� ����������� ������������ ������� ����������
    QSystemTrayIcon *m_ptrayIcon;
    // ������ ��� ���������� ������������ ����
    QMenu *m_ptrayiconMenu;
    // ������� ���������� ��� ���������� ������ ���������� �����������
    bool m_bIconSwitcher;
};

#endif // MAINWINDOW_H
