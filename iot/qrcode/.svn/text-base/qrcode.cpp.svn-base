#include "qrcode.h"

extern "C" {
#include "png.h"
}

int iQR_HanNum[40]={
		10,
		20,
		32,
		48,
		65,
		82,
		95,
		118,
		141,
		167
};

QrCode::QrCode()
{
	decoder = new QZXing(QZXing::DecoderFormat_UPC_EAN_EXTENSION,this);
	connect(decoder,SIGNAL(tagFound(QString )),this,SLOT(DecodeSuc(QString)));
}

QrCode::~QrCode()
{
	if(decoder != 0)
	{
		delete decoder;
		decoder = 0;
	}
}

QPixmap QrCode::GetPixmap(QString tag, const char *outfile)
{
	QByteArray ucstr = tag.toLatin1();
	int iVersion = AutoVersion(ucstr.data());
	QByteArray tmp = tag.toAscii();
	QRcode * qr = new QRcode();
	qr = QRcode_encodeString(tmp.data(),iVersion, QR_ECLEVEL_L, QR_MODE_8,0);

	//qDebug()<<"QR width"<<qr->width;

	writePNG(qr, outfile);

	QRcode_free(qr);

	return QPixmap(outfile);
}

#define INCHES_PER_METER (100.0/2.54)
static int margin = 2;
static int dpi = 72;
static int sized = 3;
static unsigned int fg_color[4] = {0, 0, 0, 255};
static unsigned int bg_color[4] = {255, 255, 255, 255};

int QrCode::writePNG(QRcode *qrcode, const char *outfile)
{
	static FILE *fp; // avoid clobbering by setjmp.
	png_structp png_ptr;
	png_infop info_ptr;
	png_colorp palette;
	png_byte alpha_values[2];
	unsigned char *row, *p, *q;
	int x, y, xx, yy, bit;
	int realwidth;

	realwidth = (qrcode->width + margin * 2) * sized;
	row = (unsigned char *)malloc((realwidth + 7) / 8);
	if(row == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	if(outfile[0] == '-' && outfile[1] == '\0') {
		fp = stdout;
	} else {
		fp = fopen(outfile, "wb");
		if(fp == NULL) {
			fprintf(stderr, "Failed to create file: %s\n", outfile);
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png_ptr == NULL) {
		fprintf(stderr, "Failed to initialize PNG writer.\n");
		exit(EXIT_FAILURE);
	}

	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == NULL) {
		fprintf(stderr, "Failed to initialize PNG write.\n");
		exit(EXIT_FAILURE);
	}

	if(setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fprintf(stderr, "Failed to write PNG image.\n");
		exit(EXIT_FAILURE);
	}

	palette = (png_colorp) malloc(sizeof(png_color) * 2);
	if(palette == NULL) {
		fprintf(stderr, "Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
	palette[0].red   = fg_color[0];
	palette[0].green = fg_color[1];
	palette[0].blue  = fg_color[2];
	palette[1].red   = bg_color[0];
	palette[1].green = bg_color[1];
	palette[1].blue  = bg_color[2];
	alpha_values[0] = fg_color[3];
	alpha_values[1] = bg_color[3];
	png_set_PLTE(png_ptr, info_ptr, palette, 2);
	png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);

	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr,
			realwidth, realwidth,
			1,
			PNG_COLOR_TYPE_PALETTE,
			PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT,
			PNG_FILTER_TYPE_DEFAULT);
	png_set_pHYs(png_ptr, info_ptr,
			dpi * INCHES_PER_METER,
			dpi * INCHES_PER_METER,
			PNG_RESOLUTION_METER);
	png_write_info(png_ptr, info_ptr);

	/* top margin */
	memset(row, 0xff, (realwidth + 7) / 8);
	for(y=0; y<margin * sized; y++) {
		png_write_row(png_ptr, row);
	}

	/* data */
	p = qrcode->data;
	for(y=0; y<qrcode->width; y++) {
		bit = 7;
		memset(row, 0xff, (realwidth + 7) / 8);
		q = row;
		q += margin * sized / 8;
		bit = 7 - (margin * sized % 8);
		for(x=0; x<qrcode->width; x++) {
			for(xx=0; xx<sized; xx++) {
				*q ^= (*p & 1) << bit;
				bit--;
				if(bit < 0) {
					q++;
					bit = 7;
				}
			}
			p++;
		}
		for(yy=0; yy<sized; yy++) {
			png_write_row(png_ptr, row);
		}
	}
	/* bottom margin */
	memset(row, 0xff, (realwidth + 7) / 8);
	for(y=0; y<margin * sized; y++) {
		png_write_row(png_ptr, row);
	}

	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);

	fclose(fp);
	free(row);
	free(palette);

	return 0;
}


QString QrCode::decodeImage(QImage image, int maxWidth, int maxHeight, bool smoothTransformation)
{
	m_Time.restart();
	return decoder->decodeImage(image,maxWidth,maxHeight,smoothTransformation);
}

QString QrCode::decodeImageFromFile(QString imageFilePath, int maxWidth, int maxHeight, bool smoothTransformation)
{
	m_Time.restart();
	return decoder->decodeImageFromFile(imageFilePath,maxWidth,maxHeight,smoothTransformation);
}

QString QrCode::decodeImageQML(QObject *item)
{
	m_Time.restart();
	return decoder->decodeImageQML(item);

}

QString QrCode::decodeSubImageQML(QObject* item,const double offsetX, const double offsetY,const double width, const double height)
{
	m_Time.restart();
	return decoder->decodeSubImageQML(item,offsetX, offsetY,width,height);
}

void QrCode::DecodeSuc(QString tag)
{
	emit DecodeStr(tag,m_Time.elapsed());
}

int QrCode::AutoVersion(char *str)
{
	if(str == 0)
	{
		return 0;
	}

	int ichar = 0;
	int ihan = 0;

	char *p = str;
	while (*p)
	{
		if (*p == 0x3F)  //汉字
		{
			ihan++;
		}
		else  //标准的ASCII字符
		{
			ichar++;
		}
		p += 1;
	}

	int iVersion = 0;
	while(iQR_HanNum[iVersion] < (ihan+ichar/2))
	{
		iVersion++;
	}
	//qDebug()<<"汉字:"<<ihan<<"字母"<<ichar<<"版本"<<iVersion;
	return iVersion;
}

