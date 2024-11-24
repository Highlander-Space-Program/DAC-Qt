/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#include <mainwindow.h>
#include <subscriberqtadapter.h>


#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_DAC_Qt()
{
    qmlRegisterTypesAndRevisions<PressureSubscriberQtAdapter>("DAC-Qt", 1);
    QMetaType::fromType<QSettings *>().id();
    qmlRegisterTypesAndRevisions<QSettingsWrapper>("DAC-Qt", 1);
    qmlRegisterModule("DAC-Qt", 1, 0);
}

static const QQmlModuleRegistration registration("DAC-Qt", qml_register_types_DAC_Qt);
