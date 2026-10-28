# Relazione Progetto: VectorInvaders
## Tappa 01: Setup dell'Ambiente e Architettura di Base
### Cosa si propone di fare il progetto
Il progetto si propone di sviluppare **VectorInvaders**, un videogioco arcade 2D interattivo sviluppato in **C++**. Come da requisiti, il progetto fa affidamento sulla libreria multimediale **SFML 3.0** per la gestione del rendering grafico, degli input e dell'audio, e utilizza **CMake** come sistema di build.
L'obiettivo a lungo termine (attraverso le 10 tappe previste) è quello di creare uno sparatutto 2D con visuale dall'alto, in cui il giocatore affronta ondate di nemici in un'arena fissa, completo di giocatore, nemici, collisioni e sistema di punteggio, applicando i concetti fondamentali della grafica computerizzata.

### Cosa aggiunge o risolve questa tappa
In questa prima tappa il gameplay è ridotto al minimo indispensabile. L'obiettivo primario è **gettare le fondamenta dell'applicazione**, risolvendo il problema dell'inizializzazione del progetto.
Nello specifico, questa tappa aggiunge:
*   **La creazione del contesto grafico:** Inizializzazione della finestra di gioco (800x600) con limite di 60 fotogrammi al secondo.
*   **Il Game Loop principale:** L'implementazione del ciclo di vita continuo dell'applicazione, suddiviso rigorosamente in elaborazione degli eventi, aggiornamento della logica e fase di rendering (pulizia e disegno a schermo).
*   **La macchina a stati del gioco:** Introduzione degli stati Menu principale, Gameplay e Game Over (`GameState.hpp`). Si passa dal menu al gioco con **Invio**, dal gioco al Game Over con **Esc** e si torna al menu con **Invio**; ogni stato ha un colore di sfondo diverso.
*   **Una prima versione del giocatore:** Un rettangolo verde (`Player.cpp`, `Player.hpp`) che si sposta con i tasti W, A, S, D o con le frecce direzionali.

<img width="810" height="633" alt="image" src="https://github.com/user-attachments/assets/f5ee1971-78a4-4274-9d88-8c70c33efeec" />

### Soluzioni tecniche adottate
**Architettura Orientata agli Oggetti:** Per ovviare al problema della strutturazione del codice, ho deciso di incapsulare l'intero Game Loop e le variabili fondamentali (come la finestra di render) all'interno di una classe dedicata. 
In questo modo, il file `main.cpp` si limita esclusivamente a istanziare l'oggetto gioco e ad avviare il metodo `run()`, mantenendo una netta separazione delle responsabilità. 

**Gestione degli stati tramite `enum`:** Lo stato corrente del gioco è memorizzato in un'enumerazione; sia la gestione degli eventi sia il rendering controllano lo stato corrente per decidere cosa fare e cosa disegnare.

## Tappa 02: Implementazione del Puntamento e Meccanica di Sparo

### Cosa aggiunge o risolve questa tappa
In questa seconda tappa il progetto compie il primo passo verso il gameplay interattivo. 
Nello specifico, questa tappa aggiunge:
*   **Evoluzione del Giocatore (Player):** La navicella introdotta nella Tappa 01 (`Player.cpp`, `Player.hpp`) viene estesa con la rotazione verso il cursore e con il direzionamento dello sparo; inoltre il giocatore non può più uscire dai bordi della finestra (`constrainBounds`).
*   **La meccanica di sparo (Bullet):** Introduzione dei proiettili (`Bullet.hpp`) che il giocatore genera con il tasto sinistro del mouse per difendersi. I proiettili partono dalla punta della navicella nella direzione in cui essa è orientata e vengono eliminati quando escono dallo schermo.
*   **Integrazione nel Game Loop:** Le classi `Game.cpp` e `Player.cpp` sono state collegate per intercettare gli input da tastiera e mouse, aggiornare la posizione e gestire il rendering dei proiettili attivi.
*   **Configurazione centralizzata:** Creazione di un modulo di configurazione (`Config.hpp`) per gestire in modo pulito le costanti.

<img width="812" height="631" alt="image" src="https://github.com/user-attachments/assets/9263b582-0fab-4eeb-9fa7-0f4684d5cac6" />

### Soluzioni tecniche adottate
*   **Centralizzazione dei Parametri:** È stato introdotto il file `Config.hpp`. Questa soluzione permette di raggruppare tutte le costanti di gioco (come dimensioni della finestra, velocità di movimento del giocatore, velocità dei proiettili) in un unico file, evitando l'uso di variabili numeriche sparse nel codice e facilitando il futuro bilanciamento del gioco.
*   **Gestione Indipendente dei Proiettili:** La logica dei colpi sparati è stata incapsulata nel file `Bullet.hpp`. Questo permette di istanziare e gestire in memoria molteplici proiettili in modo scalabile.
*   **Due modalità di lettura dell'input:** Il movimento della navicella usa la lettura in tempo reale dello stato dei tasti (`sf::Keyboard::isKeyPressed`), così il giocatore si muove in modo fluido finché il tasto resta premuto. Lo sparo e i cambi di stato (Invio, Esc) usano invece gli eventi SFML (`pollEvent`), che vengono generati una sola volta per ogni pressione.
*   **Funzione `updateRotation()`:** Per permettere al giocatore di orientare lo sparo, la funzione legge la posizione del cursore e la converte in coordinate del mondo di gioco con `window.mapPixelToCoords()`. Tramite l'arcotangente (`std::atan2`) viene poi calcolato l'angolo tra la navicella e il cursore, applicato direttamente alla forma geometrica come angolo in radianti (`sf::radians`).
*   **Direzione dei proiettili:** La velocità di ogni proiettile è ottenuta da coseno e seno dell'angolo della navicella, moltiplicati per la velocità definita in `Config.hpp`.

## Tappa 03: Implementazione dei Nemici e Logica di Base 
### Cosa aggiunge o risolve questa tappa 
In questa terza fase, il gameplay inizia a prendere forma introducendo i bersagli per la meccanica di sparo implementata nella fase precedente. Nello specifico, questa tappa aggiunge: 
* **L'entità Nemico (Enemy):** Introduzione della struttura per i nemici tramite il nuovo file `Enemy.hpp`. In questa tappa ogni nemico è un quadrato rosso. 
* **Generazione dei nemici:** Ogni secondo viene generato un nuovo nemico in una posizione casuale appena fuori da uno dei quattro lati dello schermo, scelto anch'esso a caso.
* **Inseguimento del giocatore:** Ogni nemico si muove ad ogni fotogramma verso la posizione attuale del giocatore.
* **Gestione Multipla:** Modifica della logica centrale del gioco per supportare la gestione di diverse istanze nemiche contemporaneamente all'interno dell'area di gioco. 
* **Evoluzione del Game Loop:** Aggiornamento delle classi `Game.cpp` e `Game.hpp` per elaborare il movimento e il rendering grafico dei nemici ad ogni ciclo di vita dell'applicazione.

<img width="805" height="626" alt="image" src="https://github.com/user-attachments/assets/4cc8f6cb-d277-4039-810d-8685814549b3" />

### Soluzioni tecniche adottate 
* **Struttura dati del nemico:** Il nemico è definito come una semplice struttura dati in `Enemy.hpp`, che contiene la sua forma grafica. La logica di generazione e di movimento è gestita dalla classe `Game`. 
* **Contenitori Dinamici per le Entità:** Per gestire un numero variabile e scalabile di nemici attivi sullo schermo, viene sfruttato un `std::vector` all'interno della classe `Game`. 
* **Generazione casuale:** Il lato di comparsa e la posizione lungo quel lato sono estratti con i generatori della libreria `<random>` (`std::mt19937` con distribuzioni uniformi).
* **Movimento verso il giocatore:** Per ogni nemico si calcola il vettore che lo separa dal giocatore e lo si normalizza dividendolo per la sua lunghezza; il risultato, moltiplicato per la velocità del nemico, è lo spostamento del fotogramma. In questo modo la velocità resta costante indipendentemente dalla distanza.
* **Temporizzazione:** La frequenza di comparsa è controllata da un `sf::Clock` confrontato con l'intervallo di generazione.
* **Estensione della Configurazione:** Sfruttando la soluzione tecnica del file `Config.hpp` introdotta nella Tappa 02, anche la velocità dei nemici è definita in modo centralizzato per un rapido bilanciamento.

## Tappa 04: Gestione delle Collisioni e Interazione tra le Entità

### Cosa aggiunge o risolve questa tappa
In questa quarta tappa, il focus principale è risolvere il problema delle collisioni e gestire in modo coerente il ciclo di vita delle entità attive. 
Nello specifico, questa tappa aggiunge:
*   **Collisione proiettile–nemico:** Implementazione della logica che verifica l'impatto tra i proiettili (`Bullet.hpp`) generati dal giocatore e i nemici (`Enemy.hpp`) presenti sullo schermo. Quando un proiettile colpisce un nemico, entrambi vengono distrutti.
*   **Collisione nemico–giocatore:** Quando un nemico tocca il giocatore, il nemico viene rimosso e il giocatore perde una vita.
*   **Punteggio e vite:** Ogni nemico distrutto vale 10 punti; il giocatore parte con 3 vite e, quando le esaurisce, il gioco passa allo stato di Game Over. Punteggio e vite vengono azzerati al ritorno al menu.
*   **Distruzione e Memory Management:** Aggiornamento della logica nel Game Loop principale (`Game.cpp`) per rimuovere correttamente le entità quando collidono.


https://github.com/user-attachments/assets/381fffc6-c923-439d-8491-0dff5eeb2b51

### Soluzioni tecniche adottate
*   **Cancellazione sicura durante l'iterazione:** La rimozione degli elementi distrutti avviene direttamente durante lo scorrimento dei vettori, usando il valore restituito da `erase` (`it = vettore.erase(it)`). In questo modo l'iteratore resta sempre valido e punta all'elemento successivo, evitando errori dovuti a iteratori invalidati.
*   **Hitbox e Intersezioni:** Le collisioni vengono rilevate verificando l'intersezione tra i rettangoli di ingombro (bounding box) delle forme, tramite `getGlobalBounds().findIntersection()`.
*   **Doppio ciclo per i proiettili:** Per ogni proiettile vengono controllati tutti i nemici; appena viene trovata una collisione il ciclo interno si interrompe, così ogni proiettile può distruggere un solo nemico.

## Tappa 05: Texture e Sprite

### Cosa aggiunge o risolve questa tappa
In questa quinta tappa l'aspetto grafico del gioco passa da semplici forme geometriche a immagini vere e proprie.
Nello specifico, questa tappa aggiunge:
*   **Sprite per giocatore e nemici:** Giocatore e nemici non sono più rettangoli colorati ma sprite (`sf::Sprite`) con texture caricate dalla cartella `Cartella-risorse` (`player.png`, `enemy.png`).
*   **Caricamento delle risorse:** Un nuovo metodo `loadResources()` carica le texture all'avvio e segnala in console eventuali file mancanti.
*   **File `Enemy.cpp`:** Il nemico ottiene un costruttore che riceve la texture da utilizzare.
*   **Finestra centrata:** All'avvio la finestra di gioco viene posizionata al centro del desktop.

<img width="812" height="632" alt="image" src="https://github.com/user-attachments/assets/533f4e0d-dd4a-47d6-bc51-dcbce9760cef" />

### Soluzioni tecniche adottate
*   **Dimensionamento indipendente dall'immagine:** In `Config.hpp` sono state aggiunte le dimensioni desiderate di giocatore e nemici (`TargetPlayerSize`, `TargetEnemySize`). Il fattore di scala viene calcolato dividendo la dimensione desiderata per la larghezza della texture, mantenendo le proporzioni originali; in questo modo si possono sostituire le immagini senza modificare il codice.
*   **Origine al centro:** L'origine di ogni sprite viene impostata al centro della texture, così rotazione e posizionamento avvengono attorno al centro dell'oggetto.
*   **Correzione dell'orientamento:** L'immagine della navicella è disegnata rivolta verso l'alto, mentre l'angolo restituito da `std::atan2` vale zero verso destra. Per questo alla rotazione viene sommato un quarto di giro (π/2) e, simmetricamente, viene sottratto nel calcolo della direzione dei proiettili.
*   **Inizializzazione dello sprite:** In SFML 3 uno sprite deve essere costruito con una texture; il giocatore viene quindi creato con la texture e configurato con il metodo `init()` dopo il caricamento delle risorse, forzando l'aggiornamento delle dimensioni dello sprite (`setTexture(texture, true)`).

## Tappa 06: Tipi di Nemici

### Cosa aggiunge o risolve questa tappa
In questa sesta tappa vengono introdotti nemici con comportamenti diversi, per rendere il gioco più vario.
Nello specifico, questa tappa aggiunge:
*   **Nemico Base:** Si muove verso il giocatore e viene distrutto con un colpo (60% delle comparse).
*   **Tank:** Più grande e lento (metà della velocità base), servono tre colpi per distruggerlo (20% delle comparse).
*   **Shooter:** Si avvicina al giocatore; quando si trova a meno di 250 pixel si ferma e gli spara contro un proiettile ogni 1,5 secondi (20% delle comparse).
*   **Proiettili nemici:** I colpi degli Shooter tolgono una vita quando colpiscono il giocatore e vengono eliminati quando escono dallo schermo.
*   **Nuove texture:** Caricamento delle immagini `tank.png` e `shooter.png`.

<img width="810" height="634" alt="image" src="https://github.com/user-attachments/assets/d29a29b0-e07a-4707-8e3e-4cd69c420785" />

### Soluzioni tecniche adottate
*   **Tipo e punti vita del nemico:** La struttura `Enemy` è stata estesa con un'enumerazione `EnemyType` (Base, Tank, Shooter), un contatore di punti vita (`hp`) e un `sf::Clock` personale per la cadenza di sparo.
*   **Estrazione percentuale:** Ad ogni comparsa viene estratto un numero da 1 a 100: da 1 a 60 si genera un nemico Base, da 61 a 80 un Tank, oltre 80 uno Shooter.
*   **Danno progressivo:** Quando un proiettile colpisce un nemico ne riduce i punti vita; il nemico viene rimosso, e il punteggio aumentato, solo quando questi arrivano a zero.
*   **Comportamento in base al tipo:** Nella funzione di aggiornamento dei nemici, il tipo determina la velocità (ridotta per il Tank) e se il nemico deve fermarsi e sparare (Shooter). Il proiettile nemico viene diretto verso il giocatore con lo stesso vettore normalizzato usato per il movimento.
*   **Vettore separato:** I proiettili nemici sono memorizzati in un vettore distinto da quelli del giocatore, così le collisioni dei due gruppi vengono controllate separatamente.

## Tappa 07: Power Up

### Cosa aggiunge o risolve questa tappa
In questa settima tappa vengono introdotti i potenziamenti, che il giocatore raccoglie passandoci sopra.
Nello specifico, questa tappa aggiunge:
*   **Comparsa dei power-up:** Ogni 10 secondi compare in un punto casuale dello schermo un potenziamento, scelto a caso tra i due tipi disponibili.
*   **Sparo a ventaglio:** Per 8 secondi il giocatore spara tre proiettili alla volta, con un'apertura a ventaglio.
*   **Scudo protettivo:** Assorbe un colpo senza perdere la vita; dopo il primo impatto si esaurisce. Quando è attivo, attorno alla navicella viene disegnato un cerchio azzurro semitrasparente.
*   **Invulnerabilità temporanea:** Dopo aver subito un colpo, o dopo che lo scudo lo ha assorbito, il giocatore è invulnerabile per 1,5 secondi e la navicella lampeggia.
*   **File `PowerUp.cpp` e `PowerUp.hpp`:** Nuova struttura per i potenziamenti, con texture dedicate (`powerup_spread.png`, `powerup_shield.png`).

<img width="807" height="628" alt="image" src="https://github.com/user-attachments/assets/a3b91679-05f0-4bd9-919b-b94a496c9ad4" />
<img width="805" height="629" alt="image" src="https://github.com/user-attachments/assets/a4db29d9-322b-4510-bf18-ed18a573cddf" />

### Soluzioni tecniche adottate
*   **Tipo del power-up:** Ogni potenziamento memorizza il proprio tipo tramite un'enumerazione `PowerUpType` (Spread, Shield).
*   **Stato del giocatore tramite flag:** Gli effetti attivi sono gestiti con variabili booleane (`hasSpread`, `hasShield`, `isInvulnerable`), ciascuna associata, dove serve, a un `sf::Clock` che ne misura la durata.
*   **Gestione centralizzata del danno:** È stata introdotta la funzione `takeDamage()`, chiamata sia dalle collisioni con i nemici sia da quelle con i proiettili nemici. Controlla in un unico punto invulnerabilità, scudo, perdita di vite e passaggio al Game Over.
*   **Sparo a ventaglio:** I tre proiettili vengono generati con la stessa funzione, aggiungendo all'angolo della navicella uno scostamento di -0,2, 0 e +0,2 radianti.
*   **Effetto di lampeggio:** Durante l'invulnerabilità la trasparenza della navicella varia seguendo una funzione seno del tempo trascorso.

## Tappa 08: Effetti Visivi

### Cosa aggiunge o risolve questa tappa
In questa ottava tappa il gioco viene arricchito con effetti grafici che migliorano il riscontro visivo delle azioni.
Nello specifico, questa tappa aggiunge:
*   **Sfondo stellato:** 150 stelle di dimensione e luminosità casuali scorrono verso il basso, dando una sensazione di movimento.
*   **Esplosioni a particelle:** Vengono generate esplosioni di particelle colorate quando un nemico viene colpito o distrutto, quando il giocatore subisce un colpo e quando lo scudo assorbe un impatto.
*   **Tremolio dello schermo (screen shake):** Quando il giocatore perde una vita, la visuale trema per 0,3 secondi.
*   **Nuovi file `Star.hpp` e `Particle.hpp`:** Strutture dati per le stelle e per le particelle.

<img width="809" height="627" alt="image" src="https://github.com/user-attachments/assets/77b760ba-97ca-4041-8f2b-06991c171649" />

### Soluzioni tecniche adottate
*   **Effetto profondità (parallasse):** La velocità di ogni stella è proporzionale al suo raggio: le stelle più grandi, che sembrano più vicine, scorrono più velocemente. Quando una stella esce dal fondo dello schermo viene riposizionata in alto in una posizione orizzontale casuale.
*   **Sistema di particelle:** Ogni particella ha una direzione casuale (angolo tra 0 e 2π), una velocità casuale e una durata di vita limitata. La sua trasparenza diminuisce in proporzione alla vita residua, così le particelle svaniscono gradualmente prima di essere rimosse dal vettore.
*   **Screen shake tramite `sf::View`:** Invece di spostare tutti gli oggetti, viene spostato il centro della visuale (`sf::View`) di un valore casuale entro un'intensità massima definita in `Config.hpp`; al termine dell'effetto la visuale torna centrata.
*   **Parametri in configurazione:** Il numero di stelle e l'intensità del tremolio sono definiti in `Config.hpp`.

## Tappa 09: Gestione Stato di Pausa e Menu

### Cosa aggiunge o risolve questa tappa
In questa nona tappa vengono introdotti un'interfaccia grafica completa e lo stato di pausa.
Nello specifico, questa tappa aggiunge:
*   **Menu principale grafico:** Titolo del gioco e pulsanti cliccabili "INIZIA" ed "ESCI"; resta comunque possibile iniziare la partita premendo Invio.
*   **Stato di pausa:** Premendo **P** la partita si ferma, sopra il gioco compare un velo scuro semitrasparente con la scritta "PAUSA" e i pulsanti per tornare al menu principale o uscire; premendo di nuovo **P** la partita riprende.
*   **HUD:** Durante la partita vengono mostrati a schermo punteggio, vite rimaste e tempo di sopravvivenza.
*   **Testi a schermo:** Caricamento di un font (`font.ttf`) per disegnare scritte con `sf::Text`.

<img width="808" height="631" alt="image" src="https://github.com/user-attachments/assets/7a51f281-17f2-4aed-93a3-7648e60158e1" />
<img width="807" height="631" alt="image" src="https://github.com/user-attachments/assets/550b1fd5-3097-4c03-b77b-5cd5a7523c98" />

### Soluzioni tecniche adottate
*   **Nuovo stato `Pause`:** L'enumerazione `GameState` è stata estesa con lo stato di pausa. In pausa la logica di gioco non viene aggiornata, ma la scena continua a essere disegnata sotto il menu.
*   **Pulsanti con effetto hover:** Ogni pulsante è un rettangolo (`sf::RectangleShape`) con un testo centrato sopra. Il clic viene riconosciuto controllando se la posizione del mouse, convertita con `mapPixelToCoords()`, è contenuta nei limiti del rettangolo; quando il cursore ci passa sopra il pulsante cambia colore.
*   **Centratura dei testi:** L'origine di ogni testo viene impostata al centro dei suoi limiti (`getLocalBounds()`), così da poterlo centrare facilmente su pulsanti e schermo.
*   **Misura del tempo:** Il game loop misura il tempo trascorso tra un fotogramma e l'altro (`deltaTime`) con un `sf::Clock`; questo valore viene usato per calcolare il tempo di sopravvivenza mostrato nell'HUD.
*   **Reset della partita:** È stata introdotta la funzione `resetGame()`, che riporta in un unico punto tutte le variabili di gioco ai valori iniziali.
*   **Continuità con l'architettura precedente:** Nonostante l'aggiunta di menu, pausa e HUD, il giocatore continua a essere gestito dalla classe `Player` (movimento, rotazione e limiti dello schermo) e tutti i parametri di gioco restano centralizzati in `Config.hpp`.
*   **Organizzazione in funzioni:** La logica di gioco è suddivisa in funzioni dedicate (`updatePlayer`, `updateBullets`, `spawnEnemy`, `updateEnemies`, `spawnPowerUp`, `updatePowerUps`, `handleCollisions`, `updateEnemyBullets`, `updateVFX`, `applyScreenShake`), che `update()` richiama in sequenza; il costruttore delega il caricamento delle risorse a `loadResources()` e la creazione dell'interfaccia a `setupUI()`.
*   **Funzioni di supporto per l'interfaccia:** I pulsanti vengono creati tutti con la stessa funzione `setupButton()`, i testi vengono centrati con `centerText()` e l'effetto hover è gestito da `updateButtonHover()`; l'avvio della partita, comune al tasto Invio e al pulsante "INIZIA", è raccolto nella funzione `startGame()`.

## Tappa 10: Audio e Difficoltà Progressiva

### Cosa aggiunge o risolve questa tappa
In questa decima e ultima tappa il gioco viene completato con il comparto audio e con una difficoltà che cresce nel tempo.
Nello specifico, questa tappa aggiunge:
*   **Musica di sottofondo:** Una musica (`music.mp3`) parte all'inizio della partita, si ripete in loop, si mette in pausa insieme al gioco e si ferma al Game Over o al ritorno al menu.
*   **Effetti sonori:** Suoni per lo sparo del giocatore e degli Shooter (`shoot.wav`) e per i colpi e le esplosioni (`explosion.wav`), con volumi diversi a seconda dell'evento.
*   **Difficoltà progressiva:** L'intervallo di comparsa dei nemici parte da 1 secondo e diminuisce con il tempo di sopravvivenza, fino a un minimo di 0,3 secondi.
*   **Bilanciamento:** La velocità dei nemici passa da 2 a 2,5 e i power-up compaiono ogni 12 secondi invece che ogni 10.
*   **Schermata di Game Over:** Al termine della partita viene mostrata la scritta "GAME OVER" con il punteggio finale e l'indicazione di premere Invio per tornare al menu.

### Soluzioni tecniche adottate
*   **Musica in streaming:** La musica usa `sf::Music`, che legge il file un poco alla volta durante la riproduzione invece di caricarlo tutto in memoria.
*   **Effetti sonori con buffer condivisi:** I suoni brevi sono caricati una sola volta in `sf::SoundBuffer`. Ogni volta che serve un suono, la funzione `playSound()` crea un nuovo `sf::Sound` collegato al buffer e lo aggiunge a un vettore, così più suoni possono essere riprodotti contemporaneamente.
*   **Pulizia dei suoni (Erase-Remove):** Ad ogni ciclo del game loop i suoni terminati vengono rimossi dal vettore con l'idioma erase-remove (`std::remove_if` seguito da `erase`), evitando che il vettore cresca senza limite.
*   **Testi del Game Over:** Le scritte della schermata finale vengono create una sola volta all'avvio, insieme al resto dell'interfaccia; ad ogni fotogramma viene aggiornato solo il testo del punteggio.
*   **Formula della difficoltà:** L'intervallo di comparsa è calcolato come `max(0,3; 1 - tempo × 0,015)`; il minimo viene quindi raggiunto dopo circa 47 secondi di sopravvivenza.
