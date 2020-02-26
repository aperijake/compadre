IF (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  TRY_COMPILE(KOKKOSKERNELS_HAS_MKL_ARG
    ${KOKKOSKERNELS_TOP_BUILD_DIR}/tpl_tests
    ${KOKKOSKERNELS_TOP_SOURCE_DIR}/cmake/compile_tests/mkl.cpp
    LINK_LIBRARIES -mkl
    COMPILE_DEFINITIONS -mkl)
  KOKKOSKERNELS_CREATE_IMPORTED_TPL(MKL INTERFACE COMPILE_OPTIONS -mkl LINK_OPTIONS -mkl)
  INCLUDE(FindPackageHandleStandardArgs)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(MKL DEFAULT_MSG KOKKOSKERNELS_HAS_MKL_ARG)
ELSE()
  MESSAGE(FATAL_ERROR "No support currently for MKL without using the Intel compiler")
ENDIF()

