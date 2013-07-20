FIND_PATH ( ZEROMQ_INCLUDE_DIR NAMES zmq.h PATHS /usr/include/ /usr/local/include/ )
FIND_LIBRARY ( ZEROMQ_LIBRARY NAMES zmq PATHS /usr/lib /usr/local/lib )


IF ( ZEROMQ_INCLUDE_DIR AND ZEROMQ_LIBRARY )
    SET ( ZEROMQ_FOUND TRUE )
ENDIF (  )
 
 
IF ( ZEROMQ_FOUND )
    MESSAGE ( STATUS "Found ZeroMQ headers in ${ZEROMQ_INCLUDE_DIR}" )
    MESSAGE ( STATUS "Found ZeroMQ library: ${ZEROMQ_LIBRARY}" )
ELSE (  )
    IF ( ZEROMQ_FIND_REQUIRED )
        MESSAGE ( FATAL_ERROR "Could not find ZeroMQ" )
    ENDIF (  )
ENDIF (  )


