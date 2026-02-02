*This project has been created as part of the 42 curriculum by lciardo.*

# GET_NEXT_LINE

## 📋 DESCRIZIONE

Il progetto **GET_NEXT_LINE** ha come obiettivo l'implementazione di una funzione in linguaggio C capace di leggere il contenuto di un file **una riga alla volta**.

La funzione `get_next_line()` consente di leggere sequenzialmente uno stream di dati da un **file descriptor (FD)**, restituendo a ogni chiamata la riga successiva, incluso il carattere newline (`\n`) se presente. Questo progetto affronta sfide fondamentali della programmazione C, tra cui:

*	**GESTIONE DELLA MEMORIA DINAMICA:** Allocazione e liberazione precisa dei buffer per evitare ogni tipo di **memory leak**.
*	**VARIABILI STATICHE:** Utilizzo strategico di variabili `static` per preservare i dati letti tra una chiamata e l'altra.
*	**BUFFER DI LETTURA:** Capacità di gestire una dimensione del buffer (`BUFFER_SIZE`) arbitraria definita solo al momento della compilazione.

### 🌟 PARTE BONUS
La versione bonus del progetto permette di gestire **PIÙ FILE DESCRIPTOR CONTEMPORANEAMENTE**. È possibile alternare la lettura tra file diversi (ad esempio: Leggi riga 1 di File A -> Leggi riga 1 di File B -> Leggi riga 2 di File A) senza perdere il progresso o mischiare i dati.

---

## 🛠️ INSTRUCTIONS (ISTRUZIONI)

### 1. PREREQUISITI
È necessario un compilatore C (come `cc`, `gcc` o `clang`) e le librerie standard.

### 2. COMPILAZIONE
Il progetto non genera un eseguibile proprio, ma i file sorgenti devono essere compilati insieme al tuo programma principale. È **obbligatorio** definire la macro `BUFFER_SIZE`.

**Esempio di compilazione (Versione Standard):**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

---

## 📚 RESOURCES (RISORSE)

### 1. RIFERIMENTI CLASSICI
*	**42 SUBJECT:** Manuale ufficiale del progetto e linee guida fornite dalla **SCUOLA 42**.

### 2. UTILIZZO DELL'IA
L'intelligenza artificiale è stata utilizzata come supporto teorico e revisionale durante lo sviluppo nelle seguenti attività:

*	**SPIEGAZIONE CONCETTUALE:** Approfondimento tecnico sul funzionamento e sulla persistenza delle **VARIABILI STATICHE** tra diverse chiamate di funzione.
*	**ANALISI DEGLI EDGE CASES:** Identificazione e gestione di scenari critici come **FILE VUOTI**, file senza **NEWLINE** finale o letture che terminano esattamente al limite del **BUFFER_SIZE**.

## 🧠 ALGORITMO E LOGICA

L'algoritmo si basa sull'utilizzo di una **VARIABILE STATICA** per conservare i dati letti che superano il carattere newline, garantendo continuità tra le chiamate.

### 1. IL FLUSSO IN BREVE
* **LETTURA:** Si legge dal file descriptor in blocchi di dimensione **BUFFER_SIZE** finché non si trova un `\n` o si raggiunge la fine del file (**EOF**).
* **ACCUMULO:** I dati letti vengono uniti allo **STASH** (la variabile statica).
* **ESTRAZIONE:** Si isola la stringa fino al primo `\n` per restituirla come **LINEA**.
* **PULIZIA:** Si aggiorna lo **STASH** mantenendo solo i caratteri rimasti dopo il `\n`.



### 2. GIUSTIFICAZIONE DELLA SCELTA
* **PERSISTENZA:** L'uso della memoria **STATICA** è indispensabile per non perdere i dati letti in eccesso tra una chiamata e l'altra.
* **EFFICIENZA:** L'algoritmo gestisce dinamicamente qualsiasi **BUFFER_SIZE**, ottimizzando il numero di letture (`read`) necessarie.
* **SICUREZZA:** La struttura permette un controllo granulare della memoria (malloc/free), riducendo drasticamente il rischio di **MEMORY LEAKS**.
