# Relazione Progetto: VectorInvaders
## Tappa 01: Setup dell'Ambiente e Architettura di Base
### Cosa si propone di fare il progetto
Il progetto si propone di sviluppare **VectorInvaders**, un videogioco arcade 2D interattivo sviluppato in **C++**. Come da requisiti, il progetto fa affidamento sulla libreria multimediale **SFML 3.0** per la gestione del rendering grafico, degli input e dell'audio, e utilizza **CMake** come sistema di build.
L'obiettivo a lungo termine (attraverso le 10 tappe previste) è quello di creare uno sparatutto a scorrimento completo di giocatore, nemici, collisioni e sistema di punteggio, applicando i concetti fondamentali della grafica computerizzata.

### Cosa aggiunge o risolve questa tappa
In questa prima tappa non sono ancora presenti elementi di gameplay. L'obiettivo primario è **gettare le fondamenta dell'applicazione**, risolvendo il problema dell'inizializzazione del progetto.
Nello specifico, questa tappa aggiunge:
*   **La creazione del contesto grafico:** Inizializzazione della finestra di gioco.
*   **Il Game Loop principale:** L'implementazione del ciclo di vita continuo dell'applicazione, suddiviso rigorosamente in elaborazione degli eventi, aggiornamento della logica (attualmente vuota) e fase di rendering (pulizia e disegno a schermo).

<img width="810" height="633" alt="image" src="https://github.com/user-attachments/assets/f5ee1971-78a4-4274-9d88-8c70c33efeec" />

### Soluzioni tecniche adottate
**Architettura Orientata agli Oggetti:** Per ovviare al problema della strutturazione del codice, ho deciso di incapsulare l'intero Game Loop e le variabili fondamentali (come la finestra di render) all'interno di una classe dedicata. 
In questo modo, il file `main.cpp` si limita esclusivamente a istanziare l'oggetto gioco e ad avviare il metodo `run()`, mantenendo una netta separazione delle responsabilità. 

## Tappa 02: Implementazione del Giocatore e Meccanica di Sparo

### Cosa aggiunge o risolve questa tappa
Dopo aver preparato il contesto grafico e il Game Loop principale, in questa seconda tappa il progetto compie il primo passo verso il gameplay interattivo. 
Nello specifico, questa tappa aggiunge:
*   **L'entità Giocatore (Player):** Implementazione della navicella controllabile dall'utente (`Player.cpp`, `Player.hpp`), del suo movimento e nel direzionamento dello sparo
*   **La meccanica di sparo (Bullet):** Introduzione dei proiettili (`Bullet.hpp`) che il giocatore può generare per difendersi
*   **Puntamento e Rotazione Dinamica (`updateRotation`):** Per permettere al giocatore di orientare lo sparo, è stata implementata la funzione che traccia la posizione del cursore. Sfruttando `window.mapPixelToCoords()`. Tramite l'arcotangente (`std::atan2`) viene calcolato l'angolo di inclinazione tra la navicella e il cursore, applicato poi direttamente alla forma geometrica con il supporto della gestione degli angoli in radianti (`sf::radians`).
*   **Integrazione nel Game Loop:** Le classi `Game.cpp` e `Player.cpp` sono state collegate per intercettare gli input da tastiera/mouse, aggiornare la posizione e gestire il rendering dei proiettili attivi.
*   **Configurazione centralizzata:** Creazione di un modulo di configurazione (`Config.hpp`) per gestire in modo pulito le costanti

<img width="812" height="631" alt="image" src="https://github.com/user-attachments/assets/9263b582-0fab-4eeb-9fa7-0f4684d5cac6" />

### Soluzioni tecniche adottate
*   **Centralizzazione dei Parametri:** È stato introdotto il file `Config.hpp`. Questa soluzione permette di raggruppare tutte le costanti di gioco (come dimensioni della finestra, velocità di movimento del giocatore, velocità dei proiettili) in un unico file, evitando l'uso di variabili numeriche sparse nel codice e facilitando il futuro bilanciamento del gioco.
*   **Gestione Indipendente dei Proiettili:** La logica dei colpi sparati è stata incapsulata nel file `Bullet.hpp`. Questo permette di istanziare e gestire in memoria molteplici proiettili in modo scalabile.
*   **Integrazione nel Game Loop:** Le classi principali, in particolare `Game.cpp` e `Player.cpp`, sono state espanse per intercettare gli input della tastiera (attraverso gli eventi SFML), aggiornare coerentemente lo stato di posizione del giocatore e gestire il rendering dinamico dei proiettili attivi.
*   **Funzione `updateRotation()`***: Per permettere al giocatore di orientare lo sparo tramite l'arcotangente e il calcolo dell'inclinazione tra navicella e cursore tramite `sf::radians`

