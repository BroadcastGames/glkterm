enum FACES { MONOR, MONOB, MONOI, MONOZ, PROPR, PROPB, PROPI, PROPZ };
enum TYPES { MONOF, PROPF };
enum STYLES { FONTR, FONTB, FONTI, FONTZ };

struct style_s
{
    int font;
    unsigned char bg[3];
    unsigned char fg[3];
    int reverse;
};

typedef struct style_s style_t;


extern style_t gli_tstyles[style_NUMSTYLES];
extern style_t gli_gstyles[style_NUMSTYLES];

extern style_t gli_tstyles_def[style_NUMSTYLES];
extern style_t gli_gstyles_def[style_NUMSTYLES];


extern int gli_conf_stylehint;


extern unsigned char gli_window_color[3];
extern unsigned char gli_caret_color[3];
extern unsigned char gli_more_color[3];
