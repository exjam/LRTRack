SLUG = LindenbergResearch
VERSION = 0.6.4-beta1
SOURCES += $(wildcard src/*.cpp src/dsp/*.cpp src/widgets/*.cpp)
DISTRIBUTABLES += $(wildcard LICENSE*) res
RACK_DIR ?= ../..

include $(RACK_DIR)/plugin.mk