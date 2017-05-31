#ifndef QRCODE_H
#define QRCODE_H

#include "qobject.h"
#include "qpixmap.h"
#include "QZXing.h"
extern "C" {
#include "qrencode.h"
#include "png.h"
}

class QrCode : public QObject
{
	Q_OBJECT
public:
    QrCode();
    ~QrCode();

    QPixmap GetPixmap(QString tag, const char *outfile = "/tmp/Qrcode.png");
    static int writePNG(QRcode *qrcode, const char *outfile);

    QString decodeImage(QImage image, int maxWidth=-1, int maxHeight=-1, bool smoothTransformation = false);
    QString decodeImageFromFile(QString imageFilePath, int maxWidth=-1, int maxHeight=-1, bool smoothTransformation = false);
    QString decodeImageQML(QObject *item);
    QString decodeSubImageQML(QObject* item,
                                 const double offsetX = 0 , const double offsetY = 0,
                                 const double width = 0, const double height = 0);


Q_SIGNALS:
	/*解码成功信号，包括处理时间*/
	void DecodeStr(QString,int);

protected slots:
	/*解码成功处理*/
	void DecodeSuc(QString tag);

protected:
	/*根据数据内容自动选择QR码版本*/
	int AutoVersion(char *str);

private:
	QZXing *decoder;
    QTime m_Time;
};

#endif // QRCODE_H
