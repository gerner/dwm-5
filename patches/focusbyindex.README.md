FOCUS BY VISIBLE CLIENT LIST INDEX
==================================

Description
-----------

This patch enables focusing a window by its position in the visible client list. This can be used to create new key bindings to focus a particular window (rather than just focusing the next window).

Configuration
-------------

Download the patch and apply it according to the [general instructions](http://dwm.suckless.org/patches/).

Add some key bindings to your config.h.

### Example

```c
static Key keys[] = {
...
    { Mod4Mask,                     XK_1,      focusvisible,   {.i = 0 } },
    { Mod4Mask,                     XK_2,      focusvisible,   {.i = 1 } },
    { Mod4Mask,                     XK_3,      focusvisible,   {.i = 2 } },
    { Mod4Mask,                     XK_4,      focusvisible,   {.i = 3 } },
    { Mod4Mask,                     XK_5,      focusvisible,   {.i = 4 } },
    { Mod4Mask,                     XK_6,      focusvisible,   {.i = 5 } },
    { Mod4Mask,                     XK_7,      focusvisible,   {.i = 6 } },
    { Mod4Mask,                     XK_8,      focusvisible,   {.i = 7 } },
    { Mod4Mask,                     XK_9,      focusvisible,   {.i = 8 } },
    { MODKEY,                       XK_Left,   focusvisible,   {.i = 0 } },
    { MODKEY,                       XK_Right,  focusvisible,   {.i = 1 } },
...
```

The above lines let you jump to a numbered client or immediately to the master window or first slave window.


Downloads
---------
* [dwm-5.9-focusbyindex.diff](dwm-5.9-focusbyindex.diff)

