RESULT = cape.out

OPENCV_INCLUDE = /usr/local/include/opencv4/

LIB_DIR = /usr/local/lib/

LINK_TO = -lopencv_core -lopencv_videoio -lopencv_highgui -lopencv_video -lopencv_imgproc

CXX_FLAGS =  \
-fsigned-char \
-W \
-Wall \
-Werror=return-type \
-Werror=non-virtual-dtor \
-Werror=address \
-Werror=sequence-point \
-Wformat \
-Werror=format-security \
-Wmissing-prototypes \
-Wstrict-prototypes \
-Winit-self \
-Wpointer-arith \
-Wshadow \
-Wsign-promo \
-Wuninitialized \
-Winit-self \
-Wno-narrowing \
-Wno-delete-non-virtual-dtor \
-Wno-unnamed-type-template-args \
-Wno-comment -fdiagnostics-show-option \
-Wno-long-long -Qunused-arguments \
-Wno-semicolon-before-method-body -ffunction-sections -fdata-sections  -fvisibility=hidden -fvisibility-inlines-hidden \
-Wno-missing-declarations \
-Wno-unused-parameter \
-Wno-undef \
-O3 \
-DNDEBUG \
-DNDEBUG \
-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk \
-fPIC \
-std=c++11

CXX_DEFINES = -D_FILE_OFFSET_BITS=64

cape: cape.cpp
	c++ $(CXX_DEFINES) -I$(OPENCV_INCLUDE) $(CXX_FLAGS) -L$(LIB_DIR) $(LINK_TO) -o bin/cape.out *.cpp

run:
	bin/$(RESULT)