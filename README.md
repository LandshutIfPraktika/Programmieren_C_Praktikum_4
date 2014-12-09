Praktikum_4
===========
Der Trick war in die struct patient einen union mit pointern auf zwei verschiedene struct (date_male, date_female) einzubauen.
Pointer sind immer gleichgroß und nur vom System abhängig 32/64Bit.
In der Funktion initialise_db() wird durch malloc() erst die Unter-struct date_male/date_female erzeugt und der Pointer dem Union
date zugewiesen.
