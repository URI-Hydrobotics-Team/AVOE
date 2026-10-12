BUILD = build
BIN = avoe

MKDIR = mkdir

CC = g++

CFLAGS = -o avoe

TARGET = tardigrade_virtual
DEBUG = none

INCLUDES += -Icore
INCLUDES += -Ilib

SOURCES += core/motor.cpp \
	core/sensor.cpp \
	core/vehicle.cpp \
	core/log.cpp \
	core/io.cpp \
	lib/network.cpp \
	lib/lib.cpp \
	lib/clock.cpp \
	plugins/middleware/general-sensor/imu.cpp \
	plugins/drivers/sensors/imu-dummy/driver.cpp \
	plugins/middleware/general-sensor/pressure.cpp \
	plugins/drivers/sensors/pressure-sensor-dummy/driver.cpp \
	plugins/middleware/general-sensor/leak.cpp \
	plugins/drivers/sensors/leak-sensor-dummy/driver.cpp \
	plugins/controllers/tardigrade_basic/controller.cpp \
	plugins/controllers/tardigrade/controller.cpp \
	plugins/drivers/sensors/bnO055/driver.cpp \
	plugins/drivers/sensors/adafruit_bno055/driver.cpp \
	plugins/drivers/sensors/adafruit_bno055/tools/restore_offsets/restore_offsets.cpp \
	plugins/middleware/general-motor/ppsti_middleware/motor_mw.cpp \
	plugins/drivers/motors/ppsti/driver.cpp \
	plugins/drivers/sensors/bar30m/driver.cpp \
	plugins/mission_control/tardigrade_mc_relative/mc.cpp \
	plugins/drivers/other/avoe_user_io/driver.cpp 

all: $(TARGET)

ifeq ($(TARGET), tardigrade_virtual)

target: tardigrade_virtual 
	cc $(CFLAGS) $(SOURCES) 
else ifeq($(TARGET), tardigrade_virtual_verbose)
CFLAGS += -DVERBOSE
	cc $(CLFLAGS) $(SOURCES)
else ifeq($(TARGET), tardigrade_virtual_g)
CFLAGS += -g
CFLAGS += -fsanitize=address
else ifeq($(TARGET), tardigrade_physical)
CFLAGS += -DTARGET_TARDIGRADE
CFLAGS += -lgpio
CFLAGS += $(exec pkg-config --cflags --libs libserialport)
else
	echo "Specify one of the following options, 'tardigrade_virtual','tardigrade_virtual_verbose','tardigrade_virtual_g',
	'tardigrade_physical'"
endif



