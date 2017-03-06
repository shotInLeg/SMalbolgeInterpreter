#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cmath>

#include <cstdio>
#include <cctype>
#include <string.h>

using namespace std;


const string cryptFrom = "+b(29e*j1VMEKLyC})8&m#~W>qxdRp0wkrUo[D7,XTcA\"lI"
                         ".v%{gJh4G\\-=O@5`_3i<?Z';FNQuY]szf$!BS/|t:Pn6^Ha";

const string cryptTo = "5z]&gqtyfr$(we4{WP)H-Zn,[%\\3dL+Q;>U!pJS72FhOA1C"
                       "B6v^=I_0/8|jsb9m<.TVac`uY*MK'X~xDl}REokN:#?G\"i@";

unsigned short crazy( unsigned short x, unsigned short y );
void processor(vector<unsigned short>& memory);
int readToRAM(vector<unsigned short>& memory, const string& input );

int main()
{
    vector<unsigned short> memory(59049); //RAM

    string input = "";
    getline(cin, input);

    readToRAM( memory, input );
    processor( memory );

    cout << endl;
    return 0;
}

int readToRAM( vector<unsigned short>& memory, const string& input )
{
    unsigned short i = 0;
    for( unsigned c = 0; c < input.size(); c++ )
    {
        int symbol = input[c];

        if ( symbol > 32 && symbol < 127 )
        {
            if ( strchr( "ji*p</vo", cryptFrom[( symbol - 33 + i ) % 94] ) == NULL )
            {
                cerr << "invalid character in source file" << endl;
                //continue;
                exit( 1 );
            }

            if ( i == 59049 )
            {
                cerr << "input file too long" << endl;
                exit( 1 );
            }

            memory[i] = (unsigned short)symbol;
            i++;
        }
    }

    for( ; i < 59049; i++ )
    {
        memory[i] = crazy( memory.at(i - 1), memory.at(i - 2) );
    }

    return 0;
}

void processor( vector<unsigned short>& memory )
{
    //Register a, c, d
    unsigned short a = 0;
    unsigned short c = 0;
    unsigned short d = 0;

    while( true )
    {
        if ( memory.at(c) > 126  || memory.at(c) < 33 )
            continue;

        switch ( cryptFrom[( memory.at(c) - 33 + c ) % 94] )
        {
          case 'j':
            d = memory.at(d);
            break;

          case 'i':
            c = memory.at(d);
            break;

          case '*':
            a = memory[d] = memory.at(d) / 3 + memory.at(d) % 3 * 19683;
            break;

          case 'p':
            a = memory[d] = crazy( a, memory.at(d) );
            break;

          case '<':
            cout << (char)a;
            break;

          case '/':
            a = getc( stdin );
            break;

          case 'v':
            return;
        }

        memory[c] = cryptTo[ memory.at(c) - 33 ];

        if ( c == 59048 )
            c = 0;
        else
            c++;

        if ( d == 59048 )
            d = 0;
        else
            d++;
    }
}

unsigned short crazy( unsigned short x, unsigned short y )
{
    unsigned short i = 0;
    unsigned short j = 0;
    unsigned short p9[5] = { 1, 9, 81, 729, 6561 };
    unsigned short o[9][9] =
    {
        { 4, 3, 3, 1, 0, 0, 1, 0, 0 },
        { 4, 3, 5, 1, 0, 2, 1, 0, 2 },
        { 5, 5, 4, 2, 2, 1, 2, 2, 1 },
        { 4, 3, 3, 1, 0, 0, 7, 6, 6 },
        { 4, 3, 5, 1, 0, 2, 7, 6, 8 },
        { 5, 5, 4, 2, 2, 1, 8, 8, 7 },
        { 7, 6, 6, 7, 6, 6, 4, 3, 3 },
        { 7, 6, 8, 7, 6, 8, 4, 3, 5 },
        { 8, 8, 7, 8, 8, 7, 5, 5, 4 },
    };

    for ( j = 0; j < 5; j++ )
    {
        i += o[y / p9[j] % 9][x / p9[j] % 9] * p9[j];
    }

    return i;
}


