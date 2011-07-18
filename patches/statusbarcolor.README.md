COLORED STATUS TEXT
===================

Description
-----------

This patch enables colors in the statusbar (and adds a method to draw colored text in general). The colors are defined in an array in config.h and are referenced by bytes which index into that array.

Configuragion
-------------

Download the patch and apply it according to the [general instructions](http://dwm.suckless.org/patches/).

Add lines to your config.h to set up your colors array (see the example below). When a status line is drawn it will interpret single bytes that could index into your colors array as setting the colors for the next set of text. The bytes are not drawn (and not replaced with spaces). 

This patch also contains an update to textnw to ignore these non-printing color setting codes when calculating text width. There's also a change to drawtext to not print the left padding (see the interplay between drawpaddedtext and drawtext).

### Example

Try adding the following to config.h

```c
#define NUMCOLORS         5
static const char colors[NUMCOLORS][ColLast][8] = {
  // border   foreground background
  { "#333333", "#aaaaaa", "#000000" },  // normal
  { "#000088", "#00ff00", "#000000" },  // good
  { "#ff0000", "#ffff00", "#000000" },  // warning
  { "#ff0000", "#ff0000", "#000000" },  // error
  { "#333333", "#aaaaaa", "#000000" },  // back to normal (for endpoints that are regular)
  // add more here
};
```

now try the following:

```bash
$ xsetroot -name $( echo -e "\x01this is normaltext \x02this is good text \x03this is warning text \x04this is warning text" )
```

Notice that we need to enable byte code interpretation with echo. Also notice that the color array is one-indexed (since a zero byte will null terminate the string).

See how [I set my status bar](https://github.com/gerner/environment/blob/master/bin/statusbar).

Downloads
---------
* [dwm-5.9-statusbarcolor.diff](dwm-5.9-statusbarcolor.diff)

Thanks
------

A big thanks to the [statuscolors](http://dwm.suckless.org/patches/statuscolors) patch from which I drew much of the drawcoloredtext method.

