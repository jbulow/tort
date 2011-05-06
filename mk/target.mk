######################################################################

GEN_FILES = 

GEN_LIBS = 

GEN_H_GEN_FILES := $(shell ls include/tort/*.h.gen 2>/dev/null | sort -u | grep -v 'include/tort/*.h.gen')
GEN_H_FILES = $(GEN_H_GEN_FILES:%.gen=%)
GEN_FILES += $(GEN_H_FILES)
GEN_C_FILES = #

LIB_CFILES := $(shell ls src/*.c $(GEN_C_FILES) | sort -u)
LIB_HFILES := $(shell ls include/tort/*.h $(GEN_H_FILES) 2>/dev/null | sort -u | grep -v 'include/tort/*.h') 
LIB_OFILES = $(LIB_CFILES:.c=.lo)

GEN_LIBS += $(LIB) #

export LIB_CFILES
export LIB_HFILES
export LIB_OFILES

GEN_LIBS += $(LIB) #
GEN_LIBS += $(LIB:.a=.so) #

export CC
export CFLAGS

######################################################################

TEST_C_FILES = $(shell ls t/*.c | sort -u)
TEST_T_FILES = $(TEST_C_FILES:.c=.t)
TEST_FILES = $(TEST_C_FILES:.c=)
TEST_OUT_FILES = $(TEST_C_FILES:.c=.out)

######################################################################
# default:
#

all : components tests
	@for d in $(SUBDIRS) .; do [ $$d = '.' ] && break; $(MAKE) -C "$$d" all; done

components : early $(GEN_H_FILES) $(GEN_C_FILES) libs 

libs : $(LIBS_EARLY) $(GEN_LIBS)

early : early-headers early-files check-gen-new

early-headers: boot/include/.touch

GEN_FILES_NEW=$(GEN_FILES:%.gen=%.new)#

check-gen-new : $(GEN_FILES_NEW)
	@set -e ;\
	for f in $(GEN_FILES_NEW:%.new=%) ;\
	do \
	  cmp -s "$$f.new" "$$f" || cp -p "$$f.new" "$$f" ;\
	done

boot: boot/include/.touch

boot/include/.touch :
	@mkdir -p $$(dirname $@)
	set -ex; for f in $(GEN_H_FILES); do \
	  dst="boot/$$f" ;\
	  mkdir -p `dirname $$dst` ;\
	  cat $$f.begin $$f.end > $$dst ;\
	  cp "$$dst" "$$f" ;\
	done
	touch $@

######################################################################
# include:
#

includes : $(GEN_H_FILES)

early-files: $(GEN_H_FILES:%=%.new)

%.new : %.gen
	$(@:.new=).gen $(@:.new=) $@

######################################################################
# src:
#

srcs : $(GEN_C_FILES)

######################################################################
# object:
#

%.lo : %.c
	$(COMPILE.c) -o $@ $<

%.s : %.c 
	$(CC_BASE) -S -o $@ $<

######################################################################
# library:
#

$(LIB) : $(LIB_OFILES)
	$(LIBTOOL) --mode=link $(CC) $(LDFLAGS) $(LIB_FLAGS) -o $@ $(LIB_OFILES)
	$(LIBTOOL) --mode=install cp $@ $(libdir)

$(LIB_OFILES) : $(LIB_HFILES)

######################################################################
# testing:
#

# TEST_LIBS = $(LIB_TORT)

%.t : %.c 
	$(LIBTOOL) --mode=link $(CC) $(CFLAGS) $(LDFLAGS) $(@:.t=.c) $(TEST_LIBS) $(LIBS) -o $@

tests : components $(TEST_T_FILES) 

$(TEST_T_FILES) : $(TEST_LIBS)

$(TEST_T_FILES) $(LIB_OFILES) : $(GEN_H_FILES) include/tort/*.h 

run-test : tests
	@set -ex; for f in $(TEST_T_FILES); do \
	  $$f ;\
	done
	for d in $(SUBDIRS) .; do [ $$d = '.' ] && break; $(MAKE) -C "$$d" run-test; done

test : tests
	@echo "Testing:"
	$(BASE_DIR)tool/t run $(TEST_FILES)
	for d in $(SUBDIRS) .; do [ $$d = '.' ] && break; $(MAKE) -C "$$d" test; done

valgrind : tests
	@echo "Valgrind:"
	$(BASE_DIR)tool/t valgrind $(TEST_FILES)
	for d in $(SUBDIRS) .; do [ $$d = '.' ] && break; $(MAKE) -C "$$d" valgrind; done

accept-test : tests
	@set -ex; for f in $(TEST_FILES); do \
	  if [ ! -f $$f.exp ] ; then cp $$f.out $$f.exp ; git add `ls $$f.{c,exp,in}`; fi ;\
	done

accept-all-test : tests
	@set -ex; for f in $(TEST_FILES); do \
	  if [ -f $$f.out ] ; then cp $$f.out $$f.exp ; git add `ls $$f.{c,exp,in}`; fi ;\
	done

######################################################################
# maint:
#

clean :
	rm -f $(TEST_T_FILES) $(GEN_LIBS) src/*{.o,.lo,.la} t/*.{t,out} $(GEN_C_FILES) $(GEN_H_FILES) .stats/*
	rm -rf boot/include
	find . -name '*.dSYM' -type d -print0 | xargs -0 rm -rf
	@for d in $(SUBDIRS) .; do [ "$$d" = '.' ] && break; $(MAKE) -C "$$d" clean; done

very-clean : clean

FIND_STAT_FILES= \
   -name '*.h' -o -name '*.c' \
-o -name '*.in' \
-o -name '*.begin' -o -name '*.end' -o -name '*.gen' \
-o -name Makefile

stats :
	@mkdir -p .stats
	@echo "`/bin/pwd`:"
	@echo "Generated LoC:"
	@find $(GEN_H_FILES) $(GEN_C_FILES) 2>/dev/null | \
	  sort -u > .stats/files_gen
	@xargs wc -l < .stats/files_gen
	@echo "Source LoC:"
	@find src include $(FIND_STAT_FILES) | \
	  sort -u > .stats/files.t
	@comm -23 .stats/files.t .stats/files_gen > .stats/files_src
	@xargs wc -l < .stats/files_src
	@echo "Test LoC:"
	@find t $(FIND_STAT_FILES) | \
	  sort -u > .stats/files.t
	@comm -23 .stats/files.t .stats/files_gen > .stats/files_t
	@xargs wc -l < .stats/files_t
	@for d in $(SUBDIRS) .; do [ "$$d" = '.' ] && break; $(MAKE) -C "$$d" stats; done
