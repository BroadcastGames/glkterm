/* gtstyle.c: Style formatting hints.
        for GlkTerm, curses.h implementation of the Glk API.
    Designed by Andrew Plotkin <erkyrath@eblong.com>
    http://www.eblong.com/zarf/glk/index.html
*/

#include "gtoption.h"
#include <stdio.h>
#include <wchar.h>
#include <curses.h>
#include "glk.h"
#include "glkterm.h"
#include "gtw_grid.h"

/* GarGlk code needs */
#include "garglk_minimum.h"

#include "gtw_buf.h"

/* GarGlk code needs */
#include <string.h>

/* Temporary to get exit to work */
#include <stdlib.h>


/* This version of the library borrows from GarGlk to try and accept style hints. */

static int isprop(int f)
{
    return f == PROPR || f == PROPI || f == PROPB || f == PROPZ;
}

static int isbold(int f)
{
    return f == PROPB || f == PROPZ || f == MONOB || f == MONOZ;
}

static int isitalic(int f)
{
    return f == PROPI || f == PROPZ || f == MONOI || f == MONOZ;
}

static int makefont(int p, int b, int i)
{
    if ( p && !b && !i) return PROPR;
    if ( p && !b &&  i) return PROPI;
    if ( p &&  b && !i) return PROPB;
    if ( p &&  b &&  i) return PROPZ;
    if (!p && !b && !i) return MONOR;
    if (!p && !b &&  i) return MONOI;
    if (!p &&  b && !i) return MONOB;
    if (!p &&  b &&  i) return MONOZ;
    return PROPR;
}


int stylehint_set_call_count = 0;
int stylehint_clear_call_count = 0;

void glk_stylehint_set(glui32 wintype, glui32 style, glui32 hint, glsi32 val)
{
  stylehint_set_call_count++;
    style_t *styles;
    int p, b, i;

/* TIP: close and open the storyhints window to see output */
fprintf(stderr, "stylehint_set %d %d %d %d %d\n", stylehint_set_call_count, wintype, style, hint, val);
/* this works: exit(0); */

    if (wintype == wintype_AllTypes)
    {
        glk_stylehint_set(wintype_TextGrid, style, hint, val);
        glk_stylehint_set(wintype_TextBuffer, style, hint, val);
        return;
    }

    if (wintype == wintype_TextGrid)
        styles = gli_gstyles;
    else if (wintype == wintype_TextBuffer)
        styles = gli_tstyles;
    else
        return;

    if (!gli_conf_stylehint)
        return;

    switch (hint)
    {
        case stylehint_TextColor:
            styles[style].fgint = val;
            fprintf(stderr, "stylehint_set %d fgint %d\n", stylehint_set_call_count, val);
            styles[style].fg[0] = (val >> 16) & 0xff;
            styles[style].fg[1] = (val >> 8) & 0xff;
            styles[style].fg[2] = (val) & 0xff;
            break;

        case stylehint_BackColor:
            styles[style].bg[0] = (val >> 16) & 0xff;
            styles[style].bg[1] = (val >> 8) & 0xff;
            styles[style].bg[2] = (val) & 0xff;
            break;

        case stylehint_ReverseColor:
            styles[style].reverse = (val != 0);
            break;

        case stylehint_Proportional:
            if (wintype == wintype_TextBuffer)
            {
                p = val > 0;
                b = isbold(styles[style].font);
                i = isitalic(styles[style].font);
                styles[style].font = makefont(p, b, i);
            }
            break;

        case stylehint_Weight:
            p = isprop(styles[style].font);
            b = val > 0;
            i = isitalic(styles[style].font);
            styles[style].font = makefont(p, b, i);
            break;

        case stylehint_Oblique:
            p = isprop(styles[style].font);
            b = isbold(styles[style].font);
            i = val > 0;
            styles[style].font = makefont(p, b, i);
            break;
    }

    /*
    Here is where the Glk Window background, cursor caret, and "More" scrolling prompt for the windows get set.
    */
    if (wintype == wintype_TextBuffer &&
            style == style_Normal &&
            hint == stylehint_BackColor)
    {
        memcpy(gli_window_color, styles[style].bg, 3);
    }

    if (wintype == wintype_TextBuffer &&
            style == style_Normal &&
            hint == stylehint_TextColor)
    {
        memcpy(gli_more_color, styles[style].fg, 3);
        memcpy(gli_caret_color, styles[style].fg, 3);
    }
}


void glk_stylehint_clear(glui32 wintype, glui32 style, glui32 hint)
{
  stylehint_clear_call_count++;
    style_t *styles;
    style_t *defaults;

    if (wintype == wintype_AllTypes)
    {
        glk_stylehint_clear(wintype_TextGrid, style, hint);
        glk_stylehint_clear(wintype_TextBuffer, style, hint);
        return;
    }

    if (wintype == wintype_TextGrid)
    {
        styles = gli_gstyles;
        defaults = gli_gstyles_def;
    }
    else if (wintype == wintype_TextBuffer)
    {
        styles = gli_tstyles;
        defaults = gli_tstyles_def;
    }
    else
    {
        return;
    }

    if (!gli_conf_stylehint)
        return;

    switch (hint)
    {
        case stylehint_TextColor:
            styles[style].fg[0] = defaults[style].fg[0];
            styles[style].fg[1] = defaults[style].fg[1];
            styles[style].fg[2] = defaults[style].fg[2];
            break;

        case stylehint_BackColor:
            styles[style].bg[0] = defaults[style].bg[0];
            styles[style].bg[1] = defaults[style].bg[1];
            styles[style].bg[2] = defaults[style].bg[2];
            break;

        case stylehint_ReverseColor:
            styles[style].reverse = defaults[style].reverse;
            break;

        case stylehint_Proportional:
        case stylehint_Weight:
        case stylehint_Oblique:
            styles[style].font = defaults[style].font;
            break;
    }
}


glui32 glk_style_distinguish(window_t *win, glui32 styl1, glui32 styl2)
{
    int *styleattrs;

    if (!win) {
        gli_strict_warning(L"style_distinguish: invalid ref");
        return FALSE;
    }

    if (styl1 >= style_NUMSTYLES || styl2 >= style_NUMSTYLES)
        return FALSE;

    switch (win->type) {
        case wintype_TextBuffer:
            styleattrs = win_textbuffer_styleattrs;
            break;
        case wintype_TextGrid:
            styleattrs = win_textgrid_styleattrs;
            break;
        default:
            return FALSE;
    }

    /* styleattrs is an array of chtype values, as defined in curses.h. */

    if (styleattrs[styl1] != styleattrs[styl2])
        return TRUE;

    return FALSE;
}

glui32 glk_style_measure(window_t *win, glui32 styl, glui32 hint,
    glui32 *result)
{
    int *styleattrs;
    glui32 dummy;

    if (!win) {
        gli_strict_warning(L"style_measure: invalid ref");
        return FALSE;
    }

    if (styl >= style_NUMSTYLES || hint >= stylehint_NUMHINTS)
        return FALSE;

    switch (win->type) {
        case wintype_TextBuffer:
            styleattrs = win_textbuffer_styleattrs;
            break;
        case wintype_TextGrid:
            styleattrs = win_textgrid_styleattrs;
            break;
        default:
            return FALSE;
    }

    if (!result)
        result = &dummy;

    switch (hint) {
        case stylehint_Indentation:
        case stylehint_ParaIndentation:
            *result = 0;
            return TRUE;
        case stylehint_Justification:
            *result = stylehint_just_LeftFlush;
            return TRUE;
        case stylehint_Size:
            *result = 1;
            return TRUE;
        case stylehint_Weight:
            *result = ((styleattrs[styl] & A_BOLD) != 0);
            return TRUE;
        case stylehint_Oblique:
            *result = ((styleattrs[styl] & A_UNDERLINE) != 0);
            return TRUE;
        case stylehint_Proportional:
            *result = FALSE;
            return TRUE;
    }

    return FALSE;
}
