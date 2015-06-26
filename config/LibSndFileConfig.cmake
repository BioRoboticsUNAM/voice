# - Try to find LibSndFile
# Once done this will define
#
# LibSndFile_FOUND          - set to true if LibSndFile was found
# LibSndFile_LIBRARY      - link these to use LibSndFile
# LibSndFile_INCLUDE_DIR    - path to LibSndFile header files

# if (LibSndFile_LIBRARY AND LibSndFile_INCLUDE_DIR)
if (LibSndFile_LIBRARY)
	# in cache already
	set(LibSndFile_FOUND TRUE)
# else (LibSndFile_LIBRARY AND LibSndFile_INCLUDE_DIR)
else (LibSndFile_LIBRARY)

	set(CANDIDATE_LIB_DIR
		/usr/lib
		/usr/local/lib
		/opt/local/lib
		/sw/lib
		/usr/lib/x86_64-linux-gnu
	)

	set(CANDIDATE_INC_DIR
		/usr/include
		/usr/local/include
	)

	# find_path(LibSndFile_INCLUDE_DIR LibSndFile.h ${CANDIDATE_INC_DIR})
	find_library(LibSndFile_LIBRARY sndfile ${CANDIDATE_LIB_DIR})

	# status output
	include(FindPackageHandleStandardArgs)

	find_package_handle_standard_args(LibSndFile
		DEFAULT_MSG
		LibSndFile_LIBRARY
		# LibSndFile_INCLUDE_DIR
	)
	mark_as_advanced(
		# LibSndFile_INCLUDE_DIR
		LibSndFile_LIBRARY
	)

# endif (LibSndFile_LIBRARY AND LibSndFile_INCLUDE_DIR)
endif (LibSndFile_LIBRARY)
