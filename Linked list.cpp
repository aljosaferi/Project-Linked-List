#include <iostream>
#include <chrono>

using namespace std;

struct element {
	int key;
	element* prev, * next;
};

int nova_nepomembna_funkcija() {
    return 100;
}

void menu() {
    cout << "______________________________________" << endl;
    cout << "|Dvojno povezan seznam - izbira      |" << endl;
    cout << "|                                    |" << endl;
    cout << "|1. Iskanje podatka                  |" << endl;
    cout << "|2. Vnos podatka v glavo             |" << endl;
    cout << "|3. Vnos podatka za elementom        |" << endl;
    cout << "|4. Vnosa podatka za repom           |" << endl;
    cout << "|5. Brisanje podatka                 |" << endl;
    cout << "|6. Izpis seznama od glave proti repu|" << endl;
    cout << "|7. Izpis seznama od repa proti glavi|" << endl;
    cout << "|8. Tesitranje hitrosti              |" << endl;
    cout << "|9. Zapri program                    |" << endl;
    cout << "|____________________________________|" << endl;
}

element* find(element* &head, int key) {
    element* current = head;
    while (current != NULL && current->key != key) {
        current = current->next;
    }
    return current;
}

void insertAfter(element* elem, element* &tail, int key) {
    element* newElement = new element();
    newElement->key = key;

    newElement->prev = elem;
    newElement->next = elem->next;
    elem->next = newElement;
    if (newElement->next != NULL) {
        newElement->next->prev = newElement;
    }
    else {
        tail = newElement;
    }

}

void insertInHead(element*& head, element*& tail, int key) {
    element* newElem = new element();
    newElem->key = key;
    newElem->next = head;
    newElem->prev = NULL;
    if (head != NULL) {
        head->prev = newElem;
    }
    else {
        tail = newElem;
    }
    head = newElem;
}

void insertAfterTail(element*& tail, element* &head, int key) {
    element* newElement = new element();
    newElement->key = key;
    newElement->next = NULL;
    newElement->prev = tail;
    if (tail != NULL) {
        tail->next = newElement;
    }
    else {
        head = newElement;
    }
    tail = newElement;
}

void deleteElement(element*& head, element*& tail, element* element) {
    if (element->prev == NULL && element->next == NULL) {
        head = NULL;
        tail = NULL;
    }
    else {
        if (element->prev != NULL) {
            element->prev->next = element->next;
        }
        else {
            head = element->next;
            head->prev = NULL;
        }
        if (element->next != NULL) {
            element->next->prev = element->prev;
        }
        else {
            tail = element->prev;
            tail->next = NULL;
        }
    }
    delete element;
}

void printHeadToTail(element*& head) {
    element* current = new element;
    current = head;
    while (current != NULL) {
        cout << current->key << "|";
        current = current->next;
    }
}

void printTailToHead(element*& tail) {
    element* current = new element();
    current = tail;
    while (current != NULL) {
        cout << current->key << "|";
        current = current->prev;
    }
}

void sumHeadToTail(element*& head) {
    long long int sum = 0;
    element* current = new element();
    current = head;

    while (current != NULL) {
        sum = sum + current->key;
        current = current->next;
    }

    cout <<"Vsota seznama od glave do repa je:" << sum;
}

void moveValuesRight(int i, int* array) {
    for (int j = i; j > 0; j--) {
        array[j] = array[j - 1];
    }
}

long long sumOfArray(int* &array, int N) {
    long long int sum = 0;
    for (long long i = 0; i < N; i++) {
        sum = sum + array[i];
    }
    return sum;
}

void speedTest(int N, element* &head, element* &tail, int &count) {
    

    int* array = new int[N];

    auto start = std::chrono::steady_clock::now();
    for (int i = 1; i <= N; i++) {
        insertInHead(head, tail, i);
        count++;
    }
    auto end = std::chrono::steady_clock::now();
    std::cout << "Cas trajanja vstavljanja elementov v glavo: " <<
        std::chrono::duration_cast<std::chrono::microseconds>
        (end - start).count() <<
        "mikrosekund." << std::endl;

    start = std::chrono::steady_clock::now();
    sumHeadToTail(head); cout << ", ";
    end = std::chrono::steady_clock::now();
    std::cout << "Cas trajanja vsote: " <<
        std::chrono::duration_cast<std::chrono::microseconds>
        (end - start).count() <<
        "mikrosekund." << std::endl;

    start = std::chrono::steady_clock::now();
    for (int i = 1; i <= N; i++) {
        moveValuesRight(i, array);
        array[0] = i;
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Cas trajanja premikanja vrednosti v desno: " <<
        std::chrono::duration_cast<std::chrono::microseconds>
        (end - start).count() <<
        "mikrosekund." << std::endl;

    /*for (int i = 0; i < N; i++) {
        cout << array[i] << "|";
    }*/
    start = std::chrono::steady_clock::now();
    long long int sumOfArray = 0;
    for (int i = 0; i < N; i++) {
        sumOfArray = sumOfArray + array[i];
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Vsota vseh vrednosti v polju je: "<< sumOfArray <<"|Cas trajanja racunanje vsote polja : " <<
        std::chrono::duration_cast<std::chrono::microseconds>
        (end - start).count() <<
        "mikrosekund." << std::endl;

    start = std::chrono::steady_clock::now();
    for (int i = 0; i < N; i++) {
        array[i] = i + 1;
    }
    end = std::chrono::steady_clock::now();
    std::cout << "Cas trajanja vstavljanja na konec polja: " <<
        std::chrono::duration_cast<std::chrono::microseconds>
        (end - start).count() <<
        "mikrosekund." << std::endl;


}

int main()
{
    element* head = new element();
    element* tail = new element();

    head = NULL;
    tail = NULL;
    
    int selection;
    bool running = true;
    int numberOfElements = 0;
    int count = 0;

    element* result = new element();
    element* input = new element();

    do {
        menu();

        cin >> selection;

        switch (selection) {
        case 1:
            int findKey;
            cout << "Vnesi vrednost ki jo zelis najti: " << endl; cin >> findKey;
            if (head == NULL && tail == NULL) {
                cout << "Seznam je prazen!" << endl;
            }
            else if (find(head, findKey) == NULL) {
                cout << "Element ne obstaja!" << endl;
            }
            else {
                cout << "Element obstaja!" << endl;
            }
            break;

        case 2:
            cout << "Vnesi vrednost, ki jo zelis vstaviti v glavo!" << endl;
            int value;
            cin >> value;
            insertInHead(head, tail, value);
            numberOfElements++;
            break;

        case 3:
            int insertValue;
            int elementAfter;

            cout << "\nVnesi element za katerega zelis vstavljati: "; cin >> elementAfter;
            cout << "Vnesi vrednost, ki jo zelis vstaviti za element: "; cin >> insertValue;

            if (find(head, elementAfter) == NULL) {
                cout << "Vstavljanje ni mogoce, element za katerega zelite vstaviti ne obstaja!" << endl;
            }
            else {
                insertAfter(find(head, elementAfter), tail, insertValue);
                numberOfElements++;
            }

            break;

        case 4:
            int insertTail;
            cout << "Vnesi vrednost, ki jo zelis vstaviti v rep: "; cin >> insertTail;
            insertAfterTail(tail, head, insertTail);
            numberOfElements++;
            break;

        case 5:
            int deleteValue;
            cout << "Vnesi vrednost elementa, ki ga zelis izbrisati: "; cin >> deleteValue;
            if (find(head, deleteValue) == NULL) {
                cout << "Element ne obstaja, ni ga mogoce izbrisat!" << endl;
            }
            else {
                deleteElement(head, tail, find(head, deleteValue));
                numberOfElements--;
            }
            break;

        case 6:
            if (head == NULL && tail == NULL) {
                cout << "Seznam je prazen!" << endl;
            }
            else {
                printHeadToTail(head);
            }
            break;

        case 7:
            if (head == NULL && tail == NULL) {
                cout << "Seznam je prazen!" << endl;
            }
            else {
                printTailToHead(tail);
            }
            break;

        case 8: {
            count += numberOfElements;
            int N;

            for (int i = 0; i < count; i++) {
                deleteElement(head, tail, head);
            }
            cout << "Vnesite stevilo elementov: "; cin >> N;

            speedTest(N, head, tail, count);

            break;
        }
        case 9:
            running = false;
            break;
        default:
            std::cout << "Napacna izbira!" << std::endl;
        }
        std::cout << std::endl;
    } while (running);

    
    delete head;
    delete tail;
    delete input;
    delete result;

    return 0;
}
