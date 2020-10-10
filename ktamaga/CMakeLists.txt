include_directories (
    ${KDE1_INCLUDE_DIR}
    src
)

qt1_wrap_cpp(MOC_FILES
    conf.h confData.h ktamaga.h tlcd.h
)

add_executable(ktamaga
    conf.cpp confData.cpp ktamaga.cpp ktamagasched.cpp ktamagastat.cpp main.cpp
    tamdata.cpp tlcd.cpp
    ${MOC_FILES}
)

target_link_libraries(ktamaga
    ${KDE1_KDECORE}
    ${KDE1_KDEUI}
    Qt::Qt1
    X11::X11
)

install_icon(ktamaga.xpm)
install(FILES ktamaga.kdelnk DESTINATION ${KDE1_APPSDIR}/Games/)

# Generates the .dat files
add_executable(convert convert.cpp tamdata.cpp)
target_link_libraries(convert Qt::Qt1 X11::X11)

add_subdirectory(data)

install(FILES
    doc/en/configure.html
    doc/en/index-1.html
    doc/en/index-2.html
    doc/en/index-3.html
    doc/en/index-4.html
    doc/en/index-5.html
    doc/en/index.html
    doc/en/alltamag.png
    doc/en/iattent.png
    doc/en/ieat.png
    doc/en/ienject.png
    doc/en/ilight.png
    doc/en/interface1.png
    doc/en/iplay.png
    doc/en/istatus.png
    doc/en/iteach.png
    doc/en/itoile.png
    doc/en/tchart.png
    DESTINATION ${KDE1_HTMLDIR}/en/ktamaga )
