#include "screenshot.h"

QPixmap Screenshot::GetScreenShot(int numberDesktop)
{
    QPixmap screenShot = QPixmap();

    screenShot = QPixmap::grabWindow(QApplication::desktop()->screen(numberDesktop)->winId(),
                                     QApplication::desktop()->screenGeometry(numberDesktop).left(),
                                     QApplication::desktop()->screenGeometry(numberDesktop).top(),
                                     -1,
                                     -1);

    return screenShot;
}

QPixmap Screenshot::GetScreenShot(int x0Position,
                                  int y0Position,
                                  int width,
                                  int height)
{
    QPixmap screenShot = QPixmap();

    screenShot = QPixmap::grabWindow(QApplication::desktop()->winId(),
                                     x0Position,
                                     y0Position,
                                     width,
                                     height);

    return screenShot;
}

int Screenshot::GetNumberDesktop()
{
    return QApplication::desktop()->numScreens();
}

QString Screenshot::GetSizeDesktop(int numberDesktop)
{
    QString sizeDesktop;
    QString sWidth, sHeight, sLeft, sTop;
    sWidth.setNum(QApplication::desktop()->screenGeometry(numberDesktop).width());
    sHeight.setNum(QApplication::desktop()->screenGeometry(numberDesktop).height());
    sLeft.setNum(QApplication::desktop()->screenGeometry(numberDesktop).left());
    sTop.setNum(QApplication::desktop()->screenGeometry(numberDesktop).top());

    sizeDesktop = sWidth + "x" + sHeight + " (" + sLeft + "," + sTop + ")";

    return sizeDesktop;
}

bool Screenshot::SaveScreenShotToPdf(QPixmap screenShot,
                                     QString fileName,
                                     QPrinter::Orientation orientation,
                                     QPrinter::PageSize pageSize,
                                     QPrinter::ColorMode colorMode)
{
    QByteArray encodedString;
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");;
    QString appendText, titleMessage;

    Qt::WindowFlags flag = 0;
    flag |=  Qt::Tool;// �������� ������ � taskbar � ������ ��������, ������� ������� ����
    flag |=  Qt::WindowStaysOnTopHint;// ������ ������ ������
    flag |=  Qt::FramelessWindowHint;
    flag |=  Qt::WindowTitleHint;

    QDateTime date_time = QDateTime::currentDateTime();

    QMessageBox msgBox;
    msgBox.setWindowTitle(date_time.toString() + " " + QApplication::applicationName() + ":" + QApplication::applicationVersion());
    msgBox.setWindowFlags(flag);

    // Step 1. ��������, ��� screenshot �� ������
    if(screenShot.isNull()){
        encodedString = "���������";
        titleMessage = codec->toUnicode(encodedString);
        encodedString = "� ������ ������ ������ ���";
        msgBox.setText(titleMessage); // ��������� ���������
        msgBox.setIcon(QMessageBox::Information); // ��� ������ ���������
        msgBox.setInformativeText(appendText); // �������� ��������� Message Box
        msgBox.setDefaultButton(QMessageBox::Save); // �� ����� ������ �������������� �� ���������
        msgBox.exec();
        return 0;
    }//if

    // Step 2. ��������, ��� fileName �� ������
    if (fileName.isEmpty()){
        encodedString = "���������";
        titleMessage = codec->toUnicode(encodedString);
        encodedString = "��� ����� �� �������";
        appendText = codec->toUnicode(encodedString);
        msgBox.setText(titleMessage); // ��������� ���������
        msgBox.setIcon(QMessageBox::Information); // ��� ������ ���������
        msgBox.setInformativeText(appendText); // �������� ��������� Message Box
        msgBox.setDefaultButton(QMessageBox::Save); // �� ����� ������ �������������� �� ���������
        msgBox.exec();
        return 0;
    }//if

    // ���������� �����
    fileName += ".pdf";

    // Step 3. �������� ������������� �����. ���� ���� ����������, �� ������, ����� �� ��� ��������������
    if (QFile::exists(fileName)){
        encodedString = "��������� ����������";
        titleMessage = codec->toUnicode(encodedString);
        encodedString = " \n��� ����������. ��������?";
        appendText = codec->toUnicode(encodedString);
        msgBox.setText(titleMessage); // ��������� ���������
        msgBox.setIcon(QMessageBox::Information); // ��� ������ ���������
        msgBox.setInformativeText(fileName + appendText); // �������� ��������� Message Box
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel); // ���������� ������������ �� ���� �������
        msgBox.setDefaultButton(QMessageBox::Save); // �� ����� ������ �������������� �� ���������

        int ret = msgBox.exec(); // ��������� QMessageBox. ����� ����������, � ret ����� ������ �������� ������, �� ������� ������ - ��� ���������� ��� ���������� ��������� �������

        if(ret == QMessageBox::Cancel)
            return 0;
    }//if

    // Step 4. ���������� ���������� ������ QPrinter � ����������� ��� ��������
    QPrinter printer;
    printer.setOutputFileName(fileName);
    printer.setFullPage(true);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(pageSize);
    printer.setOrientation(orientation);
    printer.setColorMode(colorMode);
    printer.newPage();

    // Step 5. �������� �� ��������� ������
    QPainter painter;
    if (! painter.begin(&printer)){
        encodedString = "������ �������� �����";
        titleMessage = codec->toUnicode(encodedString);
        encodedString = "���������, ��� ������ � ���� ���������";
        appendText = codec->toUnicode(encodedString);
        msgBox.setText(titleMessage); // ��������� ���������
        msgBox.setIcon(QMessageBox::Warning); // ��� ������ ���������
        msgBox.setInformativeText(appendText); // �������� ��������� Message Box
        msgBox.setDefaultButton(QMessageBox::Save); // �� ����� ������ �������������� �� ���������
        msgBox.show();
        return 0;
    }//if

/*
    if (! printer.newPage()){
        encodedString = "������ ��� ���������� ����� ��������";
        titleMessage = codec->toUnicode(encodedString);
        encodedString = "���������, ��� �� ����� ���� �����";
        appendText = codec->toUnicode(encodedString);
        msgBox.setText(titleMessage); // ��������� ���������
        msgBox.setIcon(QMessageBox::Warning); // ��� ������ ���������
        msgBox.setInformativeText(appendText); // �������� ��������� Message Box
        msgBox.setDefaultButton(QMessageBox::Save); // �� ����� ������ �������������� �� ���������
        msgBox.show();
        return 0;
    }//if
*/
    // Step 6. ����������
    painter.drawPixmap(0, 0, printer.width(), printer.height(), screenShot);
    painter.end();
/*
    QFile file("c://test.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << temp;
    out << "\n";
    file.close();
*/
    return 1;
}

bool Screenshot::SaveScreenShotToImage(QPixmap screenShot,
                                       QString fileName,
                                       QString format,
                                       int quality)
{
    QByteArray encodedString;
    QTextCodec* codec = QTextCodec::codecForName("Windows-1251");;
    QString appendText, titleMessage;

    Qt::WindowFlags flag = 0;
    flag |=  Qt::Tool;// �������� ������ � taskbar � ������ ��������, ������� ������� ����
    flag |=  Qt::WindowStaysOnTopHint;// ������ ������ ������
    flag |=  Qt::FramelessWindowHint;
    flag |=  Qt::WindowTitleHint;

    QDateTime date_time = QDateTime::currentDateTime();

    QMessageBox msgBox;
    msgBox.setWindowTitle(date_time.toString() + " " + QApplication::applicationName() + ":" + QApplication::applicationVersion());
    msgBox.setWindowFlags(flag);

    // Step 1. ��������, ��� screenshot �� ������
    if(screenShot.isNull()){
        encodedString = "���������";
        titleMessage = codec->toUnicode(encodedString);
        encodedString = "� ������ ������ ������ ���";
        msgBox.setText(titleMessage); // ��������� ���������
        msgBox.setIcon(QMessageBox::Information); // ��� ������ ���������
        msgBox.setInformativeText(appendText); // �������� ��������� Message Box
        msgBox.setDefaultButton(QMessageBox::Save); // �� ����� ������ �������������� �� ���������
        msgBox.exec();
        return 0;
    }//if

    // Step 2. ��������, ��� fileName �� ������
    if (fileName.isEmpty()){
        encodedString = "���������";
        titleMessage = codec->toUnicode(encodedString);
        encodedString = "��� ����� �� �������";
        appendText = codec->toUnicode(encodedString);
        msgBox.setText(titleMessage); // ��������� ���������
        msgBox.setIcon(QMessageBox::Information); // ��� ������ ���������
        msgBox.setInformativeText(appendText); // �������� ��������� Message Box
        msgBox.setDefaultButton(QMessageBox::Save); // �� ����� ������ �������������� �� ���������
        msgBox.exec();
        return 0;
    }//if

    // ���������� �����
    fileName += "." + format;

    // Step 3. �������� ������������� �����. ���� ���� ����������, �� ������, ����� �� ��� ��������������
    if (QFile::exists(fileName)){
        encodedString = "��������� ����������";
        titleMessage = codec->toUnicode(encodedString);
        encodedString = " ��� ����������. ��������?";
        appendText = codec->toUnicode(encodedString);
        msgBox.setText(titleMessage); // ��������� ���������
        msgBox.setIcon(QMessageBox::Information); // ��� ������ ���������
        msgBox.setInformativeText(fileName + appendText); // �������� ��������� Message Box
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel); // ���������� ������������ �� ���� �������
        msgBox.setDefaultButton(QMessageBox::Save); // �� ����� ������ �������������� �� ���������
        int ret = msgBox.exec(); // ��������� QMessageBox. ����� ����������, � ret ����� ������ �������� ������, �� ������� ������ - ��� ���������� ��� ���������� ��������� �������

        if(ret == QMessageBox::Cancel)
            return 0;
    }//if

    // Step 6. ����������
    screenShot.save(fileName, format.toLocal8Bit().data(), quality);


    return 1;
}
