#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
};


// Stwórz Węzeł
Node* StworzWezel(int key) {

    // Tworzymy dynamincznie węzeł
    Node* newnode = new Node();

    //Przypisujemy węzłowi wybraną wartość a lewemu i prawemu synowi przypisujemy wartość NULL
    newnode->key = key;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// Dodaj węzeł
Node* Dodaj(Node* root, int key) {

    // Jeśli element w drzewie nie ma przypisanej żadnej liczby (czyli drzewo jest puste) to przypisujemy
    // gałęzi wartość funkcji która tworzy gałąź
    if (root == NULL)
    {
        root = StworzWezel(key);

    }
    // Jeśli klucz jest mniejszy od aktualnego punktu w jakim znajdujemy się w drzewie, to
    // korzystając z rekurencji wykonujemy ponownie funkcje dla kolejnego elementu w drzewie
    else if (key <= root->key) {
        root->left = Dodaj(root->left, key);
    }

    // Jeśli klucz jest większy od aktualnego punktu w jakim znajdujemy się w drzewie, to
    // korzystając z rekurencji wykonujemy ponownie funkcje dla kolejnego elementu w drzewie
    else {
        root->right = Dodaj(root->right, key);
    }
    return root;

}

// Szukaj węzła
bool Szukaj(Node* root, int key, int &poziom, int &pozycja) {

    // Jeśli nie znajdziemy szukanej wartości węzła, czyli nie znajduje się on w drzewie, to zwracamy
    // wartość false
    if (root == NULL) {
        return false;
    }

    // Jeśli udało nam się znaleźć element w drzewie to zwracamy wartość true
    else if (root->key == key) {
        return true;
    }

    // Jeśli przechodząc od początku drzewa, wartość pierwszego węzła nie jest równa NULL, to porównujemy
    // pierwszy element z szukanym i sprawdzamy czy jest większy, mniejszy lub równy od klucza.

    // Jeśli element szukany jest mniejszy badź równy od wartości aktualnego miejsca w jakim się znajdujemy
    // to rekurencyjnie przesuwamy się do lewego dziecka
    else if (key <= root->key) {

        // Zmienna poziom mówi na jakiej wysokości znajduje się szukany element
        poziom++;

        // Zmienna pozycja mówi na jakiej pozycji znajduje się szukany element
        pozycja = pozycja * 2;

        return Szukaj(root->left, key, poziom, pozycja);
    }

    // Jeśli element szukany jest większy od wartości aktualnego miejsca w jakim się znajdujemy
    // to rekurencyjnie przesuwamy się do prawego dziecka
    else {
        poziom++;
        pozycja = (pozycja * 2) + 1;
        return Szukaj(root->right, key, poziom, pozycja);
    }
}


// Znajdz mina
void Min(Node* root ,int &min)
{
    // Jeśli korzeń drzewa jest równy wartości NULL, to oznacza że drzewo jest puste i zwracamy
    // wartość NULL
    if (root == NULL) {
        min = NULL;
    }
    // Jeśli korzeń drzewa posiada wartość różną od NULL, to aby znależć wartość minimalną drzewa
    // przesuwamy się po lewej gałezi w pętli while aż do momentu kiedy dotrzemy do ostatniego liścia
    // którego wartość wynosi NULL
    else {
        while (root->left != NULL) {
            root = root->left;
        }
        // Pod koniec zwracamy wartość najmniejszego elementu
        min = root->key;
    }
}

//Znajdz maxa
void Maks(Node* root, int &maks)
{
    // Jeśli korzeń drzewa jest równy wartości NULL, to oznacza że drzewo jest puste i zwracamy
    // wartość NULL
    if (root == NULL) {
        maks = NULL;
    }

    // Jeśli korzeń drzewa posiada wartość różną od NULL, to aby znależć wartość maksymalną drzewa
    // przesuwamy się po prawej gałezi w pętli while aż do momentu kiedy dotrzemy do ostatniego liścia
    // którego wartość wynosi NULL
    else {
        while (root->right != NULL) {
            root = root->right;
        }
        // Pod koniec zwracamy wartość największego elementu
        maks = root->key;
    }
}

// Zlicz węzły
int Zlicz(Node* &root) {

    int licz = 0;

    // Sprawdzamy czy korzeń jest pusty
    // Jeśli korzeń nie jest pusty zliczamy w zmiennej "l" ilość elementów elementów
    // poruszjac się po gałęziach drzewa
    if (root)
    {
        licz++;
        licz = licz + Zlicz(root->left);
        licz = licz + Zlicz(root->right);
    }
    return licz;
    // Pod koniec zwracamy ilość elementów jaką udało się zliczyć
}

// Znajdz mininimalną wartosc dla innej funkcji (usun)
Node* MinUsun(Node* root)
{
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}


// Usuń węzeł
Node* UsunWezel(Node* root, int key)
{

    // Jeśli korzeń drzewa jest równy wartości NULL, to oznacza że drzewo jest puste lub że udało nam się usunąć element z drzewa i zwracamy
    // wartość NULL
    if (root == NULL) {
        return root;
    }

    // Jeśli korzeń drzewa jest różny od wartości NULL, to porównujemy elementy w drzewie z szukanym elementem
    // i przesuwamy się po lewej lub prawej gałęzi aż do momentu znalezienia elementy (o ile znajduje się on w drzewie)
    else if (key < root->key) {
        root->left = UsunWezel(root->left, key);
    }
    else if (key > root->key) {
        root->right = UsunWezel(root->right, key);
    }

    // Jeśli znaleźliśmy element ,który chcemy usunąć w drzewie to musimy określić który z trzech przypadków
    // dotyczy elementu do usunięcia
    else {

        // Jeśli węzeł nie posiada żadnych synów to możemy go usunąć natychmiast
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }

        // Jeśli węzeł posiada jedno dziecko z prawej strony to przechowujemy wartość węzła, który chcemy
        // usunąć w tymaczasowej zmiennej "temp", następnie przesuwamy elementy z prawej gałęzi aż do usuwanego
        // węzła i usuwamy zmienną tymczasowa "temp"
        else if (root->left == NULL) {
            //Node* temp = root;
            root = root->right;
            //delete temp;
        }

        // Jeśli węzeł posiada jedno dziecko z lewej strony to przechowujemy wartość węzła, który chcemy
        // usunąć w tymaczasowej zmiennej "temp", następnie przesuwamy elementy z lewej gałęzi aż do usuwanego
        // węzła i usuwamy zmienną tymczasowa "temp"
        else if (root->right == NULL) {
            //Node* temp = root;
            root = root->left;
            //delete temp;
        }
        // Jeśli węzeł posiada oboje dzieci, musimy znaleźć węzeł z najmniejszą wartością w drzewie
        // i zapisać go w tymczasowej zmiennej temp, następnie ustawiamy wartość elementu który chcemy
        // usunąć na wartość minimalną następnie korzystając z rekurencji usuwamy wybrany element
        else {
            Node* temp = MinUsun(root->right);
            root->key = temp->key;
            root->right = UsunWezel(root->right, temp->key);
        }
    }
    return root;
}

// Wypisz drzewo (odwrotną metodą inorder)
void Wypisz(string sp, string sn, Node* root)
{
    string s;
    string cr, cl, cp;

    // Znaki pomocnicze z kodami ASCII
    cr = cl = cp = "  ";
    cr[0] = 218; cr[1] = 196;
    cl[0] = 192; cl[1] = 196;
    cp[0] = 179;

    // Jeśli drzewo jest puste to nic nie wypisuje (Warunek podstawowy)
    if (root != NULL)
    {
        // W zmiennej "s" umieszczamy tekst dla wierszy pośrednich
        s = sp;

        // Jeśli wywoływany element jest równy elementowi z tablice ASCI (w tym przypadku dla elementów znajdujących się po prawej stronie)
        // to oznacza, że musimy przesunąć się z wyświetlaniem kolejnych elementów do następnej kolumny z tego względu,
        // że już ta kolumna została uzupełniona
        if (sn == cr) {
            s[s.length() - 2] = ' ';
        }
        // Przechodzimy przez drzewo odwróconą metodą inorder
        Wypisz(s + cp, cr, root->right);
        s = s.substr(0, sp.length() - 2);
        cout << s << sn << root->key << endl;

        s = sp;

        if (sn == cl) {
            s[s.length() - 2] = ' ';
        }

        Wypisz(s + cp, cl, root->left);

    }
}
// Usuwamy całe drzewo
void UsunDrzewo(Node* root)
{   // Usuwamy elementy z drzewa metodą inorder
    if (root != NULL)
    {
        UsunDrzewo(root->left);
        UsunDrzewo(root->right);
        root->right = NULL;
        root->left = NULL;
        root->key = NULL;
    }
}
void Testy(Node** root, int liczba, int prze) {
    srand(time(NULL));
    int x;
    for (int i = 0; i < liczba; i++) {
        x = rand() % prze;
        *root = Dodaj(*root,x);
    }

}

int main()
{
    Node* root = NULL;
    int liczba;
    int min = 0;
    int maks = 0;
    int prze;
    int poziom = 1;
    int pozycja = 1;
    int wybor;
    do
    {
        system("CLS");
        cout << "-------------------------------------" << endl;
        cout << "     EMULATOR DRZEWA BINARNEGO " << endl;
        cout << "-------------------------------------" << endl;
        cout << "1. DODAJ (dodaje element do drzewa)" << endl;
        cout << "2. ZNAJDZ (szuka elementu w drzewie)" << endl;
        cout << "3. WYSWIETL (wyswietla drzewo)" << endl;
        cout << "4. MAX (znajdz maksymalny element)" << endl;
        cout << "5. MIN (znajdz minimalny element)" << endl;
        cout << "6. ZLICZ (zlicz wszystkie elementy)" << endl;
        cout << "7. USUN WEZEL (usun wybrany elememt)" << endl;
        cout << "8. USUN DRZEWO (zakonczy ten program)" << endl;
        cout << "9. TESTY (dodajemy elementy)" << endl;
        cout << "10. EXIT (zakonczy ten program)" << endl;
        cout << "--------------------------------------" << endl;
        cout << " WYBOR: ";
        cin >> wybor;
        cout << endl;

        switch (wybor)
        {

        case 1:
            cout << "Podaj liczbe jaka chcesz dodac: ";
            cin >> liczba;
            cout << endl;
            root = Dodaj(root, liczba);
            cout << "Dodano liczbe";
            cout << endl;
            system("pause");
            cout << endl;
            break;
        case 2:
            cout << "Podaj szukany element: ";
            cin >> liczba;
            cout << endl;
            if (Szukaj(root, liczba, poziom, pozycja) == true) {
                cout << "Element znajduje sie na poziomie " << poziom << " na pozycji " << pozycja;
                cout << endl;
                system("pause");
                cout << endl;
            }
            else {
                cout << "Brak szukanej liczby";
                cout << endl;
                system("pause");
            }
             break;
        case 3:
            cout << endl;
            Wypisz("", "", root);
            cout << endl;
            system("pause");
            cout << endl;
            break;
        case 4:
            Maks(root,maks);
            if (maks != NULL) {
                cout << "Maksymalna wartosc elementu w drzewie wynosi: " << maks;
                cout << endl;
                system("pause");
                cout << endl;
            }
            else {
                cout << "Brak maksymalnej wartości";
                cout << endl;
                system("pause");
                cout << endl;
            }
            break;
        case 5:
            Min(root, min);
            if (min != NULL) {
                cout << "Minimlana wartosc elementu w drzewie wynosi: " << min;
                cout << endl;
                system("pause");
                cout << endl;
            }
            else {
                cout << "Brak minimalnej wartosci";
                cout << endl;
                system("pause");
                cout << endl;
            }
            break;
        case 6:

            if (Zlicz(root) != NULL) {
                cout << "Drzewo posiada " << Zlicz(root) << " wezlow ";
                cout << endl;
                system("pause");
                cout << endl;
            }
            else {
                cout << "Brak wezlow";
                cout << endl;
                system("pause");
                cout << endl;
            }
            break;
        case 7:
            cout << "Podaj liczbe do usuniecia: ";
            cin >> liczba;
            cout << endl;
            if (Szukaj(root,liczba,poziom,pozycja) == true) {
                root = UsunWezel(root, liczba);
                cout << "Pomyslnie usunieto liczbe";
                cout << endl;
                system("pause");
                cout << endl;
            }
            else {
                cout << "Brak elementu do usuniecia";
                cout << endl;
                system("pause");
                cout << endl;
            }
            break;
        case 8:
            cout << "Wpisz 1 jesli napewno chcesz usunac drzewo lub 0 zeby wrocic: ";
            cin >> liczba;
            if (liczba == 1) {
                UsunDrzewo(root);
                root = NULL;
                cout << endl;
                cout << "Pomyslnie usunieto drzewo";
                cout << endl;
                system("pause");
                cout << endl;
            }
            else {
                break;
            }
            break;
        case 9:
            cout << "Podaj ilosc wezlow do dodania: ";
            cin >> liczba;
            cout << endl;
            cout << "Podaj przedział generowanych wartosci do wezlow od 0 do: ";
            cin >> prze;
            Testy(&root ,liczba, prze);
            break;
        }

    } while (wybor != 10);

    return 0;
}
