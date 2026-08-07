# Der ultimative OpenRGB Autostart-Trick (Windows)

Wenn man in OpenRGB den normalen Haken bei **"Enable Start at Login"** setzt, erstellt das Programm eine Verknüpfung im Windows-Autostartordner. Das funktioniert zwar zuverlässig, hat aber einen entscheidenden Nachteil: Windows bremst diesen Ordner beim Hochfahren absichtlich aus. Es dauert oft mehrere Sekunden, bis das Programm nach dem Anmelden wirklich startet und die Hardware-Farben umschaltet.

Um diese künstliche Windows-Verzögerung zu umgehen, nutzen wir die **Windows-Aufgabenplanung (Task Scheduler)**. Damit lässt sich OpenRGB zwingen, *sofort* beim Login und mit höchsten Rechten zu feuern.

---

## Schritt-für-Schritt Anleitung

### 1. Alten Autostart deaktivieren
Zuerst muss der langsame, normale Autostart deaktiviert werden, damit OpenRGB nicht versehentlich doppelt geöffnet wird.
1. Öffne OpenRGB und wechsle in die **Settings**.
2. Klappe das Menü **Start at Login** auf.
3. **Entferne** den Haken bei `Enable Start at Login`. (Den Haken bei `Start Minimized` kannst du drin lassen, er wird aber durch unser Script ohnehin übersteuert).
4. Speichere die Einstellungen und schließe OpenRGB.

### 2. Windows-Aufgabenplanung öffnen
1. Drücke die Windows-Taste, tippe **Aufgabenplanung** (oder `Task Scheduler`) ein und drücke Enter.
2. Klicke auf der rechten Seite auf **"Aufgabe erstellen..."** (nicht auf "Einfache Aufgabe erstellen").

### 3. Reiter: Allgemein
In diesem Reiter konfigurieren wir die Grunddaten und Rechte.
- **Name:** Trage hier z. B. `OpenRGB-Autostart-Turbo` ein.
- **Sicherheitsoptionen:** Wähle die Option **"Nur ausführen, wenn der Benutzer angemeldet ist"**.
- **WICHTIG:** Setze unten den Haken bei **"Mit höchsten Privilegien ausführen"** (Run with highest privileges). Das gibt OpenRGB direkte Administrator-Rechte, um sofort und ohne Verzögerung auf USB-Geräte zuzugreifen.

### 4. Reiter: Trigger (Auslöser)
Hier sagen wir Windows, *wann* das Programm gestartet werden soll.
1. Klicke auf **"Neu..."**.
2. Wähle oben im Dropdown-Menü: **"Bei Anmeldung"** (At log on).
3. Stelle sicher, dass bei Einstellungen **"Jeder Benutzer"** oder dein spezifischer Benutzerkonto-Name ausgewählt ist.
4. Klicke auf **OK**.

### 5. Reiter: Aktionen
Hier sagen wir Windows, *welches* Programm gestartet werden soll.
1. Klicke auf **"Neu..."**.
2. Aktion: **Programm starten**.
3. **Programm/Skript:** Klicke auf "Durchsuchen" und wähle die `OpenRGB.exe` aus. (In unserem Fall liegt sie unter `"C:\Program Files\OpenRGB-Custom\OpenRGB.exe"`).
4. **Argumente hinzufügen:** Trage hier `--startminimized` ein. *(Dadurch startet das Programm leise im Hintergrund und legt sich sofort unsichtbar neben die Uhr, anstatt ein nerviges Fenster aufploppen zu lassen).*
5. Klicke auf **OK**.

### 6. Reiter: Bedingungen & Einstellungen (Wichtig für Laptops)
Damit die Aufgabe nicht ungewollt abgebrochen wird, sollten wir noch ein paar Schutzmechanismen anpassen:
- **Bedingungen:** Entferne den Haken bei *"Aufgabe nur starten, falls Computer im Netzbetrieb ausgeführt wird"*. (Sonst startet OpenRGB auf Laptops nicht, wenn sie im Akkubetrieb hochfahren!)
- **Einstellungen:** Entferne den Haken bei *"Aufgabe beenden, falls sie länger ausgeführt wird als: 3 Tage"*.

### 7. Speichern
Klicke abschließend auf **OK**. Deine neue Aufgabe ist nun aktiv!

---

## Das Resultat
Sobald du den PC das nächste Mal neu startest und dein Passwort eingibst, wird Windows OpenRGB an der langsamen Warteschlange vorbeischleusen. Da es mit Administrator-Rechten ausgestattet ist, schießt es den Farbcode direkt an die Maus – du bist fertig, bevor der Desktop überhaupt komplett sichtbar ist!

> [!TIP]
> Vergiss nicht, in OpenRGB unter *Settings -> Supported Devices* alle Geräte-Suchen per Klick auf **"Disable All"** auszuschalten, die du gar nicht besitzt (und nur deine Maus aktiviert zu lassen). Dadurch spart sich OpenRGB beim Starten zusätzlich noch das Durchsuchen des gesamten PCs und ist fast in Echtzeit fertig!
