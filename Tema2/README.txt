// Copyright 2020 <Sandu Stefania-Cristina>
Task 1
-citesc numerele si il determin pe cel mai mare dintre ele pentru a sti cata memorie sa aloc pentru vectorul de frecventa
-ma pozitionez la inceputul stdin-ului pentru a le citi iar si a incrementa aparitia fiecareia in vector
-la final parcurg vectorul si afisez elementele

Task 2
-in acest task folosesc doua structuri in implementare, una pentru hashtable si una pentru informatia care trebuie retinuta, perechea key(string-ul) si value(frecventa aparitiei);astfel, hashtable-ul contine un vector de structuri de tip info
-functia de hash folosita este cea din laborator
-programul contine 3 functii, init_ht care initializeaza hashtable-ul alocand si memorie pentru buckets, put care are rolul de a modifica informatia din buckets daca acesta nu este ocupat, avand grija si de coliziuni astfel: compara string-ul(key) citit cu cel care exista in bucket-ul corespunzator indexului, iar daca acestea sunt la fel, se creste doar frecventa, altfel se cauta urmatorul index al carui bucket este liber, si functia free_ht care elibereaza memoria alocata hashtable-ului
-in main se citesc string-urile, mai intai pentru a determina size-ul hashtable-ului, apoi pentru a fi prelucrate si se apeleaza functiile implementate mai sus

Task 3
-functia de hash folosita in acest task este cea din laborator
-functia count zeros are rolul de a numara zero-urile pentru cei 21 de biti ramasi astfel:iau un aux ce reprezinta noul numar care se formeaza in urma shift-arii la stg cu 11, deci incepe cu cei 21 de biti ai numarului initial si iau numarul format prin shift-area lui 1 la stg cu 31, ce va produce 1 urmat de 31 de zero-uri, fac & intre cele doua;in acest mod, daca aux incepe cu 0 si stim ca 0 & 1 fac 0, atunci se va obtine 0 in urma acestei operatii pe care o repet, pentru a numara zero-urile, pana cand rezultatul este diferit de 0
-in cadrul aceleiasi functii, daca se citeste numarul 0, atunci zero-urile de la inceput vor fi 32
-functia max_function gaseste maximul dintre doua numere
-in main citesc din fisier si aloc memorie pentru M;

