win32 {
    debug {
        QMAKE_POST_LINK += $$quote( xcopy /Y $$PWD/../Common/metascheme.xml ./debug & )
    }

    release {
        QMAKE_POST_LINK += $$quote( xcopy /Y $$PWD/../Common/metascheme.xml ./release & )
    }
}

unix {
    QMAKE_POST_LINK += $$quote( cp $$PWD/../Common/metascheme.xml ./ & )
}
