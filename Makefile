
.PHONY: clean
.SILENT: boost

TOP = .

DEBUG = -g -DDEBUG

ifdef USE_LOCAL_BOOST
BOOST_VERSION = 1_46_1
BOOST_INCLUDE_PATH = -I $(TOP)/bin/boost_$(BOOST_VERSION)
BOOST_LIB_PATH = -L $(TOP)/bin/boost_$(BOOST_VERSION)/stage/lib \
								 -Wl,-rpath-link $(TOP)/bin/boost_$(BOOST_VERSION)/stage/lib
else
BOOST_INCLUDE_PATH =
BOOST_LIB_PATH =
endif

INCLUDES = -I $(TOP)/includes $(BOOST_INCLUDE_PATH)
LDFLAGS = $(BOOST_LIB_PATH) -lboost_unit_test_framework

CXX = g++
CXXFLAGS = -Wall -Wextra $(DEBUG)
DOXYGEN = /usr/bin/doxygen
DOXYGEN_CONFIG = .dox_config

EXECUTABLE = prefixer

SRC = src/main.cpp \
			src/Prefixer.cpp

TEST_SRC = src/Prefixer.cpp \
					 tests/prefixer_test.cpp

all: boost $(EXECUTABLE) doc

$(EXECUTABLE): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) -o bin/$@ $^

tests: boost test run_tests

test: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) -o tests/prefixer_test $^

run_tests:
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):./bin/boost_$(BOOST_VERSION)/stage/lib ./tests/prefixer_test

ifdef USE_LOCAL_BOOST
boost:
	if test -d bin/boost_$(BOOST_VERSION); then \
		echo "Using local boost++" ; \
	else \
		echo "Building boost++" ; \
		tar -C bin -xzf libs/boost_1_46_1.tar.gz ; \
		cd bin/boost_1_46_1 && ./bootstrap.sh 2>&1 1>/dev/null && ./bjam 2>&1 1>/dev/null ; \
	fi
else
boost:
endif

doc:
	mkdir -p doc
	$(DOXYGEN) $(DOXYGEN_CONFIG)


help:
	@echo "Build prefixer"
	@echo ""
	@echo "Boost library is required to build. If the system does not"
	@echo "provide the Boost library and headers, you can build it by running:"
	@echo ""
	@echo "       make USE_LOCAL_BOOST=1 <target>"
	@echo ""
	@echo "    To build executable and documentation run"
	@echo ""
	@echo "       make all"
	@echo ""
	@echo "    To build and run tests"
	@echo ""
	@echo "       make tests"
	@echo ""
	@echo "    To run tests once they're built"
	@echo ""
	@echo "       make run_tests"
	@echo ""
	@echo "    To clean the build"
	@echo ""
	@echo "       make clean"

clean:
	rm -f bin/prefixer doc

