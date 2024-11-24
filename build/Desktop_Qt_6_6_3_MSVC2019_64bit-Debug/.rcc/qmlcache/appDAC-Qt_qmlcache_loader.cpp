#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _0x5f_DAC_0x2d_Qt_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_Visualization_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_SettingsView_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_Navigation_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_Setup_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_components_visualization_MockChart_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_components_navigation_NavButton_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_components_settings_SettingsTextInput_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_components_settings_SettingsComboInput_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_components_settings_SettingsDivider_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _0x5f_DAC_0x2d_Qt_Chart_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/Main.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/Visualization.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_Visualization_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/SettingsView.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_SettingsView_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/Navigation.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_Navigation_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/Setup.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_Setup_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/components/visualization/MockChart.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_components_visualization_MockChart_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/components/navigation/NavButton.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_components_navigation_NavButton_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/components/settings/SettingsTextInput.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_components_settings_SettingsTextInput_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/components/settings/SettingsComboInput.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_components_settings_SettingsComboInput_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/components/settings/SettingsDivider.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_components_settings_SettingsDivider_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/DAC-Qt/Chart.qml"), &QmlCacheGeneratedCode::_0x5f_DAC_0x2d_Qt_Chart_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appDAC_Qt)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appDAC_Qt))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_appDAC_Qt)() {
    return 1;
}
