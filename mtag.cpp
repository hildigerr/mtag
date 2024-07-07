#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>

#include <taglib/fileref.h>
#include <taglib/tfile.h>
#include <taglib/tag.h>
#include <taglib/tpropertymap.h>
#include <taglib/id3v1genres.h>

/* Return Status */
#define STATUS_OK              0
#define STATUS_OPTION_INVALID  1
#define STATUS_FILENAME_EMPTY  2
#define STATUS_FILE_INVALID    3
#define STATUS_TAG_EMPTY       4
#define STATUS_FILE_NOT_SAVED  5

const char * copyright = "(c) 2020 Hildigerr Vergaray";
const char * version = "0.1.5";

int main( int argc, char * argv[] )
{
    int i, opt, opqt = 12, status = STATUS_OK;
    char * endptr = NULL;
    const char * sep = NULL,
               * track = NULL,
               * title = NULL,
               * artist = NULL,
               * album = NULL,
               * year = NULL,
               * genre = NULL,
               * comment = NULL,
               * delete_me = NULL;
    const char * opts = "hvLl::n:t:a:A:y:g:c:x:";
    const char * usage[opqt+1] = {
        "[-hvL] | [-l[separator]] [-n number] [-t title] [-a artist] [-A album] [-y year] [-g genre] [-c comment] [-x key] filename",
        "Display this help message and exit",
        "Display version information and exit",
        "Display the ordered list of canonical ID3v1 and Winamp genres",
        "List all the file's tags",
        "Set the file's track number tag",
        "Set the file's title tag",
        "Set the file's artist tag",
        "Set the file's album tag",
        "Set the file's year tag",
        "Set the file's genre tag",
        "Set the file's comment tag",
        "Remove an element from the tag"
    };
    struct option options[opqt] = {
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' },
        { "list-genres", no_argument, NULL, 'L' },
        { "list", optional_argument, NULL, 'l' },
        { "track", required_argument, NULL, 'n' },
        { "title", required_argument, NULL, 't' },
        { "artist", required_argument, NULL, 'a' },
        { "album", required_argument, NULL, 'A' },
        { "year", required_argument, NULL, 'y' },
        { "genre", required_argument, NULL, 'g' },
        { "comment", required_argument, NULL, 'c' },
        { "remove", required_argument, NULL, 'x' }
    };

    while( (opt = getopt_long( argc, argv, opts, options, &i )) != -1 ) {
        switch( opt ) {
            case 'n': track = optarg; break;
            case 't': title = optarg; break;
            case 'a': artist = optarg; break;
            case 'A': album = optarg; break;
            case 'g': genre = optarg; break;
            case 'y': year = optarg; break;
            case 'c': comment = optarg; break;
            case 'x': delete_me = optarg; break;
            case 'l':
                if( optarg ) sep = optarg;
                else sep = ": ";
                break;
            case '?':
                status = STATUS_OPTION_INVALID;
            case 'h':
                printf( "  Usage: %s %s\n", argv[0], usage[0] );
                for( i = 0; i < opqt; i++ )
                    printf( "    -%c, --%-12s%s\n", options[i].val, options[i].name, usage[i+1] );
                return status;
            case 'v':
                printf( "%s %s\n", argv[0], version );
                printf( "Copyright %s\nLicnese: %s\n", copyright, "Artistic-2.0" );
                return status;
            case 'L': {
                TagLib::StringList genres = TagLib::ID3v1::genreList();
                TagLib::StringList::ConstIterator each;
                for( each = genres.begin(); each != genres.end(); each++ )
                    printf( "%s\n", each->toCString() );
                return status;
            }/* End L Case */
        }/* End opt Switch */
    }/* End While */

    if( optind >= argc ) return STATUS_FILENAME_EMPTY;

    TagLib::FileRef fh(argv[optind]);
    if( fh.isNull() ) return STATUS_FILE_INVALID;

    TagLib::File * file = fh.file();
    if( !(file && file->isValid()) ) return STATUS_FILE_INVALID;

    TagLib::Tag * tag = file->tag();
    if( !tag ) return STATUS_FILE_INVALID;

    if( track ) {
        errno = 0;
        status = strtol( track, &endptr, 10);
        if(( errno )||( endptr == track )) return STATUS_OPTION_INVALID;
        tag->setTrack( status );
        status = STATUS_OK;
    }/* End track If */
    if( title ) tag->setTitle( title );
    if( artist ) tag->setArtist( artist );
    if( album ) tag->setAlbum( album );
    if( year ) {
        errno = 0;
        status = strtol( year, &endptr, 10);
        if(( errno )||( endptr == year )) return STATUS_OPTION_INVALID;
        tag->setYear( status );
        status = STATUS_OK;
    }/* End year If */
    if( genre ) tag->setGenre( genre );
    if( comment ) tag->setComment( comment );

    if( delete_me ) {
        TagLib::PropertyMap map = file->properties();
        map.erase( delete_me );
        file->setProperties(map);
    }/* End delete_me If */

    if( track || title || artist || album || year || genre || comment || delete_me )
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
