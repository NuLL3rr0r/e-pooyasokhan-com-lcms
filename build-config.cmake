# MYLIB_LIB_TYPE
#   * STATIC
#   * SHARED
SET ( MYLIB_LIB_TYPE SHARED )

SET ( BUILD_EPS_SERVER "YES" )
SET ( BUILD_EPS_ADMIN "YES" )
SET ( BUILD_EPS_TEACHER "YES" )
SET ( BUILD_EPS_STUDENT "YES" )

SET ( MYLIB_BIN_NAME "mylib" )
SET ( EPS_SERVER_BIN_NAME "eps-server" )
SET ( EPS_ADMIN_BIN_NAME "eps-admin" )
SET ( EPS_TEACHER_BIN_NAME "eps-teacher" )
SET ( EPS_STUDENT_BIN_NAME "eps-student" )


# CMAKE_BUILD_TYPE
#   * None
#   * Debug
#   * Release
#   * RelWithDebInfo
#   * MinSizeRel
#   * GCCMinSizeRel
#   * GCCMaxSpeedRel
#   * GCCNativeMinSizeRel
#   * GCCNativeMaxSpeedRel
IF( NOT CMAKE_BUILD_TYPE )
    SET ( CMAKE_BUILD_TYPE "GCCNativeMaxSpeedRel" CACHE STRING "" FORCE )
ENDIF(  )

# Reduce executable size by using GNU strip (GNU Binutils)
SET ( GCC_STRIP_EXECUTABLE "YES" )


