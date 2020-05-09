#include <stdio.h>
#include <getopt.h>

/* Return Status */
#define STATUS_OK              0
#define STATUS_OPTION_INVALID  1

const char * version = "0.0.0";

int main( int argc, char * argv[] )
{
    int i, opt, opqt = 2, status = STATUS_OK;
    const char * opts = "hv";
    const char * usage[opqt+1] = {
        "[-hv] filename",
        "Display this help message and exit",
        "Display version information and exit"
    };
    struct option options[opqt] = {
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' }
    };

    while( (opt = getopt_long( argc, argv, opts, options, &i )) != -1 ) {
        switch( opt ) {
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

    return status;
}/* End Main Func */
