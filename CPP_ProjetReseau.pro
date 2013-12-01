SOURCES += \
    model/address.cpp \
    model/location/location.cpp \
    model/location/floor.cpp \
    model/location/building_building.cpp \
    model/location/building.cpp \
    model/component/switch.cpp \
    model/component/router.cpp \
    model/component/firewall.cpp \
    model/component/component.cpp \
    model/component/backbone.cpp \
    main.cpp \
    view/requestinterface.cpp \
    model/request.cpp \
    phases/networkbuilder.cpp \
    view/panel/locationpanel.cpp \
    view/panel/buildingpanel.cpp \
    view/panel/defaultpanel.cpp \
    view/panel/b2bpanel.cpp \
    view/views/buildingview.cpp \
    view/views/b2bview.cpp \
    view/views/floorview.cpp \
    graph_view/graph_generate.cpp \
    txt_generation/table.cpp \
    txt_generation/txtgenerator.cpp \
    model/constant.cpp \
    tests/testsLocation.cpp \
    tests/testsFloor.cpp \
    tests/testsBuilding.cpp \
    tests/tests_building_building.cpp \
    tests/testsComponent.cpp \
    tests/testsFirewall.cpp

QT += widgets

HEADERS += \
    model/address.h \
    model/constant.h \
    model/location/location.h \
    model/location/floor.h \
    model/location/building_building.h \
    model/location/building.h \
    model/component/switch.h \
    model/component/router.h \
    model/component/firewall.h \
    model/component/component.h \
    model/component/backbone.h \
    view/requestinterface.h \
    model/request.h \
    phases/networkbuilder.h \
    view/panel/locationpanel.h \
    view/panel/buildingpanel.h \
    view/panel/defaultpanel.h \
    view/panel/b2bpanel.h \
    view/views/buildingview.h \
    view/views/b2bview.h \
    view/views/floorview.h \
    graph_view/graph_generate.h \
    txt_generation/table.h \
    txt_generation/txtgenerator.h \
    tests/testsLocation.h \
    tests/testsFloor.h \
    tests/testsBuilding.h \
    tests/tests_building_building.h \
    tests/testsComponent.h \
    tests/testsFirewall.h

OTHER_FILES +=
