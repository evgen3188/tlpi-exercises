include Makefile.inc

TLPI_URL = "http://man7.org/tlpi/code/download/tlpi-151105-dist.tar.gz"

BUILD_DIRS = fileio

all: download buildlib build

cleanall: cleanlib clean

update: remove download

# Note: Order of defining targets is important
remove:
	@echo "Removing $(TLPI_DIR)"
	@rm -rf $(TLPI_DIR)

download:
ifeq ($(wildcard $(TLPI_DIR)),)
	@echo "Downloading tlpi files"
	/usr/bin/curl -OLsS $(TLPI_URL)

# Note: The following lines with '\' are shell commands
# @ in the beginning of the line suppresses echoing
	@FILE=`ls | grep "^tlpi.*dist\.tar\.gz"`; \
	echo "$$FILE was downloaded"; \
	tar xfz $$FILE; \
	rm $$FILE
endif

buildlib:
ifeq ($(wildcard $(TLPI_LIB)),)
	@echo "Making $(TLPI_LIB)"
	@cd $(TLPI_DIR)/lib && $(MAKE)
endif

build:
	@echo "Building"
	@for dir in $(BUILD_DIRS); do (cd $$(dir); $(MAKE)); done

cleanlib:
	@cd $(TLPI_DIR)/lib && $(MAKE) clean

clean:
	@for dir in $(BUILD_DIRS); do (cd $$(dir); $(MAKE) clean); done
