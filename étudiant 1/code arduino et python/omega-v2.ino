/*
 * Test 3 aterliers ou tabata ou fractionne ou combat
 * Résultat attendu : 
 * Tappez 1 ou 2 ou 3 ou 4 => 'sub training' dans moniteur serie
 *
 * 
 * 
 * BOUCLE ------------------------------------
 * Un son en fonction de vitesse
 * Affichage du cycle en cours 1s
 * Affichage temps travail total 1s
 * Affichage temps repos 1s
 * 
 * Affichage Chaque seconde - 1 (en minute)
 * son de fin
 * Attente de temps de pause
 * 2 sons
 * BOUCLE ------------------------------------
 */

//##################################### INIT #####################################
#include "Adafruit_LEDBackpack.h"
#include "SoftwareSerial.h"

// Creation de l'objet  matrix de l'afficheur 
Adafruit_7segment matrix = Adafruit_7segment();

// Definition pin led
const int led_pin = 5;

// Definition pin bouton
const int boutton_pin = 2;

// Definition pin buzzer
const int buzzer_pin = 8;

// Creation de la communication pour le keypad 
// et ses pins 3 et 4 (a intervertir ou changer en fonction de vos branchements)
SoftwareSerial keypad_serial(3,4);

// Permet de selectionner le programme 1 seule fois
int etape_programme = 0;

// Permet de communiquer entre les fonctions
int global_minutes = 0;
int global_sec = 0;
int global_nbr=-1;
int global_temps_travail_sec=-1;
int global_temps_travail_sec_max=-1;
int global_temps_repos_sec=-1;
int global_vitesse=-1;
//##################################### INIT #####################################

//##################################### SETUP ####################################
void setup() {
  // Creation de la communication USB pour voir avec Outils => Moniteur série
  Serial.begin(9600);

  // Creation de la communication avec l'afficheur 
  matrix.begin(0x70);
  
  // Creation de la communication avec le keypad
  keypad_serial.begin(9600); 
    
  // Configuration des pins 
  // De la led
  pinMode(led_pin, OUTPUT);
  // Du BUZZER
  pinMode(buzzer_pin, OUTPUT);
  // Du bouton
  pinMode(boutton_pin, INPUT);
  
  // Configuration de l'aléatoire avec une connexion VIDE A0
  randomSeed(analogRead(0));

}
//##################################### SETUP ####################################

//##################################### LOOP #####################################
void loop() {
  // Selection 1 seule fois du programme 1 ou 2 ou 3 ou 4
  if(etape_programme == 0){
    int key = get_keypad();
    if(key <= 0 || key >= 5){return;}
    etape_programme=1;
    training(key);
  }
} 
//##################################### LOOP #####################################

//############################## SELECTION training ##############################
void training(int numero){
    //1=atelier,2=tabata,3=fractionné aléatoitre,4=combat
    switch(numero) {
          case 1 :
            constructor_atelier_tabata(1);
            break;
          case 2 :
            constructor_atelier_tabata(2);
            break;
          case 3 :
            constructor_fractione();
            break;
          case 4 :
            constructor_combats();
            break;
          default:
            break;
    }
}
//############################## SELECTION training ##############################








//################################ ATELIER+TABATA ################################
void constructor_atelier_tabata(int aterlier_tabata){
  // Print nature entrainement
  if(aterlier_tabata == 1){
    Serial.println("training 1 aterlier"); 
  }else{
    Serial.println("training 2 tabata");
  }

  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir nombre");
  while(global_nbr==-1){
    get_nbr(aterlier_tabata);
  }

  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir temps travail");
  while(global_temps_travail_sec == -1){
    get_temps_travail(aterlier_tabata);
  }

  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir temps repos");
  while(global_temps_repos_sec == -1){
    get_temps_repos(aterlier_tabata);
  }

  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir vitesse 1 ou 2");
  while(global_vitesse == -1){
    get_vitesse();
  }

  // Attente bouton
  Serial.println("Pressez le bouton");
  wait_for_button();
  Serial.println("bouton pressez passage travail");

  // Début boucle_principale avec tous les paramètres
  boucle_principale(0,global_nbr,global_temps_travail_sec,
  global_temps_repos_sec, global_vitesse); 
    
}
//################################ ATELIER+TABATA ################################

//################################ FRACTIONNE ################################
void constructor_fractione(){
  // Print nature entrainement
  Serial.println("training 3 fractionne"); 


  // Tant que les variables globales sont à -1 => Essayer de les attribuer  
  Serial.println("choisir cycles");
  while(global_nbr==-1){
    get_nbr(2);
  }
  
  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir temps travail min");
  while(global_temps_travail_sec == -1){
    get_temps_travail_frac(1);
  }
  
  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir temps travail max");
  while(global_temps_travail_sec_max == -1){
    get_temps_travail_frac(2);
  }
  
  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir temps repos");
  while(global_temps_repos_sec == -1){
    get_temps_repos(2);
  }
  
  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir vitesse 1 ou 2");
  while(global_vitesse == -1){
    get_vitesse();
  }

  // Attente bouton
  Serial.println("Pressez le bouton");
  wait_for_button();
  Serial.println("bouton pressez passage travail");

  // Début boucle_principale_frac avec tous les paramètres
  boucle_principale_frac(0,global_nbr,global_temps_travail_sec,global_temps_travail_sec_max,
  global_temps_repos_sec, global_vitesse, 0); 
    
}
//################################ FRACTIONNE ################################


//################################# COMBATS ##################################
void constructor_combats(){
  // Print nature entrainement
  Serial.println("training 4 combats"); 

  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir nbr rounds");
  while(global_nbr==-1){
    get_nbr(2);
  }

  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir temps travail");
  while(global_temps_travail_sec == -1){
    get_temps_travail(3);
  }

  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir temps repos");
  while(global_temps_repos_sec == -1){
    get_temps_repos(3);
  }

  // Tant que les variables globales sont à -1 => Essayer de les attribuer 
  Serial.println("choisir vitesse 1 ou 2");
  while(global_vitesse == -1){
    get_vitesse();
  } 

  
  // Attente bouton
  Serial.println("Pressez le bouton");
  wait_for_button();
  Serial.println("bouton pressez passage travail");

  // Début boucle_principale_combat avec tous les paramètres
  boucle_principale_combat(0,global_nbr,global_temps_travail_sec,
  global_temps_repos_sec, global_vitesse); 
}
//################################# COMBATS ##################################








//############## ATELIER TABATA :  RECEVOIR NOMBRE ATERLIERS #####################

// Recupération et verification d'un nombre d'atelier / cycle / round 
void get_nbr(int aterlier_tabata_combats){
  int key1 = get_input();
  if(aterlier_tabata_combats == 1){
    if(key1 > 0 && key1 < 11){
      Serial.print("Avec ");
      Serial.print(key1);
      Serial.println(" nombre d'ateriers dans la limite 1-10");
      global_nbr=key1;
    }else{
      Serial.print(key1);
      Serial.println(" nombre d'ateriers PAS la limite 1-10. Recommencer");
      get_nbr(aterlier_tabata_combats);
    }
  }else{
    Serial.print("Avec ");
    Serial.print(key1);
    if(aterlier_tabata_combats == 3){
      Serial.println(" nombre de combats");
    }else{
      Serial.println(" nombre de cycle");
    }
    global_nbr=key1;
  }
}
//############## ATELIER TABATA :  RECEVOIR NOMBRE ATERLIERS #####################



//############### ATELIER TABATA :  RECEVOIR TEMPS TRAVAIL #######################
// Recupération et verification d'un temps de travail atelier / cycle
void get_temps_travail(int aterlier_tabata){
  int key2 = get_input(); 
  Serial.print("reçus "); 
  Serial.println(key2);
  if(aterlier_tabata == 1){
    if(key2 < 10 || key2 > 300){
      Serial.print(key2);
      Serial.println(" temps travail PAS la limite 10-300. Recommencer");
      get_temps_travail(aterlier_tabata);
    }
  }if(aterlier_tabata == 2){
    if(key2 < 15 || key2 > 120){
      Serial.print(key2);
      Serial.println(" temps travail PAS la limite 15-120. Recommencer");
      get_temps_travail(aterlier_tabata);
    }
  
  }
  Serial.print("Avec ");
  Serial.print(key2);
  global_temps_travail_sec=key2;
  Serial.print("s soit ");
  seconde_minutes(key2);
  Serial.print(global_minutes);
  Serial.print(" minutes et");
  Serial.print(global_sec);
  Serial.println(" s temps de travail");
}
//############### ATELIER TABATA :  RECEVOIR TEMPS TRAVAIL #######################

//################ ATELIER TABATA : RECEVOIR TEMPS REPOS #########################
// Recupération et verification d'un temps de repos atelier / cycle
void get_temps_repos(int aterlier_tabata){
  int key2 = get_input(); 
  if(key2 < 0 || key2 > 60){
    if(aterlier_tabata == 1){
      Serial.print(key2);
      Serial.println(" temps repos PAS la limite 0-60. Recommencer");
      get_temps_repos(aterlier_tabata);
    }
  }
  Serial.print("Avec ");
  Serial.print(key2);
  global_temps_repos_sec=key2;
  Serial.print("s soit ");
  seconde_minutes(key2);
  Serial.print(global_minutes);
  Serial.print(" minutes et");
  Serial.print(global_sec);
  Serial.println(" s temps de repos");
}
//################ ATELIER TABATA : RECEVOIR TEMPS REPOS #########################

//################## ATELIER TABATA :  RECEVOIR VITESSE ##########################
// Recupération et verification d'une vitesse
void get_vitesse(){
  int key4 = get_input();
  if(key4 != 1 && key4 != 2){
     Serial.print(key4);
     Serial.println(" vitesse PAS la limite 1 ou 2. Recommencer");
     get_vitesse();
  }
  global_vitesse=key4;
  Serial.print("Avec ");
  Serial.print(key4);
  Serial.println(" vitesse");
}
//################## ATELIER TABATA :  RECEVOIR VITESSE ##########################


//################## FRACTIONNE :  RECEVOIR TEMPS ##########################
// Recupération et verification d'un temps de travail FRACTIONNE
void get_temps_travail_frac(int max_min){
  int key2 = get_input(); 
  if(max_min==1){
    if(key2 < 5 || key2 > 120){
      Serial.print(key2);
      Serial.println(" temps travail min PAS la limite 5-120. Recommencer");
      get_temps_travail_frac(max_min);
    }else{
      global_temps_travail_sec=key2;
    }
  }else{
    if(key2 < 10 || key2 > 300){
      Serial.print(key2);
      Serial.println(" temps travail max PAS la limite 10-300. Recommencer");
       get_temps_travail_frac(max_min);
    }else{
        global_temps_travail_sec_max=key2;
    }
  }
  
  Serial.print("Avec ");
  Serial.print(key2);
  Serial.print("s soit ");
  seconde_minutes(key2);
  Serial.print(global_minutes);
  Serial.print(" minutes et");
  Serial.print(global_sec);
  Serial.print(" s temps de travail ");
  if(max_min==1){
    Serial.println("min");
  }else{
    Serial.println("max");
  }
}
//################## FRACTIONNE :  RECEVOIR TEMPS ##########################











//################## ATELIER TABATA :  BOUCLE PRINCIPALE #########################
void boucle_principale(int cycle, int cycle_max, int temps1, int temps2,int vitesse){
    if(cycle > cycle_max){return;}
    
    int local_t1=temps1; // sec
    int local_t2=temps2; // sec

    // son en fonction de vitesse
    if(vitesse == 1){
      tone(buzzer_pin, 1950, 125);
    }else{
      tone(buzzer_pin, 750, 125);
    }
    
    // affichage cycle en cours
    matrix.println(cycle);
    matrix.writeDisplay();
    if(wait_while_waiting_button(1000) == -1){
      return;
    }

    // affichage temps travail sec
    seconde_minutes(temps1);
    matrix.println(global_minutes*100+global_sec);
    matrix.writeDisplay();
    if(wait_while_waiting_button(1000) == -1){
      return;
    }
    
    // affichage temps repos sec
    seconde_minutes(temps2);
    matrix.println(global_minutes*100+global_sec);
    matrix.writeDisplay();
    if(wait_while_waiting_button(1000) == -1){
      return;
    }

    digitalWrite(led_pin, HIGH);
    
    // Tant qu'il reste du temps travail
    while(local_t1 >= 1){
      // secondes -1
      local_t1=local_t1-1;
      
      // conversion en minutes + affichage
      seconde_minutes(local_t1);
      matrix.println(global_minutes*100+global_sec);
      matrix.writeDisplay();
      
      // Verification port serial
      Serial.print("Attendue : ");
      Serial.println(global_minutes*100+global_sec);
      if(wait_while_waiting_button(1000) == -1){
      return;
      }
    }
    
    son1(); // Son travail => repos
    Serial.println("passage repos");
    digitalWrite(led_pin, LOW);


    // Tant qu'il reste du temps repos
    while(local_t2 >= 1){
      // secondes -1
      local_t2=local_t2-1;
      
      // conversion en minutes + affichage
      seconde_minutes(local_t2);
      matrix.println(global_minutes*100+global_sec);
      matrix.writeDisplay();
      
      // Verification port serial
      Serial.print("Attendue : ");
      Serial.println(global_minutes*100+global_sec);
      if(wait_while_waiting_button(1000) == -1){
        return;
      }
    }

    // Son repos => travail
    son1();
    if(wait_while_waiting_button(50) == -1){
      return;
    }
    son1();
    Serial.println("passage travail");

    // prochain cycle 
    boucle_principale(cycle+1,cycle_max, temps1, temps2, vitesse);
}
//################## ATELIER TABATA :  BOUCLE PRINCIPALE #########################


//################## FRACTIONNE :  BOUCLE PRINCIPALE #########################
void boucle_principale_frac(int cycle, int cycle_max, int temps_travail_min, 
                            int temps_travail_max, int temps_repos,int vitesse, int inversion){
                              
  if(cycle > cycle_max){return;}

  // secondes
  int local_t1=temps_travail_min; 
  if(inversion == 1){
    local_t1=temps_travail_max;
  }
  int local_t2=temps_repos; 

  // son en fonction de vitesse
  if(vitesse == 1){
    tone(buzzer_pin, 1950, 125);
  }else{
    tone(buzzer_pin, 750, 125);
  }

    // affichage combat en cours
    matrix.println(cycle);
    matrix.writeDisplay();
    if(wait_while_waiting_button(1000) == -1){
      return;
    }

    // affichage temps travail sec
    seconde_minutes(local_t1);
    matrix.println(global_minutes*100+global_sec);
    matrix.writeDisplay();
    if(wait_while_waiting_button(1000) == -1){
      return;
    }
    
    // affichage temps repos sec
    seconde_minutes(local_t2);
    matrix.println(global_minutes*100+global_sec);
    matrix.writeDisplay();
    if(wait_while_waiting_button(1000) == -1){
      return;
    }

    digitalWrite(led_pin, HIGH);
 
    // Tant qu'il reste du temps travail
    while(local_t1 >= 1){
      // secondes -1
      local_t1=local_t1-1;
      
      // conversion en minutes + affichage
      seconde_minutes(local_t1);
      matrix.println(global_minutes*100+global_sec);
      matrix.writeDisplay();
      
      // Verification port serial
      Serial.print("Attendue : ");
      Serial.println(global_minutes*100+global_sec);
      
      // BIP 10 dernieres sec
      if(local_t1 <= 10){
        son1();
      }


      // random(30000) > 29998        1/30 000   soit 1 par 30 seconde
      // Changer de vitesse
      for (int i = 0; i <= 1000; i++) {        
        if(random(30000) > 29998){
         Serial.println("Vitesse changé aléatoirement");
         if(vitesse == 1){vitesse=2;}else{vitesse=1;}
         if(vitesse == 1){
          tone(buzzer_pin, 1950, 125);
         }else{
          tone(buzzer_pin, 750, 125);
         }
        }
        if(wait_while_waiting_button(1) == -1){
          return;
        }
      }   
    }
    
    son1(); // Son travail => repos
    digitalWrite(led_pin, LOW);
    Serial.println("passage repos");

    // Tant qu'il reste du temps repos
    while(local_t2 >= 1){
      // secondes -1
      local_t2=local_t2-1;
      
      // conversion en minutes + affichage
      seconde_minutes(local_t2);
      matrix.println(global_minutes*100+global_sec);
      matrix.writeDisplay();
      
      // Verification port serial
      Serial.print("Attendue : ");
      Serial.println(global_minutes*100+global_sec);
      if(wait_while_waiting_button(1000) == -1){
        return;
      }
    }

    // Son repos => travail
    son1();
    if(wait_while_waiting_button(50) == -1){
      return;
    }
    son1();
    Serial.println("passage travail");

      
    if(inversion == 0){inversion=1;}else{inversion=0;}
    boucle_principale_frac(cycle+1, cycle_max, temps_travail_min, 
                            temps_travail_max, temps_repos,vitesse, inversion);
}
//################## FRACTIONNE :  BOUCLE PRINCIPALE #########################



//#################### COMBAT :  BOUCLE PRINCIPALE ###########################
void boucle_principale_combat(int cycle, int cycle_max, int temps_travail, 
                            int temps_repos,int vitesse){
                              
  if(cycle > cycle_max){return;}

  // creation variables local en secondes
  int local_t1=temps_travail; 
  int local_t2=temps_repos; 

  // son en fonction de vitesse
  if(vitesse == 1){
    tone(buzzer_pin, 1950, 125);
  }else{
    tone(buzzer_pin, 750, 125);
  }

    // affichage combat en cours
    matrix.println(cycle);
    matrix.writeDisplay();
    if(wait_while_waiting_button(1000) == -1){
      return;
    }

    // affichage temps travail sec
    seconde_minutes(local_t1);
    matrix.println(global_minutes*100+global_sec);
    matrix.writeDisplay();
    if(wait_while_waiting_button(1000) == -1){
      return;
    }
    
    // affichage temps repos sec
    seconde_minutes(local_t2);
    matrix.println(global_minutes*100+global_sec);
    matrix.writeDisplay();
    if(wait_while_waiting_button(1000) == -1){
      return;
    }

    digitalWrite(led_pin, HIGH);
 
    // Tant qu'il reste du temps travail
    while(local_t1 >= 1){
      // secondes -1
      local_t1=local_t1-1;
      
      // conversion en minutes + affichage
      seconde_minutes(local_t1);
      matrix.println(global_minutes*100+global_sec);
      matrix.writeDisplay();
      
      // Verification port serial
      Serial.print("Attendue : ");
      Serial.println(global_minutes*100+global_sec);
      
      // BIP 10 dernieres sec
      if(local_t1 <= 10){
        son1();
      }

      
      if(wait_while_waiting_button(1000) == -1){
      return;
    }
    }
    
    son1(); // Son travail => repos
    digitalWrite(led_pin, LOW);
    Serial.println("passage repos");

    // Tant qu'il reste du temps repos
    while(local_t2 >= 1){
      // secondes -1
      local_t2=local_t2-1;
      
      // conversion en minutes + affichage
      seconde_minutes(local_t2);
      matrix.println(global_minutes*100+global_sec);
      matrix.writeDisplay();
      
      // Verification port serial
      Serial.print("Attendue : ");
      Serial.println(global_minutes*100+global_sec);

       // BIP 10 dernieres sec
      if(local_t2 <= 10){
        son1();
      }
      
      if(wait_while_waiting_button(1000) == -1){
      return;
    }
    }

    // Son repos => travail
    son1();
    if(wait_while_waiting_button(50) == -1){
      return;
    }
    son1();
    Serial.println("passage travail");

    
    boucle_principale_combat(cycle+1, cycle_max, temps_travail, 
                            temps_repos,vitesse);
}
//#################### COMBAT :  BOUCLE PRINCIPALE ###########################







//########################## GENERAL :  DELAY BUTTON ##################################
// Permet de verifier la pause, la reprise et l'arrêt dans un delay()
// Le but est de remplacer un delay(1000); en instruction non-bloquante
int wait_while_waiting_button(int _delay){
  int _pause=0;

  for (int i = 0; i < _delay; i++) { 
    if(digitalRead(boutton_pin) == 0){
     Serial.println("pause");
     for (int j = 0; j < 1200; j++) {
        if(digitalRead(boutton_pin) == 0){
     _pause=_pause+1;}
     delay(1);
     }
     if(_pause >= 900){
      Serial.println("arrêt");
      return -1;
     }
     while(digitalRead(boutton_pin) == 1){

     }
     Serial.println("fin pause");
      delay(800);
    }


    delay(1);  
  }return 1;
}


//########################## GENERAL :  DELAY BUTTON ##################################


//########################## GENERAL :  GET BUTTON ####################################
// Permet d'attendre jusqu'a l'appuie
void wait_for_button(){
  while(1){
    if(digitalRead(boutton_pin) == 0){
      // Permet de ne pas pause dès le début
      while(digitalRead(boutton_pin) == 1){
      }
      delay(800);
      break;
    }
  }
}
//########################## GENERAL :  GET BUTTON ####################################

//####################### GENERAL :  MULTI DIGIT KEYPAD ################################
// 3 nombres puis #  renvoie ce nombre
int get_input(){
  int key = get_keypad();
  int my_input = 0;
  int my_digit = 0;
  
  while(true){
    key = get_keypad();
    if(key <= 9 && key != -1){
      my_input=my_input*10+key;
      my_digit=my_digit+1;
    }
    if(key == 12){
      if(my_digit < 10 && my_digit !=0){
        Serial.print("Valeur rentré ");
        Serial.println(my_input);
        return my_input;
      }else{
         int my_input = 0;
         int my_digit = 0;
      }
    }    
  }
}
//####################### GENERAL :  MULTI DIGIT KEYPAD ################################


//####################### GENERAL :  SIGLE DIGIT KEYPAD ################################
int get_keypad(){
        uint8_t data = keypad_serial.read();
        switch(data) {
                case 0xE1 :
                    Serial.println("1");
                    return 1;
                    break;
                case 0xE2 :
                    Serial.println("2");
                    return 2;
                    break;
                case 0xE3 :
                    Serial.println("3");
                    return 3;
                    break;
                case 0xE4 :
                    Serial.println("4");
                    return 4;
                    break;
                case 0xE5 :
                    Serial.println("5");
                    return 5;
                    break;
                case 0xE6 :
                    Serial.println("6");
                    return 6;
                    break;
                case 0xE7 :
                    Serial.println("7");
                    return 7;
                    break;
                case 0xE8 :
                    Serial.println("8");
                    return 8;
                    break;
                case 0xE9 :
                    Serial.println("9");
                    return 9;
                    break;
                case 0xEA :
                    Serial.println("*");
                    return 10;
                    break;
                case 0xEB :
                    Serial.println("0");
                    return 0;
                    break;
                case 0xEC :
                    Serial.println("#");
                    return 12;
                    break;
                default:
                    return -1;
                    break;
            }}
//####################### GENERAL :  SIGLE DIGIT KEYPAD ################################


//####################### GENERAL :  SON1 ################################
void son1(){
  for (int i = 0; i < 100; i++) {  
    digitalWrite(buzzer_pin, HIGH); 
    delay(1); 
    digitalWrite(buzzer_pin, LOW); 
    delay(1);
  }
}
//####################### GENERAL :  SON1 ################################




//####################### GENERAL :   SECONDES => MINUTES ################################
// Change les variables globales  global_minutes et global_sec en 
// fonction de l'argument secondes 
void seconde_minutes(int secondes){
  int minutes=0;
  while(secondes >= 60){
  minutes=minutes+1;
  secondes=secondes-60;
  }
  global_minutes=minutes;
  global_sec=secondes;
}
//####################### GENERAL :   SECONDES => MINUTES ################################
