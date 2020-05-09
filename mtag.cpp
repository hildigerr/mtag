#include <stdio.h>
#include <getopt.h>

#include <taglib/fileref.h>
#include <taglib/tfile.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>

/* Return Status */
#define STATUS_OK              0
#define STATUS_OPTION_INVALID  1
#define STATUS_FILENAME_EMPTY  2
#define STATUS_FILE_INVALID    3
#define STATUS_TAG_EMPTY       4
#define STATUS_FILE_NOT_SAVED  5

const char * version = "0.0.2";

int main( int argc, char * argv[] )
{
    int i, opt, opqt = 7, status = STATUS_OK;
    const char * sep = NULL,
               * title = NULL,
               * artist = NULL,
               * album = NULL,
               * genre = NULL;
    const char * opts = "hvl::t:a:A:g:";
    const char * usage[opqt+1] = {
        "[-hv] | [-l[separator]] [-t title] [-a artist] [-A album] [-g genre] filename",
        "Display this help message and exit",
        "Display version information and exit",
        "List all the file's tags",
        "Set the file's title tag",
        "Set the file's artist tag",
        "Set the file's album tag",
        "Set the file's genre tag"
    };
    struct option options[opqt] = {
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' },
        { "list", optional_argument, NULL, 'l' },
        { "title", required_argument, NULL, 't' },
        { "artist", required_argument, NULL, 'a' },
        { "album", required_argument, NULL, 'A' },
        { "genre", required_argument, NULL, 'g' }
    };

    while( (opt = getopt_long( argc, argv, opts, options, &i )) != -1 ) {
        switch( opt ) {
            case 't': title = optarg; break;
            case 'a': artist = optarg; break;
            case 'A': album = optarg; break;
            case 'g': genre = optarg; break;
            case 'l':
                if( optarg ) sep = optarg;
                else sep = ": ";
                break;
            case '?':
                status = STATUS_OPTION_INVALID;
            case 'h':
                printf( "  Usage: %s %s\n", argv[0], usage[0] );
                for( i = 0; i < opqt; i++ )
                    printf( "    -%c, --%-8s%s\n", options[i].val, options[i].name, usage[i+1] );
                return status;
            case 'v':
                printf( "%s %s\n", argv[0], version );
                return status;
        }/* End opt Switch */
    }/* End While */

    if( optind >= argc ) return STATUS_FILENAME_EMPTY;

    TagLib::FileRef fh(argv[optind]);
    if( fh.isNull() ) return STATUS_FILE_INVALID;
    
    TagLib::File * file = fh.file();
    if( !(file && file->isValid()) ) return STATUS_FILE_INVALID;

    TagLib::Tag * tag = file->tag();
    if( !tag ) return STATUS_FILE_INVALID;

    if( title ) tag->setTitle( title );
    if( artist ) tag->setArtist( artist );
    if( album ) tag->setAlbum( album );
    if( genre ) tag->setGenre( genre );

    if( title || artist || album || genre )
        if( !file->save() ) return STATUS_FILE_NOT_SAVED;

    if( tag->isEmpty() ) status = STATUS_TAG_EMPTY;

    if( sep ) { /* implies --list */
        TagLib::PropertyMap map = file->properties();
        TagLib::PropertyMap::ConstIterator each;
        TagLib::StringList::ConstIterator element;
        for( each = map.begin(); each != map.end(); each++ )
            for( element = each->second.begin(); element != each->second.end(); element++ )
                printf( "%s%s%s\n", each->first.toCString(), sep, element->toCString() );
    }/* End sep If */

    return status;
}/* End Main Func */
