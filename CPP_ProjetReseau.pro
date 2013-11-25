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
    phases/networkbuilder.cpp \
    view/b2bview.cpp \
    view/panel/locationpanel.cpp \
    view/panel/buildingpanel.cpp \
    view/panel/defaultpanel.cpp \
    view/panel/b2bpanel.cpp

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
    phases/networkbuilder.h \
    view/b2bview.h \
    view/panel/locationpanel.h \
    view/panel/buildingpanel.h \
    view/panel/defaultpanel.h \
    view/panel/b2bpanel.h
