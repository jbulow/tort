BASE_DIR=.#
SUBDIRS=core ext lisp compiler#
include $(BASE_DIR)/mk/config.mk

#LIB=$(LIB_TORT)
#TEST_LIBS = $(LIB) $(LIB_TORT)

include $(BASE_DIR)/mk/target.mk

bootstrap : very-clean clean
	$(MAKE) -C core bootstrap
#	$(MAKE) clean 
#	$(MAKE)

clean ::
	rm -f tmp/*.* GPATH GRTAGS GTAGS

tags :
	gtags

######################################################################
# libgc.a:
#

ifneq "$(TORT_GC_BDW)" "0"
LIBS_EARLY += gc-bdw #

gc-bdw : $(GC_BDW)/.libs/libgc.a

$(GC_BDW)/.libs/libgc.a : $(BASE_DIR)/archive/$(GC_BDW_VERSION).tar.gz
	if [ ! -d $(GC_BDW) ]; then tar -zxvf $^; fi
	unset CFLAGS LDFLAGS; export CC='$(CC)'; cd $(GC_BDW) && if [ ! -f Makefile ]; then ./configure --enable-shared --enable-parallel-mark --enable-threads=posix --enable-large-config --enable-gc-debug USE_I686_PREFETCH=1 --prefix=$(PREFIX); fi
	unset CFLAGS LDFLAGS; export CC='$(CC)'; cd $(GC_BDW) && make && make install

$(BASE_DIR)/archive/$(GC_BDW_VERSION).tar.gz :
	mkdir -p $(BASE_DIR)/archive
	curl -Lk http://www.hpl.hp.com/personal/Hans_Boehm/gc/gc_source/$(GC_BDW_VERSION).tar.gz -o $@
endif

