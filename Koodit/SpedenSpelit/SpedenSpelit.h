#ifndef SPEDENSPELIT_H
#define SPEDENSPELIT_H
#include <arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/*
  initializeTimer() subroutine intializes Arduino Timer1 module to
  give interrupts at rate 1Hz
  
*/
void initializeTimer(){
   TCCR1A = 0;   //VGM 11 ja VGM10 bitit nollaksi
   TCCR1B = 00001011;   // prescaler  
   OCR1A  = 250000;    // -> keskeytys, kun saavuttaa arvon 250000 = vertailuarvo
   TIMSK1 = 00000010; // enabloidaan vertailu keskeytykset
  interrupts();  //enabloidaan globaalit keskeytykset
}


void initializeTimer();
// Intoduce TIMER1_COMPA_vect Interrupt SeRvice (ISR) function for timer.
ISR(TIMER1_COMPA_vect);  /* keskeytyspalvelia   ISR = interupServiceRoutine   tähän hypätään, kun timerilta tulee keskeytys --> ocr1A saavuttaa arvon 250000 
Suorittaa alla olevan ohjelma ja palaaa suorittamaan missä olikin. keskeytys tulee ja uusi luku arvotaan -> ledi syttyy*/


/*
  initializeGame() subroutine is used to initialize all variables
  needed to store random numbers and player button push data.
  This function is called from startTheGame() function.
  
*/
void initializeGame();

string randomNumbers[100];  //Arvotut luvut     Arpominen tapahtuu Timer1:n keskeytyspalvelijassa
string userNumbers[100]; //painetut napit   talletetaan näppäinten keskeytyspalvelijassa


/*
  checkGame() subroutine is used to check the status
  of the Game after each player button press.
  
  If the latest player button press is wrong, the game stops
  and if the latest press was right, game display is incremented
  by 1.
  
  Parameters
  byte lastButtonPress of the player 0 or 1 or 2 or 3
  
*/
void checkGame(byte);  //ottaa parametrit "byte"

   if(userNumbers != randomNumbers) {

     stopTheGame();  //peli päättyy

      } else {
          showResults();  // lisataanpiste ja peli jatkuu
}


/*
  void stopTheGame(void)
  keskeyttaa pelin ja nayttää tuloksen -> resetointi 
*/
void stopTheGame() {
    TCCR1B = 0;  //pysäyttää timerin laskennan
    TIMSK1 &= ~(1 << OCR1A);   //shift rekister left = disabloi keskeytykset. 
    showResults();  //Kutsuu funktiota missä näytetään lopputulos jne..
}


/*
  startTheGame() subroutine calls InitializeGame()
  function and enables Timer1 interrupts to start
  the Game.
*/
void startTheGame() {

   InitializeGame();
}



#endif
