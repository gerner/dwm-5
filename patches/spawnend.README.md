ADD SPAWNED WINDOWS TO END OF CLIENT LIST
=========================================

Description
-----------

This patch attaches newly spawned windows to the end of the client list, rather than the beginning. Newly spawned windows still get focus.

This helps preserve the ordering of clients (e.g. for use with focusbyindex patch).

Configuration
-------------

Download the patch and apply it according to the [general instructions](http://dwm.suckless.org/patches/).

It'll just work :)

Downloads
---------
* [dwm-5.9-spawnend.diff](dwm-5.9-spawnend.diff)

