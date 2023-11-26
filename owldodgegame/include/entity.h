#ifndef ENTITY_H
#define ENTITY_H
/*
 * @file entity.h
 * @brief A játékban az entitások/játékosképességek létrehozásáért, mozgásáért
 * és felszabadításáért felelős modul Itt vannak definiálva az entitásokhoz
 * köthető struktúrák Egyes függvények visszatérési értékének a felszabadítása a
 * hívóra van bízva, de a felszabadításért vannak segédfüggvények ebben a
 * modulban Ha entitást mozgat, akkor kommunikál a render modullal és felel
 * azért, hogy megjelenjen a mozgás a képernyőn
 * a game modul által használt frissítés gyakoriságától függnek az egyes időhöz
 * kötött értékek
 */

#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "../lib/debugmalloc.h"

#include "math_helper.h"
#include "render.h"
#include "scoreboard.h"
#include "state.h"
/**
 * @struct Cooldown
 * @brief A töltési idő kezeléséhez szükséges adatokat tárolja
 */
typedef struct Cooldown {
  const double cd; /**< Az az idő amely két képesség használat között el
                            kell teljen (másodperc) */
  double
      cdcounter; /**< ez az adat számol vissza a cooldown értékéről nulláig  */
  bool oncd; /**< azt tartja számon, hogy töltési időn van-e a képesség, ha igen
                akkor nem használhatja a képességet a játékos */
} Cooldown;
/**
 * @struct Spell
 * @brief A játékos egy képességhez tartozó tulajdonságokat tároló struktúra
 * Egy képességhez közösen tartozó tulajdonságokat tárol, tehát több képesség
 * esetén ezek a tulajdonságokat érvényesek mindegyikre
 */
typedef struct Spell {
  Cooldown cooldown;
  const double range; /**< A képesség hatótávja */

  double speed; /**< A képesség sebességét tárolja */

  SDL_Texture *texture; /**< a képesség textúrájára mutató pointer */
  Size imgsize;         /**< A megjelenítendő kép méretét tárolja */
} Spell;

/**
 * @struct Missile
 * @brief A játékos egy képességét, a lövedéket tároló struktúra
 * Egy adott lövedék tulajdonságait tárolja
 */

typedef struct Missile {
  Point position;    /**< A lövedék pozíciója */
  Vector2 direction; /**< A lövedék iránya normalizált vektor alakban */

  double angle; /**< A lövedék képét milyen szögben kell elforgatni (az x
                   tengelytől jobbra lefele pozitív) */
  double distancetraveled; /**< A megtett távolságát tárolja, mert ha eléri a
                              hatótávját akkor megsemmisül */
} Missile;

/**
 * @struct MissileNode
 * @brief A lövedékeket tároló láncolt lista egy elemét leíró struktúra
 */
typedef struct MissileNode {
  Missile missile;          /**< maga a lövedék adatai */
  struct MissileNode *next; /**< a következő lövedékelemre mutató pointer*/
} MissileNode;

typedef struct GameOjbect {
  Point position;    /**< Az objetkum pozíciója */
  Vector2 direction; /**< Az objetkum iránya ahova tart, 1 hosszúságú vektor*/

  int hitboxradius; /**< Az objetkum köré rajzolt kör sugarának nagysága.
                       Ütközésvizsgálat esetén ez számít az objektum
                       körvonalának */
  double speed;     /**< A objetkum sebessége */

  Size imgsize;         /**< A objetkum képének nagysága */
  SDL_Texture *texture; /**< A objetkum textúrájára mutató pointer */
} GameObject;

/**
 * @struct Player
 * @brief A játékost és az ahhoz tartozó összes adatot tároló struktúra
 */

typedef struct Player {
  GameObject character; /**< a játékos alapadait tartalmazza*/
  Point destination;    /**< Az a pont ahova a játékos tart */

  Spell flash;        /**< A játékos villanás képessége */
  Spell missileprops; /**< A játékos lövedék képességéhez tartozó adatok,
                         amelyek mindegyik lövedékre egyaránt érvényesek */
  MissileNode *missiles; /**< A játékos lövedékeinek láncolt listája */
} Player;

/**
 * @struct Entity
 * @brief Az egyes ellenségek vagy tűzgolyók adatainak tárolására levő struktúra
 */

typedef struct EntityNode {
  GameObject entity;       /**< az entitás alapadatait tartalmazza*/
  bool followplayer;       /**< Ez a változó tartalmazza, hogy minden egyes
                              mozgatásnál a játékos irányába mozogjon, vagy ne*/
  struct EntityNode *next; /**< A következő entitáselemre mutató pointer*/
} EntityNode;

/**
 * @struct SpawnProps
 * @brief Az egyes entitások létrehozásának tulajdonságait tároló struktúra
 * Előírja, hogy milyen körülmények között jönnek létre ezek az entitások
 */
typedef struct SpawnProps {
  int rate; /**< Az a mérték, hogy milyen gyorsan jönnek létre az entitások
               (frissítés gyakorisága ms-ben * rate = milyen gyakran jönnek
               létre entitások)*/
  int lowerlimit; /**< Az alsó határa annak, hogy milyen gyorsan jönnek létre
                     entitások*/
  int counter; /**< Minden frissítési ciklusban itt tárolódik, hogy hol tartunk,
                  mindig az incrementer értékével növekszik*/
  int incrementer; /**< Ezt a változót adódik hozzá a counter-hez, az érték
                      növelésével lehet gyorsítani az entitások létrehozását*/
  double initspeed; /**< az alap sebessége egy entitásnak amikor létrejön*/
} SpawnProps;
/**
 * @brief A játékos mozgatását végző függvény
 * Frissíti a játékos pozícióját a sebessége és az iránya alapján, emellett a
 * render modul segítségével kirajzoltatja az új pozíción lévő karaktert
 * @param player a játékos struktúrára mutató pointer
 */
void moveplayer(Player *player);
/**
 * @brief végrehajta a villanás képességet
 * Az egér irányába, egy bizonyos távolságon belülre teleportálja a karaktert
 * @param player structra mutató pointer
 */
void playerflash(Player *player);

/**
 * @brief
 *
 * @param entities entitásokat tartalmazó láncolt lista
 * @param rotatedimage el legyen-e forgatva a megjelenített kép?
 * @return EntityNode* a láncolt lista elejére mutató pointert adja vissza (el
 * kell tárolni az értékét, és felszabadítani később a hívónak)
 */
EntityNode *moveentities(EntityNode *entities, bool rotatedimage);
/**
 * @brief Megváltoztatja az összes entitás irányát a játékos irányába
 *
 * @param entities a láncolt lista elejére mutató pointert adja vissza (el
 * kell tárolni az értékét, és felszabadítani később a hívónak)
 * @param playerpos a játékos karakterének jelenlegi pozíciója
 */
void entitychangedir(EntityNode *entities, Point playerpos);
/**
 * @brief létrehoz egy új entitást a megadott tulajdonságok alapján egy
 * véletlenszerűen generált pozícióba. Az entitás a játékos irányába indul el.
 * Ezt az entitást hozzáfűzi az entitásokat tartalmazó láncolt lista elejére
 * @param list
 * @param playerpos a játékos
 * @param *props az új entitás alaptulajdonságait tartalmazó gameobject, a
 * következő változókat kell benne definiálni: speed, texture, imgsize,
 * hitboxradius
 * @return EntityNode* a láncolt lista elejére mutató pointert adja vissza (el
 * kell tárolni az értékét, és felszabadítani később a hívónak)
 */
EntityNode *spawnentity(EntityNode *list, Point playerpos, GameObject props);
/**
 * @brief frissíti a képesség töltési idejét a megadott milliszekundumot
 * figyelembe véve
 *
 * @param spell a játékos képességére mutató pointer
 * @param ms az a miliszekundumérték, amely közönként lefut a userevent
 */
void updatespellcooldown(Spell *spell, int ms);
/**
 * @brief Felszabadítja az entitások tartalmazó láncolt listát
 *
 * @param entities a felszabadítandó lista elejére mutató pointer
 */
void freeentities(EntityNode *entities);

/**
 * @brief létrehoz egy lövedéket
 * A kezdőpozíciója a lövedéknek a játékos, és az egér irányába indul el
 * @param player a játékosra mutató pointer (inicializálni kell a lövedékek
 * listát)
 * @return MissileNode* a láncolt lista elejére mutató pointert adja vissza (el
 * kell tárolni az értékét, és felszabadítani később a hívónak)
 */
MissileNode *spawnmissile(Player *player);
/**
 * @brief mozgatja a lövedékeket
 * Mozgatja a lövedékeket, és ha megtették a maximálisan megtehető útat, akkor
 * felszabadítja és kitörli őket a listából
 * @param player a játékosra mutató pointer
 * @return MissileNode* a láncolt lista elejére mutató pointert adja vissza (el
 * kell tárolni az értékét, és felszabadítani később a hívónak)
 */
MissileNode *movemissiles(Player *player);
/**
 * @brief felszabadítja a lövedékeket
 *
 * @param player a játékosra mutató pointer (inicializálni kell a lövedékek
 * listát)
 */
void freemissiles(Player *player);

/**
 * @brief Megnézi, hogy a játékos ütközött-e valamilyen entitással
 *
 * @param player a játékosra mutató pointer
 * @param entities az entitás láncolt listára mutató pointer
 * @return boolean igaz értékkel tér vissza, ha ütközött egy entitással, és
 * hamis értékkel, ha egyikkel sem ütközött
 */
bool checkcollisioncircles(Player *player, EntityNode *entities);
/**
 * @brief Megnézi, hogy ütköztek-e a játékos lövedékei az entitásokkal
 * ha ütköztek, akkor az adott lövedék és entitás megsemmisíti egymást, tehát
 * felszabadítódnak és kitörlődnek a láncolt listájukból
 * @param player a játékosra mutató pointer
 * @param enemies az entitás láncolt listára mutató pointer
 */
void checkcollisionmissileenemy(Player *player, EntityNode **enemies);

/**
 * @brief Ez a függvény beállítja, hogy milyen sebessége legyen egyes nehézségi
 * fokozatok mellett a spawnprops struktúrának
 *
 * @param p az adott spawnprops struktúrára mutató pointer, amelynek a sebesség
 * változója fog megváltozni
 * @param basespeed az alapsebességérték
 */
void setspeedbydiff(SpawnProps *p, double basespeed);
/**
 * @brief frissíti az adott spawnprops struktúra számlálóját
 * ha a számláló elérte a rate (gyakoriság) változó értékét, akkor alaphelyzetbe
 * állítja a számlálót, és a rate változót csökkenti egyel az előbbi esetben,
 * mivel a számláló elérte a kívánt értéket, ezért igazzal tér vissza, vagyis
 * létre lehet hozni egy új entitást
 * @param p a spawnprops struktúrára mutató pointer
 * @return boolean ha a számláló elszámolt a rate változóig, akkor igazzal tér
 * vissza, ha még nem akkor hamissal
 */
bool updatespawnprops(SpawnProps *p);
#endif