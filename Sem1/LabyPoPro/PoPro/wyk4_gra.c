int main ( void )
{
    const int MAX_LICZBA = 10;
    srand ( time( NULL ) );
    int los = rand() % MAX_LICZBA +1;
    int odp = 0;
    int liczbProb = 0;
    do {
        printf ( "Pod. liczbe od 1 do %d:(0 konczy gre)",MAX_LICZBA );
        scanf( "%d", &odp );
        if( 0 == odp )
            break;
        ++liczbProb;
    } 
    while ( odp != los );
    if( odp == los )
        printf( "Bylo %d prob\n", liczbProb );
}