win32 {
    QMAKE_POST_LINK += $$quote( $$PWD/../common/local_deploy.cmd $$PWD/metascheme*.xml ./ & )
    debug {
        QMAKE_POST_LINK += $$quote( $$PWD/../common/local_deploy.cmd $$PWD/metascheme*.xml ./debug & )
    }

    release {
        QMAKE_POST_LINK += $$quote( $$PWD/../common/local_deploy.cmd $$PWD/metascheme*.xml ./release & )
    }
}

unix {
    QMAKE_POST_LINK += $$quote( cp $$PWD/../common/metascheme*.xml ./ & )
}
