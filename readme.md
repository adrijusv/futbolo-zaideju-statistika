Futbolo žaidėjų statistikos valdymo sistema

Projekto tikslas

Sukurti C++ konsolinę programą, skirtą futbolo žaidėjų statistikos valdymui.

Pasirinkta tema

Programa leidžia saugoti ir valdyti futbolo žaidėjų informaciją: vardą, komandą, poziciją, amžių, įvarčius ir rezultatyvius perdavimus.

Programos funkcionalumas

Programa leidžia:

* Peržiūrėti visus žaidėjus;
* Peržiūrėti žaidėją pagal ID;
* Pridėti naują žaidėją;
* Redaguoti žaidėjo informaciją;
* Ištrinti žaidėją;
* Ieškoti žaidėjų pagal komandą;
* Rikiuoti žaidėjus pagal įvarčius;
* Peržiūrėti statistiką;
* Generuoti ataskaitą;
* Išsaugoti duomenis faile.

Naudojami failai

* main.cpp – programos kodas.
* zaidejai.txt – pradiniai duomenys.
* ataskaita.txt – sugeneruojama programos vykdymo metu.

Programos paleidimas

clang++ -c main.cpp
clang++ main.o -o programa
./programa

Papildomos funkcijos

* Paieška pagal komandą.
* Rikiavimas pagal įvarčius.
* Statistikos skaičiavimas.
* Ataskaitos generavimas.