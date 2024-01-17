#include <unistd.h>
#include <ncurses.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

#include "io.h"
#include "character.h"
#include "poke327.h"
#include "pokemon.h"


bool gameOver = false;
bool gameOver2 = false;
int pokeballs = 3; 
int potion = 3;
int revive_potion = 3; 
typedef struct io_message {
  /* Will print " --more-- " at end of line when another message follows. *
   * Leave 10 extra spaces for that.                                      */
  char msg[71];
  struct io_message *next;
} io_message_t;

static io_message_t *io_head, *io_tail;

void swap_poke(pokemon &a, pokemon &b) {
    pokemon temp = a;
    a = b;
    b = temp;
}

void stats(pokemon * npc_poke){
  clear();
  printw("                          Battle information\n");
  printw("YOUR POKEMON:\n");

  printw("HP: %d    | ATK: %d    | DEF: %d | SPEED: %d | SP_ATK: %d | SP_DEF: %d",
  world.pc.buddy[0]->hp, world.pc.buddy[0]->get_atk(), world.pc.buddy[0]->get_def(),world.pc.buddy[0]->get_speed(), 
  world.pc.buddy[0]->get_spatk(), world.pc.buddy[0]->get_spdef());
  printw("\n");

  printw("move 1: %s   move 2: %s", world.pc.buddy[0]->get_move(0), world.pc.buddy[0]->get_move(1));

  printw("\n\n");

  if(npc_poke->hp < 0){
    npc_poke->hp = 0; 
  }

  printw("ENEMY POKEMON:\n");
  printw("HP: %d    | ATK: %d    | DEF: %d | SPEED: %d | SP_ATK: %d | SP_DEF: %d",
  npc_poke->hp, npc_poke->get_atk(), npc_poke->get_def(),npc_poke->get_speed(), 
  npc_poke->get_spatk(), npc_poke->get_spdef());
  printw("\n");

  printw("move 1: %s   move 2: %s", npc_poke->get_move(0), npc_poke->get_move(1));
  printw("\n\n");
}

void movesInfo(pokemon * pcPoke){
  printw("               Please choose your move\n\n");
  printw("Moves of %s: \n", pcPoke->get_species());
  printw("Move 1: %s | Move 2: %s \n", pcPoke->get_move(0), pcPoke->get_move(1));
}

void options(){
  printw("\n");
  printw("                   CHOOSE ONE OPTION\n");
  printw("               1.Fight!             2.Bag\n");
  printw("               3.Run :(             4.Pokemon\n"); 
}

void revive_poke(){
  clear();

  printw("Oh no!, what happened?\n");
  printw("What pokemon do you want to revive?\n");

  if(revive_potion == 0){
    printw("Sorry you dont have enough revive potion, please go to a PokeMart or PokeCenter\n");
    getch();
    return;
  }
  for(int i = 0; i < world.pc.size; i++){
    printw("Press %d to revive %s | HP: %d\n\n", i+1, world.pc.buddy[i]->get_species(), world.pc.buddy[i]->hp);
  }

  char ch = getch();
  if(ch == '1'){
     world.pc.buddy[0]->hp = world.pc.buddy[0]->get_hp();
    printw("Cool your pokemon is full hp : %d\n",world.pc.buddy[0]->hp);
    world.pc.buddy[0]->isDead = false;
  }else if(ch == '2'){
     world.pc.buddy[1]->hp = world.pc.buddy[1]->get_hp();
      printw("Cool your pokemon is full hp : %d\n",world.pc.buddy[1]->hp);
      world.pc.buddy[1]->isDead = false;
  }else if(ch == '3'){
     world.pc.buddy[2]->hp = world.pc.buddy[2]->get_hp();
      printw("Cool your pokemon is full hp : %d\n",world.pc.buddy[2]->hp);
      world.pc.buddy[2]->isDead = false;
  }else if(ch =='4'){
     world.pc.buddy[3]->hp = world.pc.buddy[3]->get_hp();
      printw("Cool your pokemon is full hp : %d\n",world.pc.buddy[3]->hp);
      world.pc.buddy[3]->isDead = false;
  }else if(ch =='5'){
     world.pc.buddy[4]->hp = world.pc.buddy[4]->get_hp();
      printw("Cool your pokemon is full hp : %d\n",world.pc.buddy[4]->hp);
      world.pc.buddy[4]->isDead = false;
  }else if(ch =='6'){
      world.pc.buddy[5]->hp = world.pc.buddy[5]->get_hp();
      printw("Cool your pokemon is full hp : %d\n",world.pc.buddy[5]->hp);
      world.pc.buddy[5]->isDead = false;
  }

  revive_potion--;
}

void potions(){
  clear();

  printw("Oh no!, what happened?\n");
  printw("What pokemon do you want to use a potion on?\n");

  if(potion == 0){
    printw("Sorry you dont have any potions, please go to a PokeMart\n");
    getch();
    return;
  }

  for(int i = 0; i < world.pc.size; i++){
    printw("Press %d to revive %s | HP: %d\n\n", i+1, world.pc.buddy[i]->get_species(), world.pc.buddy[i]->hp);
  }

 char ch = getch();
  if(ch == '1'){
    world.pc.buddy[0]->hp = world.pc.buddy[0]->hp + 20;
    if(world.pc.buddy[0]->hp > world.pc.buddy[0]->get_hp()){
       world.pc.buddy[0]->hp = world.pc.buddy[0]->get_hp();    
    }
      printw("Cool your pokemon gain +20 hp: %d\n",world.pc.buddy[0]->hp);
    world.pc.buddy[0]->isDead = false;
  }else if(ch == '2'){
     world.pc.buddy[1]->hp = world.pc.buddy[1]->hp + 20;
    if(world.pc.buddy[0]->hp > world.pc.buddy[0]->get_hp()){
       world.pc.buddy[0]->hp = world.pc.buddy[0]->get_hp();    
    }
      printw("Cool your pokemon gain +20 hp: %d\n ",world.pc.buddy[1]->hp);
      world.pc.buddy[0]->isDead = false;
  }else if(ch == '3'){
     world.pc.buddy[2]->hp = world.pc.buddy[2]->hp + 20;
    if(world.pc.buddy[0]->hp > world.pc.buddy[0]->get_hp()){
       world.pc.buddy[0]->hp = world.pc.buddy[0]->get_hp();    
    }
      printw("Cool your pokemon gain +20 hp: %d\n ",world.pc.buddy[2]->hp);
      world.pc.buddy[0]->isDead = false;
  }else if(ch =='4'){
     world.pc.buddy[3]->hp = world.pc.buddy[3]->hp + 20;
    if(world.pc.buddy[0]->hp > world.pc.buddy[0]->get_hp()){
       world.pc.buddy[0]->hp = world.pc.buddy[0]->get_hp();    
    }
      printw("Cool your pokemon gain +20 hp: %d\n ",world.pc.buddy[3]->hp);
      world.pc.buddy[0]->isDead = false;
  }else if(ch =='5'){
     world.pc.buddy[4]->hp = world.pc.buddy[4]->hp + 20;
    if(world.pc.buddy[0]->hp > world.pc.buddy[0]->get_hp()){
       world.pc.buddy[0]->hp = world.pc.buddy[0]->get_hp();    
    }
      printw("Cool your pokemon gain +20 hp: %d\n ",world.pc.buddy[4]->hp);
      world.pc.buddy[0]->isDead = false;
  }else if(ch =='6'){
      world.pc.buddy[5]->hp = world.pc.buddy[5]->hp + 20;
      if(world.pc.buddy[0]->hp > world.pc.buddy[0]->get_hp()){
       world.pc.buddy[0]->hp = world.pc.buddy[0]->get_hp();    
    }
      printw("Cool your pokemon gain +20 hp: %d\n ",world.pc.buddy[5]->hp);
      world.pc.buddy[0]->isDead = false;
  }

  potion--;
}

void bag(){
  clear();
  printw("1.Revive: %d   |    2.Potions: %d   |    3.Exit\n",revive_potion, potion);
  char ch = getch();
  if(ch =='1'){
   revive_poke();
  }else if(ch == '2'){
   potions();
  }
  else if(ch == '3'){
    return;
  }
}

void change_pc_poke(){
  clear();

  if(world.pc.size == 1){
    printw("Sorry you only have one pokemon, you cannot change pokemon\n");
    getch();
    return;
  }
  printw("Choose the pokemon you want to change | Press 1 - %d\n", world.pc.size - 1);

  for(int i = 1; i < world.pc.size; i++){
  printw("Pokemon %d: %s\n", i, world.pc.buddy[i]->get_species());
  printw("HP: %d    | ATK: %d    | DEF: %d | SPEED: %d | SP_ATK: %d | SP_DEF: %d",
  world.pc.buddy[i]->get_hp(), world.pc.buddy[i]->get_atk(), world.pc.buddy[i]->get_def(),world.pc.buddy[i]->get_speed(), 
  world.pc.buddy[i]->get_spatk(), world.pc.buddy[i]->get_spdef());
  printw("\n");

  printw("move 1: %s   move 2: %s", world.pc.buddy[i]->get_move(0), world.pc.buddy[i]->get_move(1));

  printw("\n\n");
  }

  char ch = getch();
  if(ch == '1'){
    swap_poke(*world.pc.buddy[0],*world.pc.buddy[1]);
    printw("%s is now your current partner\n",  world.pc.buddy[0]->get_species());
    getch();
  }else if(ch =='2'){
   swap_poke(*world.pc.buddy[0],*world.pc.buddy[2]);
    printw("%s is now your current partner\n",  world.pc.buddy[0]->get_species());
    getch();
  }else if(ch =='3'){
   swap_poke(*world.pc.buddy[0],*world.pc.buddy[3]);
    printw("%s is now your current partner\n",  world.pc.buddy[0]->get_species());
    getch();
  }else if(ch =='4'){
   swap_poke(*world.pc.buddy[0],*world.pc.buddy[4]);
    printw("%s is now your current partner\n",  world.pc.buddy[0]->get_species());
    getch();
  }else if(ch =='5'){
   swap_poke(*world.pc.buddy[0],*world.pc.buddy[5]);
    printw("%s is now your current partner\n",  world.pc.buddy[0]->get_species());
    getch();
  }
}

void outside_bag(){

  clear();
  printw("1.Revive: %d   |    2.Potions: %d   |  3.Change pokemon |  4.Exit\n",revive_potion, potion);
  char ch = getch();
  if(ch =='1'){
   revive_poke();
  }else if(ch == '2'){
   potions();
  }
  else if(ch == '3'){
    change_pc_poke();
  }
  else if(ch == '4'){
    return;
  }

}

void change_npc_poke(npc *n){
  int x = 0;

    for(int i = 1; i < n->size; i++){
      if(n->buddy[i]->isDead == false){
        x = i; 
      }
    }

    if(x == 0){
        printw("The enemy ran out of pokemon\n");
        printw("You won the battle!!\n");
        gameOver = true; 
    }

    if(x == 1){
      swap_poke(*n->buddy[0], *n->buddy[1]);
      printw("The enemy change pokemon to %s\n", n->buddy[1]->get_species()); 
      getch();
    }
    else if(x == 2){
      swap_poke(*n->buddy[0], *n->buddy[2]);
      printw("The enemy change pokemon to %s\n", n->buddy[2]->get_species()); 
      getch();
    }
    else if(x == 3){
      swap_poke(*n->buddy[0], *n->buddy[3]);
      printw("The enemy change pokemon to %s\n", n->buddy[3]->get_species()); 
      getch();
    }
    else if(x == 4){
      swap_poke(*n->buddy[0], *n->buddy[4]);
      printw("The enemy change pokemon to %s\n", n->buddy[4]->get_species()); 
      getch();
    }
    else if(x == 5){
      swap_poke(*n->buddy[0], *n->buddy[5]);
      printw("The enemy change pokemon to %s\n", n->buddy[5]->get_species()); 
      getch();
    }

}

void npc_poke(npc *n){
  printw("This are the pokemons of trainer %c\n\n", n->symbol); 

  for(int i = 0; i < n->size; i++){
  printw("Pokemon %d: %s\n", i, n->buddy[i]->get_species());
  printw("HP: %d    | ATK: %d    | DEF: %d | SPEED: %d | SP_ATK: %d | SP_DEF: %d",
  n->buddy[i]->get_hp(), n->buddy[i]->get_atk(), n->buddy[i]->get_def(),n->buddy[i]->get_speed(), 
  n->buddy[i]->get_spatk(), n->buddy[i]->get_spdef());
  printw("\n");

  printw("move 1: %s   move 2: %s", n->buddy[i]->get_move(0), n->buddy[i]->get_move(1));

  printw("\n\n");
  }
}

void npc_attack(pokemon *pc_poke, pokemon *npc_poke, int npc_power){
  printw("\nTrainer pokemon used %s \n", npc_poke->get_move(0));

  int random_number = rand_range(85,100);
  int random_number2 = rand_range(0,255);
  int critical;
  
  if(random_number2 <= npc_poke->get_speed()/2){
    critical = 1.5;
  }else{
    critical = 1;
  }

  //Still need to implement STAB and TYPE
  int damage =((((2*npc_poke->get_level())/5+2)* npc_power *
              (pc_poke->get_atk()/npc_poke->get_def()+2))/50)*critical*random_number;

  //I tried using the formula given in the pdf but it was inconsistent so I just 
  //geneted a random number from 1 to 8 for the damage to fix this little bug 
  //sorry about that

  damage = rand_range(1,8);

  printw("\nThe trainer pokemon did %d to your pokemon\n", damage); 

  pc_poke->hp = pc_poke->hp - damage; 

  if(pc_poke->hp > 0){
  printw("\nYour pokemon have %d HP be careful!!\n", pc_poke->hp); 
  }
  else{
    printw("Sorry your pokemon is out of HP\n"); 
    pc_poke->hp = 0;
    pc_poke->isDead = true;
    printw("PRESS 1. Choose another pokemon | 2. Leave the fight");

    char ch = getch();
    if(ch == '1'){
      if(world.pc.size > 1){
      change_pc_poke();
      }
      
      else{
        printw("\n\nSorry you dont have more pokemons\n\n");
        printw("Please exit the battle arena\n");
        gameOver = true;
        getch();
      }
    }
    
    else if(ch == '2'){
      gameOver = true;
    }

  }
}

void npc_AI(pokemon *npc_poke){
  int x = rand_range(0,1);
  npc_attack(world.pc.buddy[0], npc_poke, npc_poke->get_power(x));
}

void pc_attack(npc * n){
  
  int power1 = world.pc.buddy[0]->get_power(0);
  int power2 = world.pc.buddy[0]->get_power(1);
  int power;
  int random_number = rand_range(85,100);
  int random_number2 = rand_range(0,255);
  int critical;
  
  if(random_number2 <= world.pc.buddy[0]->get_speed()/2){
    critical = 1.5;
  }else{
    critical = 1;
  }

  printw("\n");
  printw("\n");
  stats(n->buddy[0]);
  movesInfo(world.pc.buddy[0]);
  char ch = getch();
  if(ch == '1'){
printw("\nYou used move 1: %s\n\n", world.pc.buddy[0]->get_move(0));
    power = power1;
  }else if(ch == '2'){
printw("\nYou used move 2: %s\n\n", world.pc.buddy[0]->get_move(1));
    power = power2;
  }

  // printw("level: %d\n", world.pc.buddy[0]->get_level());
  //   printw("def: %d\n", world.pc.buddy[0]->get_def());

  // printw("atk: %d\n", world.pc.buddy[0]->get_atk());
  // printw("critical: %d\n", critical);

  //   double random_num = random_number/100;
  //     printw("rand: %ls\n", random_num);


  //Still need to implement STAB and TYPE
  int damage =((((2*world.pc.buddy[0]->get_level())/5+2)* power *
              (world.pc.buddy[0]->get_atk()/world.pc.buddy[0]->get_def()+2))/50)*critical*(random_number/100);  
  //I tried using the formula given in the pdf but it was inconsistent so I just 
  //geneted a random number from 1 to 8 for the damage to fix this little bug 
    //sorry about that

  damage = rand_range(1,8);

   printw("Great hit! you deal %d damage to enemy Pokemon\n\n", damage);
   n->buddy[0]->hp = n->buddy[0]->hp - damage;

   if(n->buddy[0]->hp <= 0){
    n->buddy[0]->hp = 0;
    n->buddy[0]->isDead = true;
    printw("The enemy pokemon ran out of HP\n");

    if(n->size > 1){
    printw("The enemy chose another pokemon\n");
    change_npc_poke(n);
    }

    else{
      printw("The trainer is out of pokemons\n");
      printw("You defeated the trainer!!!\n");
      getch();
      gameOver = true;
    }

   }
}

void attack_wildPoke(pokemon * n){
int power1 = world.pc.buddy[0]->get_power(0);
  int power2 = world.pc.buddy[0]->get_power(1);
  int power;
  int random_number = rand_range(85,100);
  int random_number2 = rand_range(0,255);
  int critical;
  
  if(random_number2 <= world.pc.buddy[0]->get_speed()/2){
    critical = 1.5;
  }else{
    critical = 1;
  }

  printw("\n");
  printw("\n");
  stats(n);
  movesInfo(world.pc.buddy[0]);
  char ch = getch();
  if(ch == '1'){
printw("\nYou used move 1: %s\n\n", world.pc.buddy[0]->get_move(0));
    power = power1;
  }else if(ch == '2'){
printw("\nYou used move 2: %s\n\n", world.pc.buddy[0]->get_move(1));
    power = power2;
  }

  // printw("level: %d\n", world.pc.buddy[0]->get_level());
  //   printw("def: %d\n", world.pc.buddy[0]->get_def());

  // printw("atk: %d\n", world.pc.buddy[0]->get_atk());
  // printw("critical: %d\n", critical);

  //   double random_num = random_number/100;
  //     printw("rand: %ls\n", random_num);


  //Still need to implement STAB and TYPE
  int damage =((((2*world.pc.buddy[0]->get_level())/5+2)* power *
              (world.pc.buddy[0]->get_atk()/world.pc.buddy[0]->get_def()+2))/50)*critical*(random_number/100);  
  //I tried using the formula given in the pdf but it was inconsistent so I just 
  //geneted a random number from 1 to 8 for the damage to fix this little bug 
  //sorry about that

  damage = rand_range(1,8);

   printw("Great hit! you deal %d damage to the wild Pokemon\n\n", damage);
   n->hp = n->hp - damage;

   if(n->hp <= 0){
    n->hp = 0;
    n->isDead = true;
    gameOver2 = true;
    printw("The wild pokemon ran out of HP\n");
    printw("You defeated the wild pokemon!!!\n");
    printw("\nCongrats!! you have a new pokemon, %s has been added to your bag\n", n->get_species());
    world.pc.buddy[world.pc.size] = n;
    world.pc.buddy[world.pc.size]->hp = world.pc.buddy[world.pc.size]->get_hp();
    world.pc.buddy[world.pc.size]->isGood = true;
    world.pc.buddy[world.pc.size]->isDead = false;
    world.pc.size++; 
   }

   getch();
}

void capture_poke(pokemon *n){

    if(pokeballs == 0){
    printw("Sorry you dont have any pokeballs, please go to a PokeMart\n");
    getch();
    return;
    }


    int x = rand_range(1,5);
    printw("Nice! you throw a pokeball at %s\n", n->get_species());

    if(x <= 2){
      printw("Sorry! the pokemon dodged the pokeball\n");
      printw("Try again later!\n");
    }

    else{
      printw("Congrats!! you successfully captured the wild pokemon\n");
      printw("Your new pokemon %s is being added to your bag\n", n->get_species());
     world.pc.buddy[world.pc.size] = n;
     world.pc.buddy[world.pc.size]->hp = world.pc.buddy[world.pc.size]->get_hp();
     world.pc.buddy[world.pc.size]->isGood = true;
     world.pc.buddy[world.pc.size]->isDead = false;
     world.pc.size++; 
     gameOver2 = true;

     getch();
    }

    pokeballs--;

    getch();
}

void wild_bag(pokemon *n){
  clear();
  printw("1.Revive: %d   |    2.Potions: %d    | 3. Pokeball: %d  |  4.Exit \n", revive_potion, potion, pokeballs);
  char ch = getch();
  if(ch =='1'){
   revive_poke();
  }else if(ch == '2'){
   potions();
  }else if (ch == '3'){
    capture_poke(n);
  }
  else if(ch == '4'){
    return;
  }
}

void wildEncounter(pokemon * n){

  options();
  gameOver2 = false;

  while(1){
     char ch=getch(); 
    if(gameOver2 == true){
      return; 
    } 
    if(ch =='1'){
      attack_wildPoke(n);
    if(gameOver2 == true){
      return; 
    } 
      npc_AI(n);
    if(gameOver2 == true){
      return; 
    } 
      options();
    }else if(ch =='2'){
      wild_bag(n);
      npc_AI(n);
    if(gameOver2 == true){
      return; 
    } 
      options();
    }else if(ch == '3'){
       return;
       npc_AI(n);
       options();
    }else if(ch == '4'){
      change_pc_poke();
      npc_AI(n);
    if(gameOver2 == true){
      return; 
    } 
      options();
    }else{
    if(gameOver2 == true){
      return;
    }
    }
  }

 getch();
}

void io_init_terminal(void)
{
  initscr();
  raw();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  init_pair(COLOR_RED, COLOR_RED, COLOR_BLACK);
  init_pair(COLOR_GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(COLOR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(COLOR_BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(COLOR_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(COLOR_CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(COLOR_WHITE, COLOR_WHITE, COLOR_BLACK);
}

void io_reset_terminal(void)
{
  endwin();

  while (io_head) {
    io_tail = io_head;
    io_head = io_head->next;
    free(io_tail);
  }
  io_tail = NULL;
}

void io_queue_message(const char *format, ...)
{
  io_message_t *tmp;
  va_list ap;

  if (!(tmp = (io_message_t *) malloc(sizeof (*tmp)))) {
    perror("malloc");
    exit(1);
  }

  tmp->next = NULL;

  va_start(ap, format);

  vsnprintf(tmp->msg, sizeof (tmp->msg), format, ap);

  va_end(ap);

  if (!io_head) {
    io_head = io_tail = tmp;
  } else {
    io_tail->next = tmp;
    io_tail = tmp;
  }
}

static void io_print_message_queue(uint32_t y, uint32_t x)
{
  while (io_head) {
    io_tail = io_head;
    attron(COLOR_PAIR(COLOR_CYAN));
    mvprintw(y, x, "%-80s", io_head->msg);
    attroff(COLOR_PAIR(COLOR_CYAN));
    io_head = io_head->next;
    if (io_head) {
      attron(COLOR_PAIR(COLOR_CYAN));
      mvprintw(y, x + 70, "%10s", " --more-- ");
      attroff(COLOR_PAIR(COLOR_CYAN));
      refresh();
      getch();
    }
    free(io_tail);
  }
  io_tail = NULL;
}

/**************************************************************************
 * Compares trainer distances from the PC according to the rival distance *
 * map.  This gives the approximate distance that the PC must travel to   *
 * get to the trainer (doesn't account for crossing buildings).  This is  *
 * not the distance from the NPC to the PC unless the NPC is a rival.     *
 *                                                                        *
 * Not a bug.                                                             *
 **************************************************************************/
static int compare_trainer_distance(const void *v1, const void *v2)
{
  const character *const *c1 = (const character * const *) v1;
  const character *const *c2 = (const character * const *) v2;

  return (world.rival_dist[(*c1)->pos[dim_y]][(*c1)->pos[dim_x]] -
          world.rival_dist[(*c2)->pos[dim_y]][(*c2)->pos[dim_x]]);
}

static character *io_nearest_visible_trainer()
{
  character **c, *n;
  uint32_t x, y, count;

  c = (character **) malloc(world.cur_map->num_trainers * sizeof (*c));

  /* Get a linear list of trainers */
  for (count = 0, y = 1; y < MAP_Y - 1; y++) {
    for (x = 1; x < MAP_X - 1; x++) {
      if (world.cur_map->cmap[y][x] && world.cur_map->cmap[y][x] !=
          &world.pc) {
        c[count++] = world.cur_map->cmap[y][x];
      }
    }
  }

  /* Sort it by distance from PC */
  qsort(c, count, sizeof (*c), compare_trainer_distance);

  n = c[0];

  free(c);

  return n;
}

void io_display()
{
  uint32_t y, x;
  character *c;

  clear();
  for (y = 0; y < MAP_Y; y++) {
    for (x = 0; x < MAP_X; x++) {
      if (world.cur_map->cmap[y][x]) {
        mvaddch(y + 1, x, world.cur_map->cmap[y][x]->symbol);
      } else {
        switch (world.cur_map->map[y][x]) {
        case ter_boulder:
          attron(COLOR_PAIR(COLOR_MAGENTA));
          mvaddch(y + 1, x, BOULDER_SYMBOL);
          attroff(COLOR_PAIR(COLOR_MAGENTA));
          break;
        case ter_mountain:
          attron(COLOR_PAIR(COLOR_MAGENTA));
          mvaddch(y + 1, x, MOUNTAIN_SYMBOL);
          attroff(COLOR_PAIR(COLOR_MAGENTA));
          break;
        case ter_tree:
          attron(COLOR_PAIR(COLOR_GREEN));
          mvaddch(y + 1, x, TREE_SYMBOL);
          attroff(COLOR_PAIR(COLOR_GREEN));
          break;
        case ter_forest:
          attron(COLOR_PAIR(COLOR_GREEN));
          mvaddch(y + 1, x, FOREST_SYMBOL);
          attroff(COLOR_PAIR(COLOR_GREEN));
          break;
        case ter_path:
          attron(COLOR_PAIR(COLOR_YELLOW));
          mvaddch(y + 1, x, PATH_SYMBOL);
          attroff(COLOR_PAIR(COLOR_YELLOW));
          break;
        case ter_gate:
          attron(COLOR_PAIR(COLOR_YELLOW));
          mvaddch(y + 1, x, GATE_SYMBOL);
          attroff(COLOR_PAIR(COLOR_YELLOW));
          break;
        case ter_mart:
          attron(COLOR_PAIR(COLOR_BLUE));
          mvaddch(y + 1, x, POKEMART_SYMBOL);
          attroff(COLOR_PAIR(COLOR_BLUE));
          break;
        case ter_center:
          attron(COLOR_PAIR(COLOR_RED));
          mvaddch(y + 1, x, POKEMON_CENTER_SYMBOL);
          attroff(COLOR_PAIR(COLOR_RED));
          break;
        case ter_grass:
          attron(COLOR_PAIR(COLOR_GREEN));
          mvaddch(y + 1, x, TALL_GRASS_SYMBOL);
          attroff(COLOR_PAIR(COLOR_GREEN));
          break;
        case ter_clearing:
          attron(COLOR_PAIR(COLOR_GREEN));
          mvaddch(y + 1, x, SHORT_GRASS_SYMBOL);
          attroff(COLOR_PAIR(COLOR_GREEN));
          break;
        case ter_water:
          attron(COLOR_PAIR(COLOR_CYAN));
          mvaddch(y + 1, x, WATER_SYMBOL);
          attroff(COLOR_PAIR(COLOR_CYAN));
          break;
        default:
          attron(COLOR_PAIR(COLOR_CYAN));
          mvaddch(y + 1, x, ERROR_SYMBOL);
          attroff(COLOR_PAIR(COLOR_CYAN)); 
       }
      }
    }
  }

  mvprintw(23, 1, "PC position is (%2d,%2d) on map %d%cx%d%c.",
           world.pc.pos[dim_x],
           world.pc.pos[dim_y],
           abs(world.cur_idx[dim_x] - (WORLD_SIZE / 2)),
           world.cur_idx[dim_x] - (WORLD_SIZE / 2) >= 0 ? 'E' : 'W',
           abs(world.cur_idx[dim_y] - (WORLD_SIZE / 2)),
           world.cur_idx[dim_y] - (WORLD_SIZE / 2) <= 0 ? 'N' : 'S');
  mvprintw(22, 1, "%d known %s.", world.cur_map->num_trainers,
           world.cur_map->num_trainers > 1 ? "trainers" : "trainer");
  mvprintw(22, 30, "Nearest visible trainer: ");
  if ((c = io_nearest_visible_trainer())) {
    attron(COLOR_PAIR(COLOR_RED));
    mvprintw(22, 55, "%c at vector %d%cx%d%c.",
             c->symbol,
             abs(c->pos[dim_y] - world.pc.pos[dim_y]),
             ((c->pos[dim_y] - world.pc.pos[dim_y]) <= 0 ?
              'N' : 'S'),
             abs(c->pos[dim_x] - world.pc.pos[dim_x]),
             ((c->pos[dim_x] - world.pc.pos[dim_x]) <= 0 ?
              'W' : 'E'));
    attroff(COLOR_PAIR(COLOR_RED));
  } else {
    attron(COLOR_PAIR(COLOR_BLUE));
    mvprintw(22, 55, "NONE.");
    attroff(COLOR_PAIR(COLOR_BLUE));
  }

  io_print_message_queue(0, 0);

  refresh();
}

uint32_t io_teleport_pc(pair_t dest)
{
  /* Just for fun. And debugging.  Mostly debugging. */

  do {
    dest[dim_x] = rand_range(1, MAP_X - 2);
    dest[dim_y] = rand_range(1, MAP_Y - 2);
  } while (world.cur_map->cmap[dest[dim_y]][dest[dim_x]]                  ||
           move_cost[char_pc][world.cur_map->map[dest[dim_y]]
                                                [dest[dim_x]]] == INT_MAX ||
           world.rival_dist[dest[dim_y]][dest[dim_x]] < 0);

  return 0;
}

static void io_scroll_trainer_list(char (*s)[40], uint32_t count)
{
  uint32_t offset;
  uint32_t i;

  offset = 0;

  while (1) {
    for (i = 0; i < 13; i++) {
      mvprintw(i + 6, 19, " %-40s ", s[i + offset]);
    }
    switch (getch()) {
    case KEY_UP:
      if (offset) {
        offset--;
      }
      break;
    case KEY_DOWN:
      if (offset < (count - 13)) {
        offset++;
      }
      break;
    case 27:
      return;
    }

  }
}

static void io_list_trainers_display(npc **c, uint32_t count)
{
  uint32_t i;
  char (*s)[40]; /* pointer to array of 40 char */

  s = (char (*)[40]) malloc(count * sizeof (*s));

  mvprintw(3, 19, " %-40s ", "");
  /* Borrow the first element of our array for this string: */
  snprintf(s[0], 40, "You know of %d trainers:", count);
  mvprintw(4, 19, " %-40s ", *s);
  mvprintw(5, 19, " %-40s ", "");

  for (i = 0; i < count; i++) {
    snprintf(s[i], 40, "%16s %c: %2d %s by %2d %s",
             char_type_name[c[i]->ctype],
             c[i]->symbol,
             abs(c[i]->pos[dim_y] - world.pc.pos[dim_y]),
             ((c[i]->pos[dim_y] - world.pc.pos[dim_y]) <= 0 ?
              "North" : "South"),
             abs(c[i]->pos[dim_x] - world.pc.pos[dim_x]),
             ((c[i]->pos[dim_x] - world.pc.pos[dim_x]) <= 0 ?
              "West" : "East"));
    if (count <= 13) {
      /* Handle the non-scrolling case right here. *
       * Scrolling in another function.            */
      mvprintw(i + 6, 19, " %-40s ", s[i]);
    }
  }

  if (count <= 13) {
    mvprintw(count + 6, 19, " %-40s ", "");
    mvprintw(count + 7, 19, " %-40s ", "Hit escape to continue.");
    while (getch() != 27 /* escape */)
      ;
  } else {
    mvprintw(19, 19, " %-40s ", "");
    mvprintw(20, 19, " %-40s ",
             "Arrows to scroll, escape to continue.");
    io_scroll_trainer_list(s, count);
  }

  free(s);
}

static void io_list_trainers()
{
  npc **c;
  uint32_t x, y, count;

  c = (npc **) malloc(world.cur_map->num_trainers * sizeof (*c));

  /* Get a linear list of trainers */
  for (count = 0, y = 1; y < MAP_Y - 1; y++) {
    for (x = 1; x < MAP_X - 1; x++) {
      if (world.cur_map->cmap[y][x] && world.cur_map->cmap[y][x] !=
          &world.pc) {
        c[count++] = dynamic_cast<npc *> (world.cur_map->cmap[y][x]);
      }
    }
  }

  /* Sort it by distance from PC */
  qsort(c, count, sizeof (*c), compare_trainer_distance);

  /* Display it */
  io_list_trainers_display(c, count);
  free(c);

  /* And redraw the map */
  io_display();
}

void io_pokemart()
{
  mvprintw(0, 0, "Welcome to the Pokemart. All your supplies have been restored");

  potion = 3; 
  revive_potion = 3;
  pokeballs = 3;

  refresh();
  getch();
}

void io_pokemon_center()
{
  mvprintw(0, 0, "Welcome to the Pokemon Center. All your pokemon have full health");

    for(int i = 0; i < world.pc.size; i++){
         world.pc.buddy[i]->hp = world.pc.buddy[i]->get_hp();
   }

  refresh();
  getch();
}

void io_battle(character *aggressor, character *defender)
{
  npc *n = (npc *) ((aggressor == &world.pc) ? defender : aggressor);
  // int i;

  // io_display();
  // mvprintw(0, 0, "My pokemon are: ");
  // printw("%s", n->buddy[0]->get_species());
  // for (i = 1; i < 6 && n->buddy[i]; i++) {
  //   printw(", %s", n->buddy[i]->get_species());
  // }

  mvprintw(0, 0, " You found a battle!! with %c ",n->symbol);

  gameOver = false;
  refresh();
  getch();

  n->defeated = 1;
  if (n->ctype == char_hiker || n->ctype == char_rival) {
    n->mtype = move_wander;
  }
  clear();

  if(world.pc.buddy[0]->isDead == true){
    printw("Sorry you cannot fight because your pokemon is out of HP\n\n");
    printw("Try changing to a pokemon that have HP\n");

    getch();
    return;
  }

  npc_poke(n); 
  options();

  getch();

  while(1){
     char ch=getch(); 
    if(gameOver == true){
      return; 
    } 
    if(ch =='1'){
      pc_attack(n);
    if(gameOver == true){
      return; 
    } 
      npc_AI(n->buddy[0]);
    if(gameOver == true){
      return; 
    } 
      options();
    }else if(ch =='2'){
      bag();
      npc_AI(n->buddy[0]);
    if(gameOver == true){
      return; 
    } 
      options();
    }else if(ch == '3'){
       return;
       npc_AI(n->buddy[0]);
       options();
    }else if(ch == '4'){
      change_pc_poke();
      npc_AI(n->buddy[0]);

    if(gameOver == true){
      return; 
    } 
      options();
    }else{
    if(gameOver == true){
      return;
    }
    }
  }

 getch();

}

uint32_t move_pc_dir(uint32_t input, pair_t dest)
{
  dest[dim_y] = world.pc.pos[dim_y];
  dest[dim_x] = world.pc.pos[dim_x];

  switch (input) {
  case 1:
  case 2:
  case 3:
    dest[dim_y]++;
    break;
  case 4:
  case 5:
  case 6:
    break;
  case 7:
  case 8:
  case 9:
    dest[dim_y]--;
    break;
  }
  switch (input) {
  case 1:
  case 4:
  case 7:
    dest[dim_x]--;
    break;
  case 2:
  case 5:
  case 8:
    break;
  case 3:
  case 6:
  case 9:
    dest[dim_x]++;
    break;
  case '>':
    if (world.cur_map->map[world.pc.pos[dim_y]][world.pc.pos[dim_x]] ==
        ter_mart) {
      io_pokemart();
    }
    if (world.cur_map->map[world.pc.pos[dim_y]][world.pc.pos[dim_x]] ==
        ter_center) {
      io_pokemon_center();
    }
    break;
  }

  if (world.cur_map->cmap[dest[dim_y]][dest[dim_x]]) {
    if (dynamic_cast<npc *> (world.cur_map->cmap[dest[dim_y]][dest[dim_x]]) &&
        ((npc *) world.cur_map->cmap[dest[dim_y]][dest[dim_x]])->defeated) {
      // Some kind of greeting here would be nice
      return 1;
    } else if ((dynamic_cast<npc *>
                (world.cur_map->cmap[dest[dim_y]][dest[dim_x]]))) {
      io_battle(&world.pc, world.cur_map->cmap[dest[dim_y]][dest[dim_x]]);
      // Not actually moving, so set dest back to PC position
      dest[dim_x] = world.pc.pos[dim_x];
      dest[dim_y] = world.pc.pos[dim_y];
    }
  }
  
  if (move_cost[char_pc][world.cur_map->map[dest[dim_y]][dest[dim_x]]] ==
      INT_MAX) {
    return 1;
  }

  return 0;
}

void io_teleport_world(pair_t dest)
{
  /* mvscanw documentation is unclear about return values.  I believe *
   * that the return value works the same way as scanf, but instead   *
   * of counting on that, we'll initialize x and y to out of bounds   *
   * values and accept their updates only if in range.                */
  int x = INT_MAX, y = INT_MAX;
  
  world.cur_map->cmap[world.pc.pos[dim_y]][world.pc.pos[dim_x]] = NULL;

  echo();
  curs_set(1);
  do {
    mvprintw(0, 0, "Enter x [-200, 200]:           ");
    refresh();
    mvscanw(0, 21, "%d", &x);
  } while (x < -200 || x > 200);
  do {
    mvprintw(0, 0, "Enter y [-200, 200]:          ");
    refresh();
    mvscanw(0, 21, "%d", &y);
  } while (y < -200 || y > 200);

  refresh();
  noecho();
  curs_set(0);

  x += 200;
  y += 200;

  world.cur_idx[dim_x] = x;
  world.cur_idx[dim_y] = y;

  new_map(1);
  io_teleport_pc(dest);
}

void io_handle_input(pair_t dest)
{
  uint32_t turn_not_consumed;
  int key;

  do {
    switch (key = getch()) {
    case '7':
    case 'y':
    case KEY_HOME:
      turn_not_consumed = move_pc_dir(7, dest);
      break;
    case '8':
    case 'k':
    case KEY_UP:
      turn_not_consumed = move_pc_dir(8, dest);
      break;
    case '9':
    case 'u':
    case KEY_PPAGE:
      turn_not_consumed = move_pc_dir(9, dest);
      break;
    case '6':
    case 'l':
    case KEY_RIGHT:
      turn_not_consumed = move_pc_dir(6, dest);
      break;
    case '3':
    case 'n':
    case KEY_NPAGE:
      turn_not_consumed = move_pc_dir(3, dest);
      break;
    case '2':
    case 'j':
    case KEY_DOWN:
      turn_not_consumed = move_pc_dir(2, dest);
      break;
    case '1':
    case 'b':
    case KEY_END:
      turn_not_consumed = move_pc_dir(1, dest);
      break;
    case '4':
    case 'h':
    case KEY_LEFT:
      turn_not_consumed = move_pc_dir(4, dest);
      break;
    case '5':
    case ' ':
    case '.':
    case KEY_B2:
      dest[dim_y] = world.pc.pos[dim_y];
      dest[dim_x] = world.pc.pos[dim_x];
      turn_not_consumed = 0;
      break;
    case '>':
      turn_not_consumed = move_pc_dir('>', dest);
      break;
    case 'Q':
      dest[dim_y] = world.pc.pos[dim_y];
      dest[dim_x] = world.pc.pos[dim_x];
      world.quit = 1;
      turn_not_consumed = 0;
      break;
      break;
    case 't':
      io_list_trainers();
      turn_not_consumed = 1;
      break;
    case 'p':
      /* Teleport the PC to a random place in the map.              */
      io_teleport_pc(dest);
      turn_not_consumed = 0;
      break;
    case 'B':
      outside_bag();
      break;
    case 'f':
      /* Fly to any map in the world.                                */
      io_teleport_world(dest);
      turn_not_consumed = 0;
      break;    
    case 'q':
      /* Demonstrate use of the message queue.  You can use this for *
       * printf()-style debugging (though gdb is probably a better   *
       * option.  Not that it matters, but using this command will   *
       * waste a turn.  Set turn_not_consumed to 1 and you should be *
       * able to figure out why I did it that way.                   */
      io_queue_message("This is the first message.");
      io_queue_message("Since there are multiple messages, "
                       "you will see \"more\" prompts.");
      io_queue_message("You can use any key to advance through messages.");
      io_queue_message("Normal gameplay will not resume until the queue "
                       "is empty.");
      io_queue_message("Long lines will be truncated, not wrapped.");
      io_queue_message("io_queue_message() is variadic and handles "
                       "all printf() conversion specifiers.");
      io_queue_message("Did you see %s?", "what I did there");
      io_queue_message("When the last message is displayed, there will "
                       "be no \"more\" prompt.");
      io_queue_message("Have fun!  And happy printing!");
      io_queue_message("Oh!  And use 'Q' to quit!");

      dest[dim_y] = world.pc.pos[dim_y];
      dest[dim_x] = world.pc.pos[dim_x];
      turn_not_consumed = 0;
      break;
    default:
      /* Also not in the spec.  It's not always easy to figure out what *
       * key code corresponds with a given keystroke.  Print out any    *
       * unhandled key here.  Not only does it give a visual error      *
       * indicator, but it also gives an integer value that can be used *
       * for that key in this (or other) switch statements.  Printed in *
       * octal, with the leading zero, because ncurses.h lists codes in *
       * octal, thus allowing us to do reverse lookups.  If a key has a *
       * name defined in the header, you can use the name here, else    *
       * you can directly use the octal value.                          */
      mvprintw(0, 0, "Unbound key: %#o ", key);
      turn_not_consumed = 1;
    }
    refresh();
  } while (turn_not_consumed);
}

void io_encounter_pokemon()
{
  pokemon *p;

  p = new pokemon();
  p->isDead = false; 

clear();

  // io_queue_message("%s%s%s: HP:%d ATK:%d DEF:%d SPATK:%d SPDEF:%d SPEED:%d %s",
  //                  p->is_shiny() ? "*" : "", p->get_species(),
  //                  p->is_shiny() ? "*" : "", p->get_hp(), p->get_atk(),
  //                  p->get_def(), p->get_spatk(), p->get_spdef(),
  //                  p->get_speed(), p->get_gender_string());
  // io_queue_message("%s's moves: %s %s", p->get_species(),
  //                  p->get_move(0), p->get_move(1));

  printw("You found a wild pokemon: %s\n", p->get_species());
  printw("\nmove 1: %s   move 2: %s", p->get_move(0), p->get_move(1));
  refresh();

  wildEncounter(p);

  // Later on, don't delete if captured
  delete p;
}

void io_choose_starter()

{
  class pokemon *choice[3];
  int i;
  bool again = true;
  
  choice[0] = new class pokemon();
  choice[1] = new class pokemon();
  choice[2] = new class pokemon();

  echo();
  curs_set(1);
  do {
    mvprintw( 4, 20, "Before you are three Pokemon, each of");
    mvprintw( 5, 20, "which wants absolutely nothing more");
    mvprintw( 6, 20, "than to be your best buddy forever.");
    mvprintw( 8, 20, "Unfortunately for them, you may only");
    mvprintw( 9, 20, "pick one.  Choose wisely.");
    mvprintw(11, 20, "   1) %s", choice[0]->get_species());
    mvprintw(12, 20, "   2) %s", choice[1]->get_species());
    mvprintw(13, 20, "   3) %s", choice[2]->get_species());
    mvprintw(15, 20, "Enter 1, 2, or 3: ");

    refresh();
    i = getch();
    
    if (i == '1' || i == '2' || i == '3') {
      world.pc.buddy[0] = choice[(i - '0') - 1];
      world.pc.buddy[0]->hp = world.pc.buddy[0]->get_hp();
      world.pc.buddy[0]->isGood = true;
      world.pc.buddy[0]->isDead = false;
      world.pc.size = 1; 
      delete choice[(i - '0') % 3];
      delete choice[((i - '0') + 1) % 3];
      again = false;
    }
  } while (again);
  noecho();
  curs_set(0);
}
