#include <QString>
#include "qt_clip.h"

QString _Q_U(const char *src_str)
{
    return QString::fromStdString(GbkToUtf8(src_str));
}
QString _Q_G(const char *src_str)
{
    return QString::fromStdString(Utf8ToGbk(src_str));
}
QString _Q(const char *src_str)
{
    return QString::fromStdString(std::string(src_str));
}

