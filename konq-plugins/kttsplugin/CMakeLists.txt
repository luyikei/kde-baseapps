########### khtmlkttsdplugin ###############

include(MacroOptionalDependPackage)

set(khtmlkttsdplugin_PART_SRCS khtmlkttsd.cpp )

qt4_add_dbus_interfaces(khtmlkttsdplugin_PART_SRCS ${KDE4_DBUS_INTERFACES_DIR}/org.kde.KSpeech.xml)

kde4_add_plugin(khtmlkttsdplugin ${khtmlkttsdplugin_PART_SRCS})

target_link_libraries(khtmlkttsdplugin  ${KDE4_KPARTS_LIBS} )

install(TARGETS khtmlkttsdplugin  DESTINATION ${PLUGIN_INSTALL_DIR} )


########### install files ###############

install( FILES khtmlkttsd.rc khtmlkttsd.desktop  DESTINATION  ${DATA_INSTALL_DIR}/khtml/kpartplugins )
install( FILES khtmlkttsd.rc khtmlkttsd.desktop  DESTINATION  ${DATA_INSTALL_DIR}/kwebkitpart/kpartplugins )

