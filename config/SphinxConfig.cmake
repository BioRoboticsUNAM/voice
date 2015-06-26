# - Try to find Sphinx
# Once done this will define
#
# SphinxBase_FOUND          - set to true if SphinxBase was found
# SphinxBase_LIBRARIES      - link these to use SphinxBase
# SphinxBase_INCLUDE_DIR    - path to SphinxBase header files
#
# PocketSphinx_FOUND         - set to true if SphinxBase was found
# PocketSphinx_LIBRARIES     - link these to use SphinxBase
# PocketSphinx_INCLUDE_DIR   - path to SphinxBase header files

if (SphinxBase_LIBRARIES AND SphinxBase_INCLUDE_DIR AND PocketSphinx_LIBRARIES AND PocketSphinx_INCLUDE_DIR)
	# in cache already
	set(SphinxBase_FOUND TRUE)
	set(PocketSphinx_FOUND TRUE)
	message(STATUS "Found SphinxBase at: ${SphinxBase_LIBRARIES}")
	message(STATUS "Found PocketSphinx at: ${PocketSphinx_LIBRARIES}")
else (SphinxBase_LIBRARIES AND SphinxBase_INCLUDE_DIR AND PocketSphinx_LIBRARIES AND PocketSphinx_INCLUDE_DIR)

	set(SPHINX_BASE_CANDIDATE_LIB_DIR
		/usr/lib
		/usr/local/lib
		/usr/lib/SphinxBase
		/usr/local/lib/SphinxBase
		/usr/local/SphinxBase/lib
		/opt/SphinxBase/lib
	)

	set(POCKET_SPHINX_CANDIDATE_LIB_DIR
		/usr/lib
		/usr/local/lib
		/usr/lib/PocketSphinx
		/usr/local/lib/PocketSphinx
		/usr/local/PocketSphinx/lib
		/opt/PocketSphinx/lib
	)

	set(SPHINX_BASE_CANDIDATE_INC_DIR
		/usr/include
		/usr/include/sphinxbase
		/usr/local/include
		/usr/local/include/sphinxbase
		/usr/local/sphinxbase/include
		/opt/sphinxbase/include
	)

	set(POCKET_SPHINX_CANDIDATE_INC_DIR
		/usr/include
		/usr/include/pocketsphinx
		/usr/local/include
		/usr/local/include/pocketsphinx
		/usr/local/PocketSphinx/include
		/opt/PocketSphinx/include
	)

	find_path(SphinxBase_INCLUDE_DIR sphinxbase_export.h ${SPHINX_BASE_CANDIDATE_INC_DIR})
	find_library(SphinxBase_LIBRARIES sphinxbase ${SPHINX_BASE_CANDIDATE_LIB_DIR})

	find_path(PocketSphinx_INCLUDE_DIR pocketsphinx.h ${POCKET_SPHINX_CANDIDATE_INC_DIR})
	find_library(PocketSphinx_LIBRARIES pocketsphinx ${POCKET_SPHINX_CANDIDATE_LIB_DIR})

	# status output
	include(FindPackageHandleStandardArgs)

	find_package_handle_standard_args(SphinxBase
		DEFAULT_MSG
		SphinxBase_LIBRARIES
		SphinxBase_INCLUDE_DIR
	)
	mark_as_advanced(
		SphinxBase_INCLUDE_DIR
		SphinxBase_LIBRARIES
	)

	find_package_handle_standard_args(PocketSphinx
		DEFAULT_MSG
		PocketSphinx_LIBRARIES
		PocketSphinx_INCLUDE_DIR
	)
	mark_as_advanced(
		PocketSphinx_INCLUDE_DIR
		PocketSphinx_LIBRARIES
	)

endif (SphinxBase_LIBRARIES AND SphinxBase_INCLUDE_DIR AND PocketSphinx_LIBRARIES AND PocketSphinx_INCLUDE_DIR)