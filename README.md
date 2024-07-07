## MTag ##
The Music Tag Manipulator, [MTag](https://github.com/hildigerr/mtag), is a music file tag manipulator by [Hildigerr Vergaray](https://github.com/hildigerr) using [TagLib](http://taglib.org). It was designed to be lightweight and composable.

### Options ###
`Useage: mtag [-hvL] | [-l[separator]] [-n number] [-t title] [-a artist] [-A album] [-y year] [-g genre] [-c comment] [-x key] filename`
 - -h, --help Displays a help message.
 - -v, --version Displays version information.
 - -L, --list-genres Displays the canonical genres list.
 - -l, --list Lists the file's tags as key value pairs.
 - -n, --track Set the file's track number tag
 - -t, --title Set the file's title tag
 - -a, --artist Set the file's artist tag
 - -A, --album Set the file's album tag
 - -y, --year Set the file's year tag
 - -g, --genre Set the file's genre tag
 - -c, --comment Set the file's comment tag
 - -x, --remove Remove an element with the specified key from the tag.


#### list separator ####
You can override the default tag listing separator (': '). For example `-l=` or `--list==` will separate the key value pairs with the `=` character.

### Return Status ###
 - 0 STATUS_OK
 - 1 STATUS_OPTION_INVALID
 - 2 STATUS_FILENAME_EMPTY
 - 3 STATUS_FILE_INVALID
 - 4 STATUS_TAG_EMPTY
 - 5 STATUS_FILE_NOT_SAVED
