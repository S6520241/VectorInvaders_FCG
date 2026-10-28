# VectorInvaders

**VectorInvaders** è un'applicazione grafica interattiva 2D sviluppata in C++ utilizzando la libreria **SFML 3.0**. Il progetto è articolato in 10 tappe di sviluppo progressivo.

## Requisiti e Compilazione

### Requisiti di Sistema
- **Compilatore C++**: Compatibile con lo standard C++17 o C++20.
- **CMake**: Versione 3.16 o superiore.
- **SFML**: Versione 3.0 (moduli `graphics`, `window`, `system`, `audio`). Non è necessario installarla: viene scaricata e compilata automaticamente da CMake, quindi alla prima configurazione serve una connessione internet. Su Linux sono richieste le librerie di sistema necessarie a SFML (X11, OpenGL, udev, freetype, librerie audio).

### Metodo Unico di Compilazione
Per compilare l'intero progetto, eseguire le seguenti istruzioni dalla radice del repository:

```bash
# 1. Creazione e configurazione della cartella di build
mkdir build
cd build
cmake ..

# 2. Compilazione di tutte le tappe in un unico comando
cmake --build .
```

Al termine della compilazione, gli eseguibili di tutte le tappe saranno generati all'interno della cartella build:
Tappa01, Tappa02, Tappa03, Tappa04, Tappa05, Tappa06, Tappa07, Tappa08, Tappa09, Tappa10.

### Esecuzione
Dalla cartella build/, avviare la tappa desiderata specificando il nome dell'eseguibile:
```bash
# Esempio: Esecuzione della Tappa 01
./Tappa01

# Esempio: Esecuzione della Tappa 02
./Tappa02
# ...
```

### Elenco Schematico dell'Interfaccia Utente (Tastiera e Mouse)
I controlli dell'interfaccia utente si evolvono con l'avanzare delle tappe di sviluppo

### Dettaglio Progressivo per Tappa
## Tappa 01 - Struttura Base e Movimento:

**Invio** : Avvio della sessione di gioco.

**Esc**: Fine della partita (Game Over); premendo **Invio** si torna al menu principale.

**Tasti W, A, S, D** oppure **Frecce Direzionali**: Spostamento della navicella nello spazio di gioco.

## Tappa 02 - Puntamento e Sparo:

**Movimento del Mouse**: Controllo dinamico della rotazione e della direzione di puntamento del giocatore.

**Tasto Sinistro del Mouse**: Attivazione del sistema di sparo.

## Tappa 07 - Power Up

**Scudo protettivo**: Permette di assorbire un colpo e non perdere la vita in caso di collisione o impatto; dopo il primo impatto lo scudo si esaurisce.   

**Sparo a ventaglio**: Consente di sparare tre proiettili alla volta per 8 secondi.

## Tappa 09 - Gestione Stato di Pausa e Menu:

**Tasto P**: Interruzione temporanea della partita (Pausa) e visualizzazione dell'interfaccia di menu; premendo di nuovo **P** la partita riprende.
