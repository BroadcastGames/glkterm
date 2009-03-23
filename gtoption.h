/* gtoption.h: Options header file
        for GlkTerm, curses.h implementation of the Glk API.
    Designed by Andrew Plotkin <erkyrath@netcom.com>
    http://www.edoc.com/zarf/glk/index.html
*/

#ifndef GTOPTION_H
#define GTOPTION_H

/* This is the only GlkTerm source file you should need to edit
    in order to compile the thing. Well, unless there's something
    funny about your OS -- which is probably inevitable. See the
    readme file for a list of OSes which GlkTerm is known to
    compile under, and what changes are appropriate.
*/

/* Options: */

#define LIBRARY_VERSION "0.1 alpha"
#define LIBRARY_PORT "Generic"

/* If you change this code substantially, you should change the
    LIBRARY_PORT definition to something which explains what the
    heck you did. (For example, if you release an Amiga port --
    or whatever -- and jigger the display code to make it work,
    you could change LIBRARY_PORT to "Amiga port".)
   The LIBRARY_VERSION definition should generally stay the same; 
    it tracks the version of the original GlkTerm code that I
    support. If you want to distinguish different versions of a
    port, you could change LIBRARY_PORT to "Amiga port 1.3".
   If you want to make major changes to the internals of the
    GlkTerm library, add a note to LIBRARY_VERSION, or contact
    me so that I can incorporate your changes into the original
    source.
*/  

#define OPT_WINCHANGED_SIGNAL

/* OPT_WINCHANGED_SIGNAL should be defined if your OS sends a
    SIGWINCH signal whenever the window size changes. If this
    is defined, GlkTerm will call signal() to set a handler for
    SIGWINCH, and rearrange the screen properly when the window
    is resized. If this is not defined, GlkTerm will think that
    the window size is fixed, and not watch for changes.
   This should generally be defined; comment it out only if your
    OS does not define signal() or SIGWINCH.
   OPT_WINCHANGED_SIGNAL will be ignored unless OPT_TIMED_INPUT
    is also defined. This is because GlkTerm has to check
    periodically to see if it's time to rearrange the screen.
*/

#define OPT_TIMED_INPUT

/* OPT_TIMED_INPUT should be defined if your OS allows timed
    input using the halfdelay() curses library call. If this is
    defined, GlkTerm will support timed input. If not, it won't
    (and the -precise command-line option will also be removed.)
   Note that GlkTerm implements time-checking using both the
    halfdelay() call in curses.h, and the gettimeofday() call in
    sys/time.h. If your OS does not support gettimeofday(), you
    will have to comment this option out, unless you want to hack
    gtevent.c to use a different time API.
*/

/* #define NO_MEMMOVE */

/* NO_MEMMOVE should be defined if your standard library doesn't
    have a memmove() function. If this is defined, a simple 
    memmove() will be defined in gtmisc.c.
*/

#endif /* GTOPTION_H */

