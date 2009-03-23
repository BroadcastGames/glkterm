/* gtw_pair.h: The pair window header
        for GlkTerm, curses.h implementation of the Glk API.
    Designed by Andrew Plotkin <erkyrath@netcom.com>
    http://www.edoc.com/zarf/glk/index.html
*/

typedef struct window_pair_struct {
    window_t *owner;

    window_t *child1, *child2; 
    int splitpos; /* The split center. To be picky, this is the position
        of the top of the border, or the top of the bottom window if the
        border is zero-width. (If vertical is true, rotate this comment
        90 degrees.) */
    int splitwidth; /* The width of the border. Zero or one. */
    
    /* split info... */
    uint32 dir; /* winmethod_Left, Right, Above, or Below */
    int vertical, backward; /* flags */
    uint32 division; /* winmethod_Fixed or winmethod_Proportional */
    window_t *key; /* NULL or a leaf-descendant (not a Pair) */
    int keydamage; /* used as scratch space in window closing */
    uint32 size; /* size value */
    
} window_pair_t;

extern window_pair_t *win_pair_create(window_t *win, uint32 method, 
    window_t *key, uint32 size);
extern void win_pair_destroy(window_pair_t *dwin);
extern void win_pair_rearrange(window_t *win, grect_t *box);
extern void win_pair_redraw(window_t *win);
