#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QtGui>
#include <QMessageBox>
#include <QPixmap>

class Screenshot
{
public:
    // �������� ������ ������ ��������� ��������
    static QPixmap GetScreenShot(int numberDesktop);

    static QPixmap GetScreenShot(int x0Position,
                                 int y0Position,
                                 int width,
                                 int height);

    // ����� ���������
    static int GetNumberDesktop();

    // ������ ������
    static QString GetSizeDesktop(int numberDesktop);

    // ���������� ������ ������ � ������� *.pdf
    // screenshot - ��������� ������, �������� ������ ������
    // path - ���� ����������
    // orientation - ����������: ������������ ��� ��������������
    // pageSize - ������ �����: �0..�9
    // colorMode - �������� �����: ������� ��� �����-�����
    static bool SaveScreenShotToPdf(QPixmap screenShot,
                                    QString path,
                                    QPrinter::Orientation orientation,
                                    QPrinter::PageSize pageSize,
                                    QPrinter::ColorMode colorMode);

    // ���������� ������ ������ � ������� ��������
    // screenshot - ��������� ������, �������� ������ ������
    // path - ���� ����������
    // format - ������ ��������: PNG, JPG, JPEG, BMP
    // quality - ��������
    static bool SaveScreenShotToImage(QPixmap screenShot,
                                      QString paths,
                                      QString format,
                                      int quality);
};

#endif // SCREENSHOT_H
