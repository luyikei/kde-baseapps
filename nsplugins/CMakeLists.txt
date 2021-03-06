macro_optional_find_package(GLIB2 2.0)
set_package_properties(GLIB2 PROPERTIES DESCRIPTION "Low-level core library for data structure handling, portability wrappers, etc."
                       URL "http://www.gtk.org"
                       TYPE OPTIONAL
                       PURPOSE "Glib event loop integration from Qt is required for Netscape plugins support."
                      )

if(GLIB2_FOUND)
  set(HAVE_GLIB2 1)
endif( GLIB2_FOUND)

configure_file (config-nsplugins.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-nsplugins.h )

if (X11_Xt_LIB)

  add_subdirectory( viewer ) 


  ########### next target ###############

  set(nsplugins_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/plugin_part.cpp ${CMAKE_CURRENT_SOURCE_DIR}/nspluginloader.cpp ${CMAKE_CURRENT_SOURCE_DIR}/comm/dbustypes.cpp)

  set(nsplugins_PART_SRCS
       ${nsplugins_SRCS}
    )

  qt4_add_dbus_adaptor( nsplugins_PART_SRCS org.kde.nsplugins.CallBack.xml ${CMAKE_CURRENT_SOURCE_DIR}/plugin_part.h PluginPart )

  set(nsplugins_class_xml  ${CMAKE_CURRENT_SOURCE_DIR}/viewer/org.kde.nsplugins.class.xml)
  QT4_ADD_DBUS_INTERFACE( nsplugins_PART_SRCS ${nsplugins_class_xml} nsplugins_class_interface )

  set(nsplugins_instance_xml  ${CMAKE_CURRENT_SOURCE_DIR}/viewer/org.kde.nsplugins.instance.xml)
  set_source_files_properties(${nsplugins_instance_xml} PROPERTIES INCLUDE "comm/dbustypes.h")
  QT4_ADD_DBUS_INTERFACE( nsplugins_PART_SRCS ${nsplugins_instance_xml} nsplugins_instance_interface )

  set(nsplugins_viewer_xml  ${CMAKE_CURRENT_SOURCE_DIR}/viewer/org.kde.nsplugins.viewer.xml)
  QT4_ADD_DBUS_INTERFACE( nsplugins_PART_SRCS ${nsplugins_viewer_xml} nsplugins_viewer_interface )


  kde4_add_plugin(libnsplugin ${nsplugins_PART_SRCS})

  target_link_libraries(libnsplugin ${KDE4_KPARTS_LIBS} ${QT_QTGUI_LIBRARY})

  install(TARGETS libnsplugin  DESTINATION ${PLUGIN_INSTALL_DIR} )


  ########### next target ###############

  set(kcminit_nsplugins_SRCS kcm_nsplugins.cpp plugin_paths.cpp)


  kde4_add_plugin(kcminit_nsplugins WITH_PREFIX  ${kcminit_nsplugins_SRCS})

  target_link_libraries(kcminit_nsplugins ${KDE4_KDECORE_LIBS} )

  install(TARGETS kcminit_nsplugins  DESTINATION ${PLUGIN_INSTALL_DIR} )


  ########### nspluginscan ###############

  set(nspluginscan_SRCS pluginscan.cpp plugin_paths.cpp mimetypewriter.cpp)

  kde4_add_executable(nspluginscan ${nspluginscan_SRCS})

  target_link_libraries(nspluginscan  ${KDE4_KIO_LIBS} ${X11_Xt_LIB})

  install(TARGETS nspluginscan ${INSTALL_TARGETS_DEFAULT_ARGS})

  ########### install files ###############

  install( FILES khtml_plugins.desktop  DESTINATION  ${SERVICES_INSTALL_DIR} )
  install( FILES nspluginpart.rc  DESTINATION  ${DATA_INSTALL_DIR}/nsplugin )
  install( FILES org.kde.nsplugins.CallBack.xml DESTINATION ${DBUS_INTERFACES_INSTALL_DIR} )

  add_subdirectory( test )

else (X11_Xt_LIB)

  message(STATUS "libXt not found - browser plugin support disabled")

endif (X11_Xt_LIB)
