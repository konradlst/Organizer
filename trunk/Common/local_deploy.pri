win32 {
    debug {
        QMAKE_POST_LINK += $$quote( $$PWD/../Common/local_deploy.cmd $$PWD/metascheme*.xml ./debug & )
    }

    release {
        QMAKE_POST_LINK += $$quote( $$PWD/../Common/local_deploy.cmd $$PWD/metascheme*.xml ./release & )
    }
}

unix {
    QMAKE_POST_LINK += $$quote( cp $$PWD/../Common/metascheme*.xml ./ & )
}
