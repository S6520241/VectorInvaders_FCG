# Relazione Progetto: VectorInvaders
## Tappa 01: Setup dell'Ambiente e Architettura di Base
### Cosa si propone di fare il progetto
Il progetto si propone di sviluppare **VectorInvaders**, un videogioco arcade 2D interattivo sviluppato in **C++**. Come da requisiti, il progetto fa affidamento sulla libreria multimediale **SFML 3.0** per la gestione del rendering grafico, degli input e dell'audio, e utilizza **CMake** come sistema di build.
L'obiettivo a lungo termine (attraverso le 10 tappe previste) è quello di creare uno sparatutto a scorrimento completo di giocatore, nemici, collisioni e sistema di punteggio, applicando i concetti fondamentali della grafica computerizzata e della programmazione orientata agli oggetti.

### Cosa aggiunge o risolve questa tappa
In questa prima tappa non sono ancora presenti elementi di gameplay. L'obiettivo primario è **gettare le fondamenta dell'applicazione**, risolvendo il problema dell'inizializzazione del progetto.
Nello specifico, questa tappa aggiunge:
*   **La creazione del contesto grafico:** Inizializzazione della finestra di gioco tramite le API di SFML.
*   **Il Game Loop principale:** L'implementazione del ciclo di vita continuo dell'applicazione, suddiviso rigorosamente in elaborazione degli eventi (es. chiusura della finestra), aggiornamento della logica (attualmente vuota) e fase di rendering (pulizia e disegno a schermo).

<img width="810" height="633" alt="image" src="https://github.com/user-attachments/assets/f5ee1971-78a4-4274-9d88-8c70c33efeec" />

### Soluzioni tecniche adottate
*   **Architettura Orientata agli Oggetti:** Per ovviare al problema della strutturazione del codice, ho deciso di incapsulare l'intero Game Loop e le variabili fondamentali (come la finestra di render) all'interno di una classe dedicata. 
*   In questo modo, il file `main.cpp` si limita esclusivamente a istanziare l'oggetto gioco e ad avviare il metodo `run()`, mantenendo una netta separazione delle responsabilità. 
