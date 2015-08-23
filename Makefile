CXX := g++
CXX_FLAGS := -g -std=c++11

LIBS := `pkg-config --libs sdl2 SDL2_image SDL2_mixer jsoncpp`
CXX_FLAGS += `pkg-config --cflags sdl2 SDL2_image SDL2_mixer jsoncpp` -std=c++11
CXX_FLAGS += -I inc -I jsoncpp

EM_CXX := ~/Programs/emsdk_portable/emscripten/tag-1.34.3/em++
EM_CXX_FLAGS := -I inc -I jsoncpp/include
EM_CXX_FLAGS += -s USE_SDL=2 -s USE_SDL_IMAGE=2 -std=c++11 -s ASM_JS=1 -O3 \
	--preload-file ./asset

OUT_DIR := out
SRC_DIR := src
INC_DIR := inc
$(shell mkdir -p $(OUT_DIR))

SRCS := $(wildcard $(SRC_DIR)/*)
INCS := $(wildcard $(INC_DIR)/*)
OBJS := $(addprefix $(OUT_DIR)/, $(SRCS:.cpp=.o))
BCS := $(addprefix $(OUT_DIR)/, $(SRCS:.cpp=.bc))

JSONCPP_SRCS := $(wildcard ./jsoncpp/src/lib_json/*.cpp)
BCS += $(addprefix $(OUT_DIR)/, $(JSONCPP_SRCS:.cpp=.bc))

OUT_EXE := ld33
OUT_WEBPAGE := ld33.html

all: $(OUT_EXE)
web: $(OUT_WEBPAGE)

$(OUT_EXE): $(OBJS)
	@echo "[OUT]	$@"
	@$(CXX) $^ $(LIBS) -o $@

$(OUT_DIR)/%.o: %.cpp
	@echo "[CXX]	$@"
	@mkdir -p $(dir $@)
	@$(CXX) $< $(CXX_FLAGS) -c -o $@

$(OUT_WEBPAGE): $(BCS)
	@echo "[EM_OUT]	$@"
	@$(EM_CXX) $^ $(EM_CXX_FLAGS) -o $@

$(OUT_DIR)/%.bc: %.cpp
	@echo "[EM_CXX]	$@"
	@mkdir -p $(dir $@)
	@$(EM_CXX) $< $(EM_CXX_FLAGS) -c -o $@

.PHONY: clean
clean:
	@rm -fvr $(OUT_DIR) $(OUT_EXE)
