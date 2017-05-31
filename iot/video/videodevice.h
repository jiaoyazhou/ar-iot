#ifndef VIDEODEVICE_H
#define VIDEODEVICE_H
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <asm/types.h>
#include <linux/videodev2.h>
#include <QString>
#include <QObject>

#define CLEAR(x) memset(&(x), 0, sizeof(x))
#define WIDTH  320
#define HEIGHT 240

class VideoDevice : public QObject
{
    Q_OBJECT
public:
    explicit VideoDevice(QObject *parent = 0);
    VideoDevice(QString dev_name);
    int open_device();
    int close_device();
    int init_device();
    int start_capturing();
    int stop_capturing();
    int uninit_device();
    int get_frame(void **, size_t*);
    int unget_frame();

    int convert_yuv_to_rgb_pixel(int y, int u, int v);
    int convert_yuv_to_rgb_buffer(unsigned char *yuv, unsigned char *rgb, unsigned int width, unsigned int height);

private:
    int init_mmap();

    struct buffer
    {
        void * start;
        size_t length;
    };
    QString dev_name;
    int fd;
    buffer* buffers;
    unsigned int n_buffers;
    int index;
signals:
    void display_error(QString);
public slots:

};

#endif // VIDEODEVICE_H
