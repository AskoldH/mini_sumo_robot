# STM8 Tools

Šablona projektu k vývoji firmwaru pro mikrokontroléry z rodiny STM8S.

## 🧮 Jak to používat, základní info

Následují ukázky často používaných akcí / příkazů.

### Klonování

Příkaz, který naklonuje (stáhne) tento repozitář.

```bash
git clone https://gitlab.com/wykys/stm8-tools.git
```

### Přejmenování

Doporučuji si každý projekt vhodně (nejlépe popisně) pojmenovat. Může to usnadnit život v budoucnu. Při výběru jména se preventivně vyvarujte použití diakritiky. K přejmenování budeme používat příkaz `mv` (__Move__), který slouží k přejmenování, případně přesunu souborů.

```bash
mv stm8-tools blikac
```

### Fígl - klonování s přejmenováním

Stejného výsledku jako s použitím posloupnosti příkazů `git clone` a `mv` lze dosáhnou i tak, že na konec příkazu `git clone` za `URL` repozitáře vložím jak chci, aby se repozitář jmenoval na mém disku.

```
git clone https://gitlab.com/wykys/stm8-tools.git blikac
```

### Změna složky

Příkaz `cd` (__Change Directory__) změní aktuální složku, ve které se nacházíme, za jinou. Tedy nám to umožní pohyb mezi složkami.

```bash
# přejdeme do složky cesta_ke_slozce
cd cesta_ke_slozce
# přejdeme o adresář víš
cd ..
# přejdeme do domovské složky
cd
```

### VS Code

Otevřeme editor VS Code v aktuální složce. __Tečka__ symbolizuje aktuální adresář, můžeme však zadat cestu k libovolné složce nebo souboru.

```bash
code .
```

### Kompilace projektu

Cílem kompilace je vytvořit binární soubor, obsahující náš program, který budeme moci nahrát do mikrokontroléru. Pokud bude kompilace úspěšná, vytvoří se nám složka `build` a v ní soubor `firmware.elf`, který obsahuje náš program. Kompilaci provedeme příkazem `make`.

```bash
make
```

### Nahrání FW do MCU

Následující příkaz provede "flashnutí", tedy ze souboru `build/firmware.elf` zapíše obsah programové paměti pomocí programátoru / debugeru ST-Link do mikrokontroléru.

```bash
make flash
```

### Kompilace s nahráním FW do MCU v jednom

Tento příkaz se chová stejně jako posloupnost příkazů `make` následovaný `make flash`. Může nám tedy ušetřit psaní.

```bash
make build_and_flash
```

## 📎 Doporučený pracovní postup

1. Naklonovat šablonu projektu
2. Přejmenovat šablonu na jméno projektu
3. Přejít do složky s projektem
4. Otevřít projektovou složku ve VS Code
5. Ve VS Code otevřít terminál (ve Win zkontrolovat shell)
6. Ověřit konfiguraci našeptávání `.vscode/c_cpp_properties.json`
7. Začít programovat

```bash
git clone https://gitlab.com/wykys/stm8-tools.git
mv stm8-tools jmeno_projektu
cd jmeno_projektu
code .
```

## 💡 Tipy k VS Code

VS Code je mocný textový editor, který se snadno rozšíří o nové funkce díky rozšířením. Ta se dají instalovat pomocí ikony bedny v postranním panelu.

### Integrovaný terminál

Přímo ve VS Code se dá vytvořit terminál a ten používat ke kompilaci a nahrávání FW. To může ušetřit čas strávený přepínáním mezi okny. Zároveň nám to umožní mít "všechno" v jedné aplikaci. Nový terminál spustíme pomocí klávesové zkratky `Ctrl` + `Shift` + `P`. To vyvolá příkazovou lištu, do které zadáme `Create New Terminal`:

```bash
>Terminal: Create New Terminal
```

⚠️ Pokud se z nějakého záhadného důvodu nacházíte na platformě MS Windows, tak je mi vás líto. V tom případě je třeba přepnout shell terminálu na `Git Bash`. To lze provést pomocí malé rozevírací šipky v pravé části terminálu. Své utrpení můžete zmírnit změnou výchozího shell pro `code` na `bash`. Jak to provést je popsáno v následujícím tipu.

### Nastavení výchozího shellu

Pokud používáte __Win__, tak po spuštění `code` budete mít pravděpodobně nastaven výchozí shell jako `PowerShell` a pokaždé jej budete ručně přepínat na `git-bash`. Naštěstí se snadno dá nastavit výchozí shell. Ve spuštěném `code` stiskněte `Ctrl` + `Shift` + `P` a do příkazového řádku zadejte `select default profile`:

```bash
>Terminal: Select Default Profile
```

Poté si zvolte `bash` jako výchozí shell. V nově otevřeném terminálu již bude spuštěn nově nastavený shell.

### Jak na našeptávání?

Doporučuji nainstalovat si rozšíření C/C++ od firmy Microsoft s podnadpisem _C/C++ IntelliSense, debugging, and code browsing._ Odkaz na [market place](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools).

Toto rozšíření zpřístupní mocnou funkci našeptávání, čímž můžeme rapidně zvýšit produktivitu naší práce i usnadnit hledání chyb.

Aby našeptávání fungovalo korektně, je třeba zkontrolovat soubor `.vscode/c_cpp_properties.json` a případně jej upravit dle používané platformy. Následují ukázky tohoto souboru:

<details>
<summary> Ukázková verze pro Linux </summary>

```json
{
    "configurations": [
        {
            "name": "STM8",
            "includePath": [
                "${workspaceFolder}/**",
                "/opt/sdcc/share/sdcc/include/**",
                "app/inc/**",
                "drivers/inc/**"
            ],
            "defines": [
                "STM8S208",
                "USE_STDPERIPH_DRIVER",
                "_SDCC_"
            ],
            "compilerPath": "/opt/sdcc/bin/sdcc",
            "cStandard": "c99",
            "cppStandard": "c++11",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
}
```

</details>

<details>
<summary> Ukázková verze pro MS Windows </summary>

```json
{
    "configurations": [
        {
            "name": "STM8",
            "includePath": [
                "${workspaceFolder}/**",
                "C:/Program Files/SDCC/include/**",
                "app/inc/**",
                "drivers/inc/**"
            ],
            "defines": [
                "STM8S208",
                "USE_STDPERIPH_DRIVER",
                "_SDCC_"
            ],
            "compilerPath": "C:/ProgramData/chocolatey/bin/gcc.exe",
            "cStandard": "c99",
            "cppStandard": "c++11",
            "intelliSenseMode": "gcc-x64"
        }
    ],
    "version": 4
}

```

</details>

## 🐧 Instalace na Debianu a jeho derivátech

Následuje návod na instalaci toolchainu pro Linuxové distribuce odvozené od Debianu (Ubuntu, Mint, ...). Ubuntu je proslulý balíčkovacím systémem `apt`, který používají i jeho deriváty. Mezi deriváty se mohou některé balíčky lišit v pojmenování, dle konvencí příslušné distribuce.

### Instalace pomocí balíčků

```bash
sudo apt update
sudo apt upgrade
sudo apt install sdcc sdcc-libraries git make openocd
```

### Instalace VS Code

Ve výchozí instalaci systému není repozitář, který by obsahoval balíček `code`. Nejsnadnější cesta je stáhnout si `*.deb` balíček obsahující `code` přímo s [oficiálních stránek](https://code.visualstudio.com/). A ten poté nainstalovat:

```bash
sudo apt install ./cesta_k_balicku_code.deb
```

Po instalaci bude automaticky do systému přidán i repozitář pro aktualizace a certifikát, pro validaci balíčků.

### Kompilace `openocd`

<details>
<summary> Dozvědět se více </summary>

OpenOCD je nástroj, který slouží ke komunikaci s programátory a debugery. V tomhle toolchainu je použit pro flashování FW do MCU.

Pokud byste chtěli používat aktuální verzi tohoto nástroje, je velmi jednoduché si jej zkompilovat ze zdrojových souborů.

Oficiální zrcadlo `git` repozitáře Open OCD je hostován na https://github.com/openocd-org/openocd. Pokud si jej chceme zkompilovat, nejprve si jej naklonujeme:

```bash
git clone https://github.com/openocd-org/openocd.git
```

Nejprve přejdeme do složky s `openocd`:

```bash
cd openocd
```

Poté můžeme zahájit kompilaci. Nejprve pomocí příkazu `./bootstrap` stáhneme závislosti a cygeneruje `./configure`.

```bash
./bootstrap
```

Příkaz `./configure` zkontroluje závislosti a vygeneruje `Makefile`. Můžeme mu explicitně říci, které zařízení budeme potřebovat a podle toho se upraví `Makefile`. Pokud bychom chtěli získat přehled konfiguračních možností, můžeme použít příkaz `./configure --help`.

```bash
./configure --enable-stlink --enable-ft232r --enable-ftdi
```

Poté již můžeme zahájit kompilaci.

```bash
make
```

Po kompilaci nainstalujeme vytvořené soubory do systému.

```bash
sudo make install
```

</details>

## 💩 Instalace na MS Windows

V této části bude popsána instalace všech programů pro korektní funkci toolchainu na MS Windows. Vřele doporučuji k instalaci využít správce balíčků https://chocolatey.org/, ten obsahuje vše, co potřebujeme, krom kompilátoru SDCC.

### Instalace Chocolatey

Doporučuji použít oficiální postup, který byl v době psaní tohoto manuálu následující:

Spustit Windows PowerShell jako administrátor systému a do příkazové řádky zadat tento příkaz, který nainstaluje Chocolatey:

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

Po  úspěšné instalaci bude v systému dostupný příkaz `choco`. Díky němu můžeme nainstalovat většinu potřebného SW.

### Instalace dostupného SW pomocí správce balíčků Chocolatey

Do administrátorského PowerShellu zadat tyto příkazy:

```powershell
choco install git make openocd vscode mingw
```

> Balíček `git` obsahuje i `bash`.

> Balíček `mingw` obsahuje kompilátor `gcc`, jenž je využit při našeptávání.

### Instalace kompilátoru SDCC

Nakonec je třeba stáhnout a nainstalovat kompilátor `SDCC`, který sídlí na adrese http://sdcc.sourceforge.net/. Instalace probíhá prostřednictvím klasického klikacího formuláře.



## ❗ Něco po instalaci nefunguje?

Pokud jste pečlivě dodržovali návod a a přesto něco nefunguje, možná v této sekci naleznete řešení vašeho problému.

### Nefunguje komunikace s MCU přes `openocd`?

V tom případě jsem zatím odhalil následující možné příčiny chyb:

1. Máte nevhodný USB kabel. Možná je pouze napájecí, nebo příliš dlouhý či polámaný. Nejlepší variantou je krátký stíněný kabel.

2. Máte v počítači poškozený USB port, zkuste použít jiný.

3. Pokud používáte __Win__, je možné že vám v systému bude chybět vhodný ovladač USB, který `openocd` potřebuje ke komunikaci. Nejsnadnější cesta jak jej nainstalovat je prostřednictvím utility [Zadig](https://zadig.akeo.ie/). Při instalaci vyberte připojený programátor (ST-Link) a cílový ovladač nastavte na `libusbK`. Poté potvrďte instalaci ovladače a vyčkejte na jeho nainstalování. Pro zavedení nového ovladače je nutné zařízení od USB odpojit a opět připojit.

4. Zkuste si naklonovat nejnovější verzi, i tento repozitář se občas vyvíjí a přidává nové funkce a opravuje chyby...
