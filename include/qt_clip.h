#ifndef QT_CLIP_H
#define QT_CLIP_H


#include <QString>

string GbkToUtf8(const char *src_str);
string Utf8ToGbk(const char *src_str);

QString _Q_U(const char *src_str)
{
    return QString::fromStdString(GbkToUtf8(src_str));
}
QString _Q_G(const char *src_str)
{
    return QString::fromStdString(Utf8ToGbk(src_str));
}

#endif // QT_CLIP_H
