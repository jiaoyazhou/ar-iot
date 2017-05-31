/*
 * global.cpp
 *
 *  Created on: 2017年4月25日
 *      Author: root
 */

#include "global.h"

QrCode *g_qrcode = 0;
statusbar *g_Statusbar = 0;
Database *g_database = 0;



QSize g_ScreenSize = QSize(0,0);
QRect g_RcStatusbar = QRect(0,0,0,0);
QRect g_RcMain = QRect(0,0,0,0);
QFont g_Font[3];

QPalette g_Palette;

QVector<int> m_temperature;
QVector<int> m_humidity;
