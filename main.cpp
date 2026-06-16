#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Zaidejas {
    int id;
    string vardas;
    string komanda;
    string pozicija;
    int amzius;
    int ivarciai;
    int perdavimai;
};

const string DUOMENU_FAILAS = "zaidejai.txt";
const string ATASKAITOS_FAILAS = "ataskaita.txt";

vector<string> isskaidytiEilute(const string& eilute, char skirtukas) {
    vector<string> dalys;
    string dalis;
    stringstream ss(eilute);

    while (getline(ss, dalis, skirtukas)) {
        dalys.push_back(dalis);
    }

    return dalys;
}

void nuskaitytiIsFailo(vector<Zaidejas>& zaidejai) {
    ifstream failas(DUOMENU_FAILAS);

    if (!failas) {
        cout << "Nepavyko atidaryti failo: " << DUOMENU_FAILAS << endl;
        return;
    }

    zaidejai.clear();
    string eilute;

    while (getline(failas, eilute)) {
        if (eilute.empty()) {
            continue;
        }

        vector<string> dalys = isskaidytiEilute(eilute, ';');

        if (dalys.size() == 7) {
            Zaidejas z;
            z.id = stoi(dalys[0]);
            z.vardas = dalys[1];
            z.komanda = dalys[2];
            z.pozicija = dalys[3];
            z.amzius = stoi(dalys[4]);
            z.ivarciai = stoi(dalys[5]);
            z.perdavimai = stoi(dalys[6]);

            zaidejai.push_back(z);
        }
    }

    failas.close();
}

void issaugotiIFaila(const vector<Zaidejas>& zaidejai) {
    ofstream failas(DUOMENU_FAILAS);

    if (!failas) {
        cout << "Nepavyko issaugoti duomenu i faila." << endl;
        return;
    }

    for (const Zaidejas& z : zaidejai) {
        failas << z.id << ";"
               << z.vardas << ";"
               << z.komanda << ";"
               << z.pozicija << ";"
               << z.amzius << ";"
               << z.ivarciai << ";"
               << z.perdavimai << endl;
    }

    failas.close();
    cout << "Duomenys sekmingai issaugoti i faila." << endl;
}

void rodytiZaideja(const Zaidejas& z) {
    cout << left << setw(5) << z.id
         << setw(22) << z.vardas
         << setw(18) << z.komanda
         << setw(10) << z.pozicija
         << setw(8) << z.amzius
         << setw(10) << z.ivarciai
         << setw(12) << z.perdavimai << endl;
}

void rodytiAntraste() {
    cout << left << setw(5) << "ID"
         << setw(22) << "Vardas"
         << setw(18) << "Komanda"
         << setw(10) << "Pozicija"
         << setw(8) << "Amzius"
         << setw(10) << "Ivarciai"
         << setw(12) << "Perdavimai" << endl;

    cout << string(85, '-') << endl;
}

void rodytiVisusZaidejus(const vector<Zaidejas>& zaidejai) {
    if (zaidejai.empty()) {
        cout << "Zaideju sarasas tuscias." << endl;
        return;
    }

    rodytiAntraste();

    for (const Zaidejas& z : zaidejai) {
        rodytiZaideja(z);
    }
}

int rastiZaidejoIndeksaPagalId(const vector<Zaidejas>& zaidejai, int id) {
    for (int i = 0; i < (int)zaidejai.size(); i++) {
        if (zaidejai[i].id == id) {
            return i;
        }
    }

    return -1;
}

int generuotiNaujaId(const vector<Zaidejas>& zaidejai) {
    int didziausiasId = 0;

    for (const Zaidejas& z : zaidejai) {
        if (z.id > didziausiasId) {
            didziausiasId = z.id;
        }
    }

    return didziausiasId + 1;
}

void rodytiZaidejaPagalId(const vector<Zaidejas>& zaidejai) {
    int id;
    cout << "Iveskite zaidejo ID: ";
    cin >> id;

    int indeksas = rastiZaidejoIndeksaPagalId(zaidejai, id);

    if (indeksas == -1) {
        cout << "Zaidejas su tokiu ID nerastas." << endl;
    } else {
        rodytiAntraste();
        rodytiZaideja(zaidejai[indeksas]);
    }
}

void pridetiZaideja(vector<Zaidejas>& zaidejai) {
    Zaidejas z;
    z.id = generuotiNaujaId(zaidejai);

    cin.ignore();

    cout << "Iveskite zaidejo varda ir pavarde: ";
    getline(cin, z.vardas);

    cout << "Iveskite komanda: ";
    getline(cin, z.komanda);

    cout << "Iveskite pozicija: ";
    getline(cin, z.pozicija);

    cout << "Iveskite amziu: ";
    cin >> z.amzius;

    cout << "Iveskite ivarciu skaiciu: ";
    cin >> z.ivarciai;

    cout << "Iveskite perdavimu skaiciu: ";
    cin >> z.perdavimai;

    zaidejai.push_back(z);

    cout << "Zaidejas pridetas sekmingai. Jam priskirtas ID: " << z.id << endl;
}

void redaguotiZaideja(vector<Zaidejas>& zaidejai) {
    int id;
    cout << "Iveskite redaguojamo zaidejo ID: ";
    cin >> id;

    int indeksas = rastiZaidejoIndeksaPagalId(zaidejai, id);

    if (indeksas == -1) {
        cout << "Zaidejas su tokiu ID nerastas." << endl;
        return;
    }

    cin.ignore();

    cout << "Naujas vardas ir pavarde: ";
    getline(cin, zaidejai[indeksas].vardas);

    cout << "Nauja komanda: ";
    getline(cin, zaidejai[indeksas].komanda);

    cout << "Nauja pozicija: ";
    getline(cin, zaidejai[indeksas].pozicija);

    cout << "Naujas amzius: ";
    cin >> zaidejai[indeksas].amzius;

    cout << "Naujas ivarciu skaicius: ";
    cin >> zaidejai[indeksas].ivarciai;

    cout << "Naujas perdavimu skaicius: ";
    cin >> zaidejai[indeksas].perdavimai;

    cout << "Zaidejo duomenys atnaujinti." << endl;
}

void istrintiZaideja(vector<Zaidejas>& zaidejai) {
    int id;
    cout << "Iveskite trinamo zaidejo ID: ";
    cin >> id;

    int indeksas = rastiZaidejoIndeksaPagalId(zaidejai, id);

    if (indeksas == -1) {
        cout << "Zaidejas su tokiu ID nerastas." << endl;
        return;
    }

    zaidejai.erase(zaidejai.begin() + indeksas);

    cout << "Zaidejas istrintas sekmingai." << endl;
}

void ieskotiPagalKomanda(const vector<Zaidejas>& zaidejai) {
    cin.ignore();

    string komanda;
    cout << "Iveskite komandos pavadinima: ";
    getline(cin, komanda);

    bool rasta = false;
    rodytiAntraste();

    for (const Zaidejas& z : zaidejai) {
        if (z.komanda == komanda) {
            rodytiZaideja(z);
            rasta = true;
        }
    }

    if (!rasta) {
        cout << "Zaideju is tokios komandos nerasta." << endl;
    }
}

void rikiuotiPagalIvarcius(vector<Zaidejas>& zaidejai) {
    sort(zaidejai.begin(), zaidejai.end(), [](const Zaidejas& a, const Zaidejas& b) {
        return a.ivarciai > b.ivarciai;
    });

    cout << "Zaidejai surikiuoti pagal ivarcius mazejimo tvarka." << endl;
    rodytiVisusZaidejus(zaidejai);
}

void rodytiStatistika(const vector<Zaidejas>& zaidejai) {
    if (zaidejai.empty()) {
        cout << "Negalima skaiciuoti statistikos, nes sarasas tuscias." << endl;
        return;
    }

    int bendriIvarciai = 0;
    int bendriPerdavimai = 0;
    int rezultatyviausioIndeksas = 0;

    for (int i = 0; i < (int)zaidejai.size(); i++) {
        bendriIvarciai += zaidejai[i].ivarciai;
        bendriPerdavimai += zaidejai[i].perdavimai;

        if (zaidejai[i].ivarciai > zaidejai[rezultatyviausioIndeksas].ivarciai) {
            rezultatyviausioIndeksas = i;
        }
    }

    double ivarciuVidurkis = (double)bendriIvarciai / zaidejai.size();

    cout << "Zaideju skaicius: " << zaidejai.size() << endl;
    cout << "Bendras ivarciu skaicius: " << bendriIvarciai << endl;
    cout << "Bendras perdavimu skaicius: " << bendriPerdavimai << endl;
    cout << fixed << setprecision(2);
    cout << "Vidutinis ivarciu skaicius: " << ivarciuVidurkis << endl;
    cout << "Rezultatyviausias zaidejas: "
         << zaidejai[rezultatyviausioIndeksas].vardas
         << " (" << zaidejai[rezultatyviausioIndeksas].ivarciai << " ivarciai)" << endl;
}

void generuotiAtaskaita(const vector<Zaidejas>& zaidejai) {
    ofstream failas(ATASKAITOS_FAILAS);

    if (!failas) {
        cout << "Nepavyko sukurti ataskaitos failo." << endl;
        return;
    }

    int bendriIvarciai = 0;
    int bendriPerdavimai = 0;

    for (const Zaidejas& z : zaidejai) {
        bendriIvarciai += z.ivarciai;
        bendriPerdavimai += z.perdavimai;
    }

    failas << "Futbolo zaideju statistikos ataskaita" << endl;
    failas << "====================================" << endl;
    failas << "Zaideju skaicius: " << zaidejai.size() << endl;
    failas << "Bendras ivarciu skaicius: " << bendriIvarciai << endl;
    failas << "Bendras perdavimu skaicius: " << bendriPerdavimai << endl;

    if (!zaidejai.empty()) {
        failas << "Vidutinis ivarciu skaicius: "
               << fixed << setprecision(2)
               << (double)bendriIvarciai / zaidejai.size() << endl;
    }

    failas << endl << "Visi zaidejai:" << endl;

    for (const Zaidejas& z : zaidejai) {
        failas << z.id << ". "
               << z.vardas << ", "
               << z.komanda << ", "
               << z.pozicija << ", "
               << z.amzius << " m., "
               << z.ivarciai << " ivarciai, "
               << z.perdavimai << " perdavimai" << endl;
    }

    failas.close();

    cout << "Ataskaita sugeneruota faile: " << ATASKAITOS_FAILAS << endl;
}

void rodytiMeniu() {
    cout << endl;
    cout << "========================================" << endl;
    cout << " FUTBOLO ZAIDEJU STATISTIKOS SISTEMA" << endl;
    cout << "========================================" << endl;
    cout << "1. Rodyti visus zaidejus" << endl;
    cout << "2. Rodyti zaideja pagal ID" << endl;
    cout << "3. Prideti nauja zaideja" << endl;
    cout << "4. Redaguoti zaideja" << endl;
    cout << "5. Istrinti zaideja" << endl;
    cout << "6. Ieskoti pagal komanda" << endl;
    cout << "7. Rikiuoti pagal ivarcius" << endl;
    cout << "8. Rodyti statistika" << endl;
    cout << "9. Generuoti ataskaita" << endl;
    cout << "10. Issaugoti duomenis i faila" << endl;
    cout << "0. Baigti programa" << endl;
    cout << "Pasirinkite veiksma: ";
}

int main() {
    vector<Zaidejas> zaidejai;
    int pasirinkimas;

    nuskaitytiIsFailo(zaidejai);

    do {
        rodytiMeniu();
        cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                rodytiVisusZaidejus(zaidejai);
                break;
            case 2:
                rodytiZaidejaPagalId(zaidejai);
                break;
            case 3:
                pridetiZaideja(zaidejai);
                break;
            case 4:
                redaguotiZaideja(zaidejai);
                break;
            case 5:
                istrintiZaideja(zaidejai);
                break;
            case 6:
                ieskotiPagalKomanda(zaidejai);
                break;
            case 7:
                rikiuotiPagalIvarcius(zaidejai);
                break;
            case 8:
                rodytiStatistika(zaidejai);
                break;
            case 9:
                generuotiAtaskaita(zaidejai);
                break;
            case 10:
                issaugotiIFaila(zaidejai);
                break;
            case 0:
                issaugotiIFaila(zaidejai);
                cout << "Programa baigta." << endl;
                break;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
        }

    } while (pasirinkimas != 0);

    return 0;
}
