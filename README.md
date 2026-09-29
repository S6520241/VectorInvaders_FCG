# VectorInvaders

**VectorInvaders** è un'applicazione grafica interattiva 2D sviluppata in C++ utilizzando la libreria **SFML 3.0** e **CMake**. Il progetto è articolato in 10 tappe di sviluppo progressivo.

## 1. Requisiti e Compilazione

### Requisiti di Sistema
- **Compilatore C++**: Compatibile con lo standard C++17 o C++20.
- **CMake**: Versione 3.16 o superiore.
- **SFML**: Versione 3.0 (moduli `graphics`, `window`, `system`, `audio`).

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
tappa01, tappa02, tappa03, tappa04, tappa05, tappa06, tappa07, tappa08, tappa09, tappa10.

### Esecuzione
Dalla cartella build/, avviare la tappa desiderata specificando il nome dell'eseguibile:
```bash
# Esempio: Esecuzione della Tappa 01
./Tappa01

# Esempio: Esecuzione della Tappa 02
./Tappa02
```

### Elenco Schematico dell'Interfaccia Utente (Tastiera e Mouse)
I controlli dell'interfaccia utente si evolvono con l'avanzare delle tappe di sviluppo

### Dettaglio Progressivo per Tappa
## Tappa 01 - Struttura Base e Movimento:

**Invio** : Avvio della sessione di gioco.

**Esc**: Chiusura / Uscita dall'applicazione.

**W, A, S, D** oppure **Frecce Direzionali**: Spostamento della navicella nello spazio di gioco.

## Tappa 02 - Puntamento e Sparo:

**Movimento del Mouse**: Controllo dinamico della direzione del giocatore.

**Tasto Destro del Mouse**: Attivazione del sistema di sparo.

## Tappa 09 - Gestione Stato di Pausa e Menu:

**P**: Interruzione temporanea della partita (Pausa) e visualizzazione dell'interfaccia di menu.
