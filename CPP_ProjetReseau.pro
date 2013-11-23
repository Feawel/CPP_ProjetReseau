SOURCES += \
    model/address.cpp \
    model/link.cpp \
    model/location/location.cpp \
    model/location/floor.cpp \
    model/location/building_building.cpp \
    model/location/building.cpp \
    model/component/switch.cpp \
    model/component/router.cpp \
    model/component/port.cpp \
    model/component/firewall.cpp \
    model/component/component.cpp \
    model/component/backbone.cpp \
    main.cpp \
    view/requestinterface.cpp \
    view/buildingview.cpp \
    phases/request.cpp \
    view/locationpanel.cpp \
    phases/networkbuilder.cpp

QT += widgets

HEADERS += \
    model/address.h \
    model/constant.h \
    model/link.h \
    model/location/location.h \
    model/location/floor.h \
    model/location/building_building.h \
    model/location/building.h \
    model/component/switch.h \
    model/component/router.h \
    model/component/port.h \
    model/component/firewall.h \
    model/component/component.h \
    model/component/backbone.h \
    view/requestinterface.h \
    view/buildingview.h \
    phases/request.h \
    view/locationpanel.h \
    phases/networkbuilder.h
