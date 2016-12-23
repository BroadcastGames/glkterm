enum FACES { MONOR, MONOB, MONOI, MONOZ, PROPR, PROPB, PROPI, PROPZ };
enum TYPES { MONOF, PROPF };
enum STYLES { FONTR, FONTB, FONTI, FONTZ };

#ifndef A_H_STYLE_S
#define A_H_STYLE_S
struct style_s
{
    int font;
    unsigned char bg[3];   /* background color */
    unsigned char fg[3];   /* foreground color */
    int fgint;             /* foreground color raw 24-bit int from Glk */
    int reverse;           /* reverse colors flag, inverse text */
};

typedef struct style_s style_t;
#endif

extern style_t gli_tstyles[style_NUMSTYLES];
extern style_t gli_gstyles[style_NUMSTYLES];

extern style_t gli_tstyles_def[style_NUMSTYLES];
extern style_t gli_gstyles_def[style_NUMSTYLES];


extern int gli_conf_stylehint;


extern unsigned char gli_window_color[3];
extern unsigned char gli_caret_color[3];
extern unsigned char gli_more_color[3];


extern int stylehint_set_call_count;
extern int stylehint_clear_call_count;
