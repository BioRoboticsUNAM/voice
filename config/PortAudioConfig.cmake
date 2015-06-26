# - Try to find PortAudio
# Once done this will define
#
# PortAudio_FOUND          - set to true if PortAudio was found
# PortAudio_LIBRARY      - link these to use PortAudio
# PortAudio_INCLUDE_DIR    - path to PortAudio header files

if (PortAudio_LIBRARY AND PortAudio_INCLUDE_DIR)
	# in cache already
	set(PortAudio_FOUND TRUE)
	message(STATUS "Found PortAudio at: ${PortAudio_LIBRARY}")
else (PortAudio_LIBRARY AND PortAudio_INCLUDE_DIR)

	set(CANDIDATE_LIB_DIR
		/usr/lib
		/usr/local/lib
		/opt/local/lib
		/sw/lib
		/usr/lib/x86_64-linux-gnu/
	)

	set(CANDIDATE_INC_DIR
		/usr/include
		/usr/local/include
	)

	find_path(PortAudio_INCLUDE_DIR portaudio.h ${CANDIDATE_INC_DIR})
	find_library(PortAudio_LIBRARY portaudio ${CANDIDATE_LIB_DIR})

	# status output
	include(FindPackageHandleStandardArgs)

	find_package_handle_standard_args(PortAudio
		DEFAULT_MSG
		PortAudio_LIBRARY
		PortAudio_INCLUDE_DIR
	)
	mark_as_advanced(
		PortAudio_INCLUDE_DIR
		PortAudio_LIBRARY
	)

	message(STATUS "Found PortAudio at ${PortAudio_LIBRARY}")

endif (PortAudio_LIBRARY AND PortAudio_INCLUDE_DIR)
