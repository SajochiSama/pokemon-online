#include "functions.h"

#include <QtGui>

QString escapeHtml(const QString & toConvert)
{
    QString ret = toConvert;

    ret.replace("&", "&#38;");
    ret.replace("<", "&#60;");
    ret.replace(">", "&#62;");
    ret.replace(QRegExp("\\b((?:https?|ftp)://[^\\s]+)", Qt::CaseInsensitive), "<a href='\\1'>\\1</a>");

    return ret;
}

QByteArray md5_hash(const QByteArray &result) {
    return QCryptographicHash::hash(result, QCryptographicHash::Md5).toHex();
}

void createIntMapper(QObject *src, const char *signal, QObject *dest, const char *slot, int id)
{
    QSignalMapper *mymapper = new QSignalMapper(src);
    mymapper->setMapping(src, id);
    src->connect(src, signal, mymapper, SLOT(map()));
    src->connect(mymapper, SIGNAL(mapped(int)), dest, slot);
}

QString slug(const QString &s)
{
    QString ret = "";

    foreach(QChar c, s) {
        if (c.isLetter() || c.isDigit() || c == '_') {
            ret += c.toLower();
        }
    }

    return ret;
}

void writeSettings(QWidget *w)
{
    QSettings settings;

    settings.beginGroup(w->metaObject()->className());
    settings.setValue("size", w->topLevelWidget()->size());
    settings.setValue("pos", w->topLevelWidget()->pos());
    settings.endGroup();
}

void loadSettings(QWidget *w, const QSize &defaultSize)
{
    QSettings settings;

    settings.beginGroup(w->metaObject()->className());
    if (settings.contains("size") || !defaultSize.isNull())
        w->topLevelWidget()->resize(settings.value("size", defaultSize).toSize());
    if (settings.contains("pos"))
        w->topLevelWidget()->move(settings.value("pos").toPoint());
    settings.endGroup();
}
