TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    robot.cpp

include(deployment.pri)
qtcAddDeployment()

