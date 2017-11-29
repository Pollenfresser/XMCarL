# Hier sind unsere Coding styles 

ALLES AUF ENGLISCH!

!!!DARAUF ACHTEN, dass sinnvolle Namen gegeben werden - kein x, y, i, ...

Golden rule: keinen code stehlen (auf Lizenz & Copyright achten)

# Funktionen
Funktionsnamen: klein mit unterstrichen
Eine Funktion hat eine Funktionalität
Funktionalität-Funktionen von Aufruf-Funktionen trennen

<b>Beispiel:</b>
void chrisy_function_macht_nichts()

# Variablen
Variablennamen: klein mit unterstrichen

<b>Beispiel:</b>
int zaehl_variable = 0;

# Struct
t_ für type zu Beginn des Typen

<b>Beispiel:</b>
typedef struct name{
        unsigned char sinnvoll_x;
        unsigned char sinnvoll_y;
} t_beispiel;    

name … Strukturtyp
{ xxx } … Strukturdefinition
t_beispiel … Strukturvariable / Variablenname


# Konstanten

Funktionsnamen: groß mit unterstrich
Enum bei nicht funktionalen Werten (zb Status: fahren 1, stehen 2, links 3, ...)

<b>Beispiel:</b>
    #define VARIABLE_KONSTANT 42




# C - File (Reihenfolge)

Erklärung was im File “passiert” -> Kommentare
Inkludieren der Headerfiles

Funktionen
- Kommentar, Erklärung was die Funktion macht
- Definition der Funktion - void chrisy_function(){ ... 
- Lokale Variablen
- Code
- Return (wenn nicht void)
Mainfunktion (Nur im Hauptprogramm)

Usage and Operating Instructions, if applicable for program files only

# H - File (Reihenfolge)

Header File Includes, in this sequence:
```
#include <stdio.h> (or <stdlib.h>)
#include <other system headers>
#include “user header files”
```

Defines and Typedefs that apply to the file as a whole, including:
enums
typedefs
constant macro defines
function macro defines

# Kommentare

<b>ReadMe File</b>
Beschreibung des gesamten Projekts
Beschreibung jedes einzelnen Files, in Gruppen von .c und .h File
Fileheader
zugehöriges Headerfile
Definierte Funktionen
Funktionsprolog
Definierte Variablen
Variablenbeschreibung

<b>Fileheader; C-File</b>
Im Fileheader ist die Funktion des Files zu beschreiben, aus dem Header soll klar hervorgehen wozu dieses File benötigt wird.
Zusätzlich ist das zugehörige Headerfile sowie alle Funktionen und Variablen aufzulisten.
Als weitere Information ist der Autor, das Erstellungsdatum und das zugehörige Projekt anzuführen.

Beispiel:
```
/*-----------------------------------------------------------------*/
/* Author:                                               */
/*                                                   */
/* Created: yyyy-mm-dd                                   */
/* Project: XMCarL                                       */
/*                                                   */
/* Diese Beschreibung dient als Beispieltext für eine            */ 
/* Filebeschreibung aus welcher klar hervorgehen soll was in        */
/* diesem File passiert und wozu dieses benötigt wird.           */
/*-----------------------------------------------------------------*/
```

<b>Funktionskommentar</b>
Im Funktionsprolog sind die Funktionen der Funktion sowie die verwendeten Variablen aufzulisten.

Beispiel:
```
/*-----------------------------------------------------------------*/
/* Name der Funktion                                    */
/* Hier wird ein Beispiel für einen Prolog aufgelistet.            */
/* beispiel_var Dient als Beispiel der Variablenauflistung.        */
/*-----------------------------------------------------------------*/
```

<b>In line Kommentare</b>
nicht zu viele - eher ins Funktionskommentar
-> keine sternchen
// Beispielkommentar


