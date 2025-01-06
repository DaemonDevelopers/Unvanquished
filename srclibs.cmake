set(CRUNCHLIST
    ${LIB_DIR}/crunch/inc/crn_decomp.h
    ${LIB_DIR}/crunch/inc/crnlib.h
)

set(FINDLOCALELIST
    ${LIB_DIR}/findlocale/findlocale.c
)

set(MINIZIPLIST
    ${LIB_DIR}/minizip/ioapi.c
    ${LIB_DIR}/minizip/ioapi.h
    ${LIB_DIR}/minizip/unzip.c
    ${LIB_DIR}/minizip/unzip.h
)

if (USE_MUMBLE)
set(MUMBLELINKLIST
    ${LIB_DIR}/mumblelink/libmumblelink.cpp
    ${LIB_DIR}/mumblelink/libmumblelink.h
)
endif()

set(NACLLIST_MODULE
    ${LIB_DIR}/nacl/native_client/src/shared/imc/nacl/nacl_imc.cc
    ${LIB_DIR}/nacl/native_client/src/shared/imc/nacl_imc_common.cc
    ${LIB_DIR}/nacl/native_client/src/untrusted/nacl/imc_accept.c
    ${LIB_DIR}/nacl/native_client/src/untrusted/nacl/imc_connect.c
    ${LIB_DIR}/nacl/native_client/src/untrusted/nacl/imc_makeboundsock.c
    ${LIB_DIR}/nacl/native_client/src/untrusted/nacl/imc_mem_obj_create.c
    ${LIB_DIR}/nacl/native_client/src/untrusted/nacl/imc_recvmsg.c
    ${LIB_DIR}/nacl/native_client/src/untrusted/nacl/imc_sendmsg.c
    ${LIB_DIR}/nacl/native_client/src/untrusted/nacl/imc_socketpair.c
)

if (APPLE)
    set(NACLLIST_NATIVE
        ${LIB_DIR}/nacl/native_client/src/shared/imc/nacl_imc_common.cc
        ${LIB_DIR}/nacl/native_client/src/shared/imc/posix/nacl_imc_posix.cc
        ${LIB_DIR}/nacl/native_client/src/shared/imc/osx/nacl_imc.cc
    )
elseif (LINUX OR FREEBSD)
    set(NACLLIST_NATIVE
        ${LIB_DIR}/nacl/native_client/src/shared/imc/nacl_imc_common.cc
        ${LIB_DIR}/nacl/native_client/src/shared/imc/posix/nacl_imc_posix.cc
        ${LIB_DIR}/nacl/native_client/src/shared/imc/linux/nacl_imc.cc
    )
elseif (WIN32)
    set(NACLLIST_NATIVE
        ${LIB_DIR}/nacl/native_client/src/shared/imc/nacl_imc_common.cc
        ${LIB_DIR}/nacl/native_client/src/shared/imc/win/nacl_imc.cc
        ${LIB_DIR}/nacl/native_client/src/shared/imc/win/nacl_shm.cc
    )
endif()

set(PDCURSESLIST
    ${LIB_DIR}/pdcursesmod/curses.h
    ${LIB_DIR}/pdcursesmod/curspriv.h
    ${LIB_DIR}/pdcursesmod/panel.h
    ${LIB_DIR}/pdcursesmod/term.h
    ${LIB_DIR}/pdcursesmod/pdcurses/addch.c
    ${LIB_DIR}/pdcursesmod/pdcurses/addchstr.c
    ${LIB_DIR}/pdcursesmod/pdcurses/addstr.c
    ${LIB_DIR}/pdcursesmod/pdcurses/attr.c
    ${LIB_DIR}/pdcursesmod/pdcurses/beep.c
    ${LIB_DIR}/pdcursesmod/pdcurses/bkgd.c
    ${LIB_DIR}/pdcursesmod/pdcurses/border.c
    ${LIB_DIR}/pdcursesmod/pdcurses/clear.c
    ${LIB_DIR}/pdcursesmod/pdcurses/color.c
    ${LIB_DIR}/pdcursesmod/pdcurses/debug.c
    ${LIB_DIR}/pdcursesmod/pdcurses/delch.c
    ${LIB_DIR}/pdcursesmod/pdcurses/deleteln.c
    ${LIB_DIR}/pdcursesmod/pdcurses/getch.c
    ${LIB_DIR}/pdcursesmod/pdcurses/getstr.c
    ${LIB_DIR}/pdcursesmod/pdcurses/getyx.c
    ${LIB_DIR}/pdcursesmod/pdcurses/inch.c
    ${LIB_DIR}/pdcursesmod/pdcurses/inchstr.c
    ${LIB_DIR}/pdcursesmod/pdcurses/initscr.c
    ${LIB_DIR}/pdcursesmod/pdcurses/inopts.c
    ${LIB_DIR}/pdcursesmod/pdcurses/insch.c
    ${LIB_DIR}/pdcursesmod/pdcurses/insstr.c
    ${LIB_DIR}/pdcursesmod/pdcurses/instr.c
    ${LIB_DIR}/pdcursesmod/pdcurses/kernel.c
    ${LIB_DIR}/pdcursesmod/pdcurses/keyname.c
    ${LIB_DIR}/pdcursesmod/pdcurses/mouse.c
    ${LIB_DIR}/pdcursesmod/pdcurses/move.c
    ${LIB_DIR}/pdcursesmod/pdcurses/outopts.c
    ${LIB_DIR}/pdcursesmod/pdcurses/overlay.c
    ${LIB_DIR}/pdcursesmod/pdcurses/pad.c
    ${LIB_DIR}/pdcursesmod/pdcurses/panel.c
    ${LIB_DIR}/pdcursesmod/pdcurses/printw.c
    ${LIB_DIR}/pdcursesmod/pdcurses/refresh.c
    ${LIB_DIR}/pdcursesmod/pdcurses/scanw.c
    ${LIB_DIR}/pdcursesmod/pdcurses/scr_dump.c
    ${LIB_DIR}/pdcursesmod/pdcurses/scroll.c
    ${LIB_DIR}/pdcursesmod/pdcurses/slk.c
    ${LIB_DIR}/pdcursesmod/pdcurses/termattr.c
    ${LIB_DIR}/pdcursesmod/pdcurses/terminfo.c
    ${LIB_DIR}/pdcursesmod/pdcurses/touch.c
    ${LIB_DIR}/pdcursesmod/pdcurses/util.c
    ${LIB_DIR}/pdcursesmod/pdcurses/window.c
)

if (WIN32)
	set(PDCURSESLIST
		${PDCURSESLIST}
		${LIB_DIR}/pdcursesmod/wingui/pdcclip.c
		${LIB_DIR}/pdcursesmod/wingui/pdcdisp.c
		${LIB_DIR}/pdcursesmod/wingui/pdcgetsc.c
		${LIB_DIR}/pdcursesmod/wingui/pdckbd.c
		${LIB_DIR}/pdcursesmod/wingui/pdcscrn.c
		${LIB_DIR}/pdcursesmod/wingui/pdcsetsc.c
		${LIB_DIR}/pdcursesmod/wingui/pdcutil.c
		${LIB_DIR}/pdcursesmod/wingui/pdcwin.h
	)
else()
	set(PDCURSESLIST
		${PDCURSESLIST}
		${LIB_DIR}/pdcursesmod/vt/pdcclip.c
		${LIB_DIR}/pdcursesmod/vt/pdcdisp.c
		${LIB_DIR}/pdcursesmod/vt/pdcgetsc.c
		${LIB_DIR}/pdcursesmod/vt/pdckbd.c
		${LIB_DIR}/pdcursesmod/vt/pdcscrn.c
		${LIB_DIR}/pdcursesmod/vt/pdcsetsc.c
		${LIB_DIR}/pdcursesmod/vt/pdcutil.c
		${LIB_DIR}/pdcursesmod/vt/pdcvt.h
	)
endif()

set(TINYFORMATLIST
    ${LIB_DIR}/tinyformat/tinyformat.h
)

set(TINYGETTEXTLIST
    ${FINDLOCALELIST}
    ${LIB_DIR}/tinygettext/dictionary.cpp
    ${LIB_DIR}/tinygettext/dictionary.hpp
    ${LIB_DIR}/tinygettext/dictionary_manager.cpp
    ${LIB_DIR}/tinygettext/dictionary_manager.hpp
    ${LIB_DIR}/tinygettext/file_system.hpp
    ${LIB_DIR}/tinygettext/iconv.cpp
    ${LIB_DIR}/tinygettext/iconv.hpp
    ${LIB_DIR}/tinygettext/language.cpp
    ${LIB_DIR}/tinygettext/language.hpp
    ${LIB_DIR}/tinygettext/log.cpp
    ${LIB_DIR}/tinygettext/log.hpp
    ${LIB_DIR}/tinygettext/log_stream.hpp
    ${LIB_DIR}/tinygettext/plural_forms.cpp
    ${LIB_DIR}/tinygettext/plural_forms.hpp
    ${LIB_DIR}/tinygettext/po_parser.cpp
    ${LIB_DIR}/tinygettext/po_parser.hpp
    ${LIB_DIR}/tinygettext/tinygettext.cpp
    ${LIB_DIR}/tinygettext/tinygettext.hpp
)

if (WIN32)
    set(BREAKPAD_COMMON_LIST
        ${LIB_DIR}/breakpad/src/common/windows/guid_string.cc
        ${LIB_DIR}/breakpad/src/common/windows/guid_string.h
        ${LIB_DIR}/breakpad/src/common/windows/http_upload.cc
        ${LIB_DIR}/breakpad/src/common/windows/http_upload.h
        ${LIB_DIR}/breakpad/src/common/windows/string_utils.cc
    )
    set(BREAKPAD_CRASHGENERATIONSERVER_LIST
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/client_info.cc
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/crash_generation_server.cc
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/minidump_generator.cc
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/client_info.h
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/crash_generation_client.h
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/crash_generation_server.h
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/minidump_generator.h
    )
    set(BREAKPAD_CRASHGENERATIONCLIENT_LIST
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/crash_generation_client.h
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/crash_generation_client.cc
        ${LIB_DIR}/breakpad/src/client/windows/crash_generation/crash_generation_server.h
    )
    set(BREAKPAD_EXCEPTIONHANDLER_LIST
        ${LIB_DIR}/breakpad/src/client/windows/handler/exception_handler.cc
        ${LIB_DIR}/breakpad/src/client/windows/handler/exception_handler.h
    )
elseif (LINUX)
    set(BREAKPAD_LIST
        ${LIB_DIR}/breakpad/src/client/linux/crash_generation/crash_generation_client.cc
        ${LIB_DIR}/breakpad/src/client/linux/crash_generation/crash_generation_server.cc
        ${LIB_DIR}/breakpad/src/client/linux/dump_writer_common/thread_info.cc
        ${LIB_DIR}/breakpad/src/client/linux/dump_writer_common/ucontext_reader.cc
        ${LIB_DIR}/breakpad/src/client/linux/handler/exception_handler.cc
        ${LIB_DIR}/breakpad/src/client/linux/handler/exception_handler.h
        ${LIB_DIR}/breakpad/src/client/linux/handler/minidump_descriptor.cc
        ${LIB_DIR}/breakpad/src/client/linux/handler/minidump_descriptor.h
        ${LIB_DIR}/breakpad/src/client/linux/log/log.cc
        ${LIB_DIR}/breakpad/src/client/linux/log/log.h
        ${LIB_DIR}/breakpad/src/client/linux/microdump_writer/microdump_writer.cc
        ${LIB_DIR}/breakpad/src/client/linux/microdump_writer/microdump_writer.h
        ${LIB_DIR}/breakpad/src/client/linux/minidump_writer/linux_core_dumper.cc
        ${LIB_DIR}/breakpad/src/client/linux/minidump_writer/linux_dumper.cc
        ${LIB_DIR}/breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.cc
        ${LIB_DIR}/breakpad/src/client/linux/minidump_writer/minidump_writer.cc
        ${LIB_DIR}/breakpad/src/client/minidump_file_writer-inl.h
        ${LIB_DIR}/breakpad/src/client/minidump_file_writer.cc
        ${LIB_DIR}/breakpad/src/client/minidump_file_writer.h
        ${LIB_DIR}/breakpad/src/common/convert_UTF.cc
        ${LIB_DIR}/breakpad/src/common/convert_UTF.h
        ${LIB_DIR}/breakpad/src/common/md5.cc
        ${LIB_DIR}/breakpad/src/common/md5.h
        ${LIB_DIR}/breakpad/src/common/string_conversion.cc
        ${LIB_DIR}/breakpad/src/common/string_conversion.h
        ${LIB_DIR}/breakpad/src/common/linux/elf_core_dump.cc
        ${LIB_DIR}/breakpad/src/common/linux/elfutils.cc
        ${LIB_DIR}/breakpad/src/common/linux/elfutils.h
        ${LIB_DIR}/breakpad/src/common/linux/file_id.cc
        ${LIB_DIR}/breakpad/src/common/linux/file_id.h
        ${LIB_DIR}/breakpad/src/common/linux/guid_creator.cc
        ${LIB_DIR}/breakpad/src/common/linux/guid_creator.h
        ${LIB_DIR}/breakpad/src/common/linux/linux_libc_support.cc
        ${LIB_DIR}/breakpad/src/common/linux/memory_mapped_file.cc
        ${LIB_DIR}/breakpad/src/common/linux/safe_readlink.cc
    )
endif()
