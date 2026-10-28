# VectorInvaders

**VectorInvaders** è un'applicazione grafica interattiva 2D sviluppata in C++ utilizzando la libreria **SFML 3.0**. Il progetto è articolato in 10 tappe di sviluppo progressivo.

## Requisiti e Compilazione

### Requisiti di Sistema
- **Compilatore C++**: Compatibile con lo standard C++20.
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

Le risorse (immagini, font e audio) vengono caricate dal percorso relativo `../Cartella-risorse/`: per questo gli eseguibili vanno avviati dalla cartella `build/` creata nella radice del repository.

### Elenco Schematico dell'Interfaccia Utente (Tastiera e Mouse)
I controlli dell'interfaccia utente si evolvono con l'avanzare delle tappe di sviluppo. Nella versione finale (Tappa 10):

- **Invio** oppure clic su **Start**: Avvio della partita dal menu principale.
- **Tasti W, A, S, D** oppure **Frecce Direzionali**: Spostamento della navicella.
- **Movimento del Mouse**: Rotazione e puntamento della navicella.
- **Tasto Sinistro del Mouse**: Sparo.
- **Tasto P**: Pausa / ripresa della partita.
- **Esc**: Fine della partita (Game Over).
- **Invio** (in Game Over): Ritorno al menu principale.

### Dettaglio Progressivo per Tappa
#### Tappa 01 - Struttura Base e Movimento:

**Invio** : Avvio della sessione di gioco.

**Esc**: Fine della partita (Game Over); premendo **Invio** si torna al menu principale.

**Tasti W, A, S, D** oppure **Frecce Direzionali**: Spostamento della navicella nello spazio di gioco.

#### Tappa 02 - Puntamento e Sparo:

**Movimento del Mouse**: Controllo dinamico della rotazione e della direzione di puntamento del giocatore.

**Tasto Sinistro del Mouse**: Attivazione del sistema di sparo.

#### Tappa 03 - Nemici:

**Controlli**: Invariati rispetto alla Tappa 02.

**Nemici**: Compaiono i primi avversari, generati e gestiti in più istanze contemporaneamente nell'area di gioco.

#### Tappa 04 - Collisioni:

**Controlli**: Invariati rispetto alla Tappa 02.

**Collisioni**: I proiettili colpiscono e distruggono i nemici; vengono introdotti punteggio e vite del giocatore.

#### Tappa 05 - Texture e Sprite:

**Controlli**: Invariati rispetto alla Tappa 02.

**Grafica**: Giocatore e nemici passano da forme geometriche a sprite con texture caricate da `Cartella-risorse`.

#### Tappa 06 - Tipi di Nemici:

**Controlli**: Invariati rispetto alla Tappa 02.

**Nemico Base**: Un solo colpo per essere distrutto.

**Tank**: Più grande e più lento, servono tre colpi per distruggerlo.

**Shooter**: Si ferma vicino al giocatore e gli spara contro.

#### Tappa 07 - Power Up

**Scudo protettivo**: Permette di assorbire un colpo e non perdere la vita in caso di collisione o impatto; dopo il primo impatto lo scudo si esaurisce.

**Sparo a ventaglio**: Consente di sparare tre proiettili alla volta per 8 secondi.

#### Tappa 08 - Effetti Visivi:

**Controlli**: Invariati rispetto alla Tappa 02.

**Effetti**: Sfondo stellato in movimento, esplosioni a particelle alla distruzione dei nemici e tremolio dello schermo (screen shake) quando il giocatore viene colpito.

#### Tappa 09 - Gestione Stato di Pausa e Menu:

**Tasto P**: Interruzione temporanea della partita (Pausa) e visualizzazione dell'interfaccia di menu; premendo di nuovo **P** la partita riprende.

**Menu principale**: Pulsanti cliccabili per avviare la partita o uscire dall'applicazione.

**Menu di pausa**: Pulsanti cliccabili per tornare al menu principale o uscire dall'applicazione.

**HUD**: Visualizzazione a schermo di punteggio, vite e tempo di sopravvivenza durante la partita.

#### Tappa 10 - Audio e Difficoltà Progressiva:

**Controlli**: Invariati rispetto alla Tappa 09.

**Audio**: Musica di sottofondo (messa in pausa insieme alla partita) ed effetti sonori per sparo ed esplosioni.

**Difficoltà progressiva**: La frequenza di comparsa dei nemici aumenta con il tempo di sopravvivenza.

