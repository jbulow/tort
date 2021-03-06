/* -*- c -*- */
/* Sources:
include/tort/box.h
include/tort/config.h
include/tort/core.h
include/tort/d_m.h
include/tort/d_mt.h
include/tort/d_s.all.h
include/tort/d_s.h
include/tort/d_slot.h
include/tort/fixnum.h
include/tort/internal.h
include/tort/ops.h
include/tort/tort.h
src/cmp.c
src/debug.c
src/dynlib.c
src/eq.c
src/error.c
src/fixnum.c
src/gc.c
src/init.c
src/io.c
src/literal.c
src/locative.c
src/lookup.c
src/map.c
src/message.c
src/method.c
src/mtable.c
src/object.c
src/pair.c
src/printf.c
src/ptr.c
src/slot.c
src/string.c
src/symbol.c
src/symbol_encoding.c
src/tagged.c
src/value.c
src/vector.c
src/word.c
src/write.c
*/
tort_d_s(ADD)
tort_d_s(AND)
tort_d_s(CMP)
tort_d_s(DIV)
tort_d_s(EQ)
tort_d_s(GE)
tort_d_s(GT)
tort_d_s(INV)
tort_d_s(LAND)
tort_d_s(LE)
tort_d_s(LOR)
tort_d_s(LSH)
tort_d_s(LT)
tort_d_s(MOD)
tort_d_s(MUL)
tort_d_s(NE)
tort_d_s(NEG)
tort_d_s(NOT)
tort_d_s(OR)
tort_d_s(RSH)
tort_d_s(SUB)
tort_d_s(XOR)
tort_d_s(__debugger)
tort_d_s(__finalize)
tort_d_s(__message)
tort_d_s(__new)
tort_d_s(__printfs)
tort_d_s(__printfsv)
tort_d_s(__read)
tort_d_s(__register_finalizer)
tort_d_s(__stat)
tort_d_s(__write)
tort_d_s(_add)
tort_d_s(_allocate)
tort_d_s(_append)
tort_d_s(_applyf)
tort_d_s(_applyfSET)
tort_d_s(_cannot_apply)
tort_d_s(_ccall)
tort_d_s(_ccallv)
tort_d_s(_create)
tort_d_s(_data)
tort_d_s(_delegate_changed)
tort_d_s(_delete_n)
tort_d_s(_error)
tort_d_s(_fatal)
tort_d_s(_gc_free)
tort_d_s(_gc_mark)
tort_d_s(_initialize)
tort_d_s(_inspect)
tort_d_s(_load_methods)
tort_d_s(_load_slots)
tort_d_s(_load_symtab)
tort_d_s(_method_changed)
tort_d_s(_method_not_found)
tort_d_s(_mtable)
tort_d_s(_mtableSET)
tort_d_s(_name)
tort_d_s(_new)
tort_d_s(_object_ptr)
tort_d_s(_ops)
tort_d_s(_printf_dispatch)
tort_d_s(_printfv)
tort_d_s(_ptr_data)
tort_d_s(_ref)
tort_d_s(_run_initializers)
tort_d_s(_set_slot_at)
tort_d_s(_slot_at)
tort_d_s(_slot_locative_at)
tort_d_s(_tag)
tort_d_s(_to_c_ptr)
tort_d_s(_to_literal)
tort_d_s(_to_string)
tort_d_s(_value)
tort_d_s(_version_change)
tort_d_s(_word)
tort_d_s(_word_data)
tort_d_s(_write)
tort_d_s(add)
tort_d_s(add_method)
tort_d_s(alias_method)
tort_d_s(all)
tort_d_s(alloc_size)
tort_d_s(allocate)
tort_d_s(append)
tort_d_s(argc)
tort_d_s(argcSET)
tort_d_s(attach)
tort_d_s(backtrace)
tort_d_s(bdw_all_interior_pointers)
tort_d_s(bdw_dont_expand)
tort_d_s(bdw_dont_gc)
tort_d_s(bdw_dont_precollect)
tort_d_s(bdw_finalize_on_demand)
tort_d_s(bdw_free_space_divisor)
tort_d_s(bdw_full_freq)
tort_d_s(bdw_gc_no)
tort_d_s(bdw_get_bytes_since_gc)
tort_d_s(bdw_get_free_bytes)
tort_d_s(bdw_get_heap_size)
tort_d_s(bdw_get_total_bytes)
tort_d_s(bdw_java_finalization)
tort_d_s(bdw_max_retries)
tort_d_s(bdw_no_dls)
tort_d_s(bdw_non_gc_bytes)
tort_d_s(bdw_use_entire_heap)
tort_d_s(blksize)
tort_d_s(block)
tort_d_s(blocks)
tort_d_s(boolean)
tort_d_s(bop)
tort_d_s(caller_info)
tort_d_s(caller_infoSET)
tort_d_s(clone)
tort_d_s(close)
tort_d_s(cmp)
tort_d_s(data)
tort_d_s(dataSET)
tort_d_s(debug)
tort_d_s(delegate)
tort_d_s(delegateSET)
tort_d_s(delegates)
tort_d_s(delete)
tort_d_s(dev)
tort_d_s(dl_maps)
tort_d_s(dlopen)
tort_d_s(dynlib)
tort_d_s(dynlib_global_prefix)
tort_d_s(dynlib_suffix)
tort_d_s(each)
tort_d_s(element_size)
tort_d_s(emit)
tort_d_s(emptyE)
tort_d_s(encode)
tort_d_s(eof)
tort_d_s(eos)
tort_d_s(eq)
tort_d_s(eqCMP)
tort_d_s(eqQ)
tort_d_s(equalQ)
tort_d_s(equality)
tort_d_s(equalitySET)
tort_d_s(eqvCMP)
tort_d_s(eqvQ)
tort_d_s(error)
tort_d_s(escape)
tort_d_s(fiber)
tort_d_s(fiberSET)
tort_d_s(file)
tort_d_s(fileSET)
tort_d_s(first)
tort_d_s(firstSET)
tort_d_s(fixnum)
tort_d_s(flags)
tort_d_s(flagsSET)
tort_d_s(flush)
tort_d_s(fp)
tort_d_s(fpSET)
tort_d_s(gc)
tort_d_s(gc_collect)
tort_d_s(gc_data)
tort_d_s(gc_dataSET)
tort_d_s(gc_free_method)
tort_d_s(gc_free_methodSET)
tort_d_s(gc_mark_method)
tort_d_s(gc_mark_methodSET)
tort_d_s(gc_ready)
tort_d_s(gc_stats)
tort_d_s(get)
tort_d_s(get_entry)
tort_d_s(get_entry_by_value)
tort_d_s(get_entry_cstr)
tort_d_s(get_entry_string)
tort_d_s(get_key)
tort_d_s(get_string)
tort_d_s(gid)
tort_d_s(go)
tort_d_s(identity)
tort_d_s(initialize)
tort_d_s(initialized)
tort_d_s(initializer)
tort_d_s(initializing)
tort_d_s(ino)
tort_d_s(instance_size)
tort_d_s(instance_sizeSET)
tort_d_s(io)
tort_d_s(io_stderr)
tort_d_s(io_stdin)
tort_d_s(io_stdout)
tort_d_s(line)
tort_d_s(lineSET)
tort_d_s(load)
tort_d_s(locative)
tort_d_s(lookup)
tort_d_s(lop)
tort_d_s(lup)
tort_d_s(malloc)
tort_d_s(map)
tort_d_s(mapE)
tort_d_s(mark)
tort_d_s(message)
tort_d_s(method)
tort_d_s(methodSET)
tort_d_s(mode)
tort_d_s(modeSET)
tort_d_s(mtable)
tort_d_s(mtableSET)
tort_d_s(mtable_method_map)
tort_d_s(mtable_method_mapSET)
tort_d_s(name)
tort_d_s(nameSET)
tort_d_s(new)
tort_d_s(new_class)
tort_d_s(new_mtable)
tort_d_s(new_value)
tort_d_s(nil)
tort_d_s(nlink)
tort_d_s(not)
tort_d_s(nullQ)
tort_d_s(object)
tort_d_s(object_changed_mtable_from)
tort_d_s(object_changing_mtable_to)
tort_d_s(offset)
tort_d_s(offsetSET)
tort_d_s(open)
tort_d_s(openQ)
tort_d_s(pair)
tort_d_s(popen)
tort_d_s(previous_message)
tort_d_s(previous_messageSET)
tort_d_s(printf)
tort_d_s(printf_as_string)
tort_d_s(prog_symtab)
tort_d_s(ptr)
tort_d_s(rdev)
tort_d_s(read)
tort_d_s(receiver)
tort_d_s(receiverSET)
tort_d_s(remove_method)
tort_d_s(resize)
tort_d_s(rop)
tort_d_s(runtime)
tort_d_s(second)
tort_d_s(secondSET)
tort_d_s(selector)
tort_d_s(selectorSET)
tort_d_s(set)
tort_d_s(size)
tort_d_s(sizeSET)
tort_d_s(slot)
tort_d_s(slots)
tort_d_s(string)
tort_d_s(symbol)
tort_d_s(symbol_encoder)
tort_d_s(tagged)
tort_d_s(tort_finalize_n)
tort_d_s(tort_finalizer_n)
tort_d_s(tort_free_atomic_n)
tort_d_s(tort_free_n)
tort_d_s(tort_malloc_atomic_bytes)
tort_d_s(tort_malloc_atomic_n)
tort_d_s(tort_malloc_bytes)
tort_d_s(tort_malloc_n)
tort_d_s(tort_object_alloc_bytes)
tort_d_s(tort_object_alloc_n)
tort_d_s(tort_realloc_atomic_bytes)
tort_d_s(tort_realloc_atomic_n)
tort_d_s(tort_realloc_bytes)
tort_d_s(tort_realloc_n)
tort_d_s(tort_v)
tort_d_s(type)
tort_d_s(typeSET)
tort_d_s(u8vector)
tort_d_s(uid)
tort_d_s(unescapeE)
tort_d_s(uop)
tort_d_s(value)
tort_d_s(valueSET)
tort_d_s(value_locative)
tort_d_s(vector)
tort_d_s(vector_base)
tort_d_s(version)
tort_d_s(versionSET)
tort_d_s(word)
/* -*- c -*- */
#undef tort_d_s
