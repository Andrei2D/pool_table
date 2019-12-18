# Tabla de Biliard

1. Descriere proiect
2. Motivație
3. Implementare
4. Funcția de desenare

___

### 1. Descriere proiect

Proiectul prezinta o simulare a unei bile pe o masa drepunghiulara care se misca si ricoseaza la impactul cu peretii. Mingii i se poate imprima o forta si i se poate schimba orientarea.

### 2. Motivație

Dintre proiectele listate acesta mi s-a parut cel mai interesant pentru ca ideea de baza este un joc foarte popular si pentru ca implica concepte de baza de fizica.

### 3. Implementare

Modul in care functioneaza proiectul este in felul urmator:
* Se proceseaza input-urile 
* Se actualizeaza o stare
* Se reprezinta grafic starea

#### Starea
Starea este reprezentata de o clasa **Ball**, care are mai multe caracteristici fizice, carteziane si de limitare
```c++

struct Ball {
    // variabile statice

    float x; 
    float y;
    double alfa;
    float dist, veloc, acc;
    int lim_x_top, lim_y_top;
    int lim_x_bot, lim_y_bot;

    // metode
};
```
- x, y -reprezinta pozitiile centrului mingii
- alfa - unghiul orientarii mingii
- acc, veloc, dist - acceleratia, viteza si distanta parcusa de minge la apelarea functiei de actualizare a starii
- lim_x_top, lim_y_top - cordonatele punctului din stanga sus ce definesc un dreptunghi de care se loveste mingea
- lim_x_bot, lim_y_bot - coordonatele punctului din dreapta jos ale dreptunghiului

Modul in care se actualizeaza starea este prin apelarea functiei update() intr-o bucla infinita pe un thread separat creat in functia de initializare a proiectului, a carei structura este in felul urmator:

```

void* ball_update_thread(void* args) {

    // initializare minge

    while (true) {
        // asteptare un anumit interval de timp
        // actualizare stare 
    }

}
```
Functia de actualizare a mingii calculeaza distanta pe care o va parcuge mingea la acel timp in functie de viteza pe care o are si actualizeaza viteza in functie de acceleratie. 
Acceleratia scade cu o valoare fixa, o abstractizare a fortei de frecare a mingii cu tabla, pana cand viteza devine 0.
```c++
void Ball::update () {
    veloc += acc;
    dist += veloc;
    move ();    // actualizare pozitie in functie de distanta
    check_limits ();    // ciocniri cu marginea mesei

    if (veloc <= 0) {
        veloc = 0;
        acc = 0;
    } 
    else {
        acc -= this->fric_force;
    }
}
```

#### Input-urile
Exista 3 input-uri ce se prelucreaza:
* imprimare forta -> '.'
* rotire in sens trigonometric -> '7'
* retire in sens ceasornic -> '9'

In cadrul imprimarii unei forte se schimba acceleratia mingii.

### 4. Funcția de desenare

In cadrul functiei de desenare se realizeaza urmatorii pasi:
* extragere date minge in varabila locala
* desenare fundal
* creare matrice de tranzitie in functie de pozitia mingei
* desenare a unui cerc
  
Initializarile care se realizeaza inainte de de functia de desenare sunt:
- calcularea coordonatelor fundalului si setarea lor
- calcularea coordonatelor de pe diametrul unui cerc
- realizarea unei functii de normalizare din reperul [0, 1000]x[0, 625] in [-1,1]x[-1,1]
- pornirea firului de executie a mingii