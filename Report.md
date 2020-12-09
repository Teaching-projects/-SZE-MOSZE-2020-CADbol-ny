# Tagok

| Név | Github azonosito  | Javasolt relatív érdemjegy | Becsült óra | Indoklás  | 
| --- | ---- | --- | ------------------ | --------- |
| Sótonyi Áron | @tupoljev | 0 | 20-30 | Lelkiismeretesen végezte a dolgát, bármi kérdése akadt @dobaybalazs -hoz fordult. |
| Dobay Balázs | @dobaybalazs | +1 | 50-60 | Mindent megcsinált, bárkinek kérdése volt szívesen segített. |
| Szita Tamás | @Medivessing | -1 | 20-30 | A tárgyon oktatott eszközöket elsajátította, de a programozási részeknél többször kért segítséget. |


# Videók

 - [Gameplay](/videos/gameplay.mp4)
 - [CodeBaseDefense](/videos/codebasedefense.mp4)

# Befejezett feladatok

| Feladat | Merge ideje a határidóhöz (nap) | Change request körök | Reviewer | 
| ------- | ------------------------------- | -------------------- | -------- |
| Feladat 1 | +3 | 3 | @vizvezetek | 
| Feladat 2 | +4 | 2 | @oliverosz |
| jsonparser | +8 | 1 | @wajzy |
| levelup | +12 | 1 | @oliverosz |
| attackspeed | +1 | 1 | @vizvezetek |
| documentation | -1 | 0 | @GitCraft / @Patorik @ztamas97 |
| unittest | -1 | 0| @GitCraft / @Patorik @ztamas97 |
| makefile | 0 | 1 | @hegyhati |
| refactor | +7 | 0 | @tupoljev |
| docker | 0 | 0 | @tupoljev |
| jsonpimp | Merge: 11.18 | 1 | @tupoljev @Medivessing |
| map | Merge: 11.29 | 0 | @Medivessing  @tupoljev |
| game | Merge: 11.29 | 0 | @Medivessing  @tupoljev |
| defense | Merge: 11.29 | 0 | @Medivessing  @tupoljev |
| damage | Merge: 11.29 | 0 | @Medivessing |
| markedmap | Merge: 12.07 | 0 | @Medivessing |
| preparedgame | Merge: 12.07  | 0 | @Medivessing |
| light radius | Merge: 12.07  | 0 | @Medivessing |
| rendering | Merge: 12.07  | 0 |  @tupoljev |

# Unit tesztek

| Osztály | Publikus metódusok száma | Unit tesztelt metódusok száma | Unit tesztek száma |
| --- | --- | --- | --- |
| `Unit` | 14 | 14 | 9 |
| `Hero` | 9 | 9 | 9 | 
| `Monster` | 3 | 3 | 9 |
| `JSON` | 6 | 6 | 7 | 
| `Map` | 8 | 8 | 6 |  
| `MarkedMap` | 2 | 2 | 2 |  
| `Game` | 16 | 16 | 5 |  
| `PreparedGame` | 1 | 1 | 1 | 
| `Renderer` | 2 | 2 | 1 |  
| `SVGRenderer` | 1 | 1 | 1 |  
| `Exceptions` | 8 | 8 | 8 | 

# Kód dokumentáció

| Teljesen dokumentált osztályok | Részben dokumentált osztályok | Nem dokumentált osztályok |
| --- | --- | --- | 
| `Unit` | --- | --- | 
| `Hero` | --- | --- |  
| `JSON` | --- | --- |
| `Monster` | --- | --- |
| `Game` | --- | --- |
| `PreparedGame` | --- | --- |
| `Map` | --- | --- |
| `MarkedMap` | --- | --- |
| `Renderer` | --- | --- |
| `SVGRenderer` | --- | --- |


# Mindenféle számok

 - Összes cpp kódsor : 1201
 - Egyéb kódsor (make,doxyfile,shellscript, ...) : 167
 - cppcheck
   - warning : 0
   - style : 1 (preparedgamenél 0)
   - performance : 0
   - unusedFunction :  8 (sima gamenél: 4)
   - missingInclude :  0
 
# Implicit megtanult dolgok
Olyanok, amik nem a tárgy anyaga, de muszáj/hasznos volt elsajátítani:
 - alapvető shell/python scripting
 - `std::variant` JSON parsernél
 - `std::any_of` cppcheck ajánlására
 - `std::count_if` cppcheck ajánlására
 - `std::any` JSON parser első verziójában
 - Operációsrendszerek közti fájlkezelési/sorvégi karakter különbségek :)
 - `std::enable_if` JSON parser második verziójában
 - `std::is_same` JSON parser második verziójában
 - `std::copy` refactor main.cpp, JSON parser
 - SVG fájlok alapvető funkciója,működése

# Feedback (optional)
 
Melyik részt találtátok a leghasznosabbnak, miért. Használtátok-e az itt megszerzett dolgokat esetleg közben máskor. Volt-e olyan, amit hiányoltatok a tárgyból. Utólag visszagondolva is jó volt-e az online videósdi?

Minden megismert eszközt hasznosnak találunk, talán ami kiemelkedik az magának a github használatának megismerése mert azóta többször is hasznunkra vált, egyetemhez köthető projekteken kívül is. De a többi eszköz is a projekt készítése során kifejezetten hasznosnak bizonyult és meglehetősen felgyorsították a tesztelési illetve debuggolási folyamatokat. 

A dolgok amik leginkább lassították a feladatok teljesítését inkább voltak programozáshoz köthetőek, mint sem a megtanult eszközökhöz és bár ezek is nagyon sok jó tapasztalattal gazdagítottak minket, viszont nagyon időigényesek voltak ami kicsit besűrűsítette az elmúlt pár hónapunkat. 

A tárgynál kifejezetten előnyös volt, hogy az oktatott anyag online videók formájában is elérhető volt, sokat segített az eszközök megértésében.

# Üzenet a jövőbe (optional)

Így, hogy túlvagytok rajta, mi az, aminek örültetek volna, ha első héten elmondom, avagy: jövőre mit lenne jó, ha elmondanék majd?

Mindenképpen előnyösnek tartanánk ha tantárgyi követelmények közt meg lenne említve, hogy milyen mélységű programozási ismeretek szükségesek a dolgok gördülékeny haladásához ha ez nincs megtéve(mi nem találtuk).