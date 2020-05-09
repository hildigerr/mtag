## MTag ##
The Music Tag Manipulator, [MTag](https://github.com/hildigerr/mtag), is a [TagLib](http://taglib.org) based music file tag manipulator by [Hildigerr Vergaray](https://github.com/hildigerr). It was designed to be lightweight and composable.

### Options ###
`Useage: mtag [-hv] | [-l[separator]] filename`
 - -h, --help Displays a help message.
 - -v, --version Displays version information.
 - -l, --list Lists the file's tags as key value pairs.

#### list separator ####
You can override the default tag listing separator (': '). For example `-l=` or `--list==` will separate the key value pairs with the `=` character.

### Return Status ###
 - 0 STATUS_OK
 - 1 STATUS_OPTION_INVALID
 - 2 STATUS_FILENAME_EMPTY
 - 3 STATUS_FILE_INVALID
 - 4 STATUS_TAG_EMPTY
