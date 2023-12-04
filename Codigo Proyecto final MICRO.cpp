/*
  Proyecto: Grua utilizando Arduino
  
  Descripción:
  Este codigo esta escrito en el lenguaje de programacion C++, y especificamente para ser utilizado en Arduino,
  la funcion que realizara este proyecto sera la simulacion de una grua en la vida real en nuestro caso caso
  haciendo uso de 2 servomotores que uno actuara como la parte del gancho de la grua que sube y baja y el otro 
  realizara el moviemiento de izquierda a derecha para ellos necesitamos los conocimientos aplicados en clase y
  despues de inventigar por internet pudimos obtener el resultado deseado.
  
  Componentes:
  Para el desarrollo de dicho proyecto utilizamos
  - Placa de arduino
  - 2 servomotores
  - 2 luces led
  - 2 resistencias de 220 ohmios
  - Cables jumper
  - 1 Protoboard
  - 1 joystick

  Conexiones:
  Basicamente el encargado de coordinar el movimiento del gancho de la grua sera el joystick este le estara enviando
  las ordenes a los servomotores para ver que movimiento es el que deben realizar.
  Los LED funcionaran como indicadores unicamente, y estos lo que haran sera dar aviso que si esta en funcionamiento
  la grua no puede circular nadie por ende se enciende la LED roja y cuando se deteniene de operar la LED verde
  procede a encerderse y puede continuar la libre circulacion en el area de trabajo.
*/

// Bibliotecas necesarias para el funcionamiento del proyecto
#include <Servo.h>  // Incluye la biblioteca para controlar nuestros 2 servos

// Declaracion de constantes para pines de los LEDs y servomotores
const int ledRojoPin = 13; //Pin para controlar el led rojo
const int ledVerdePin = 12; //Pin para controlar el led rojo

// Variables globales
Servo servo1; // Objeto de la clase Servo para controlar el servo1
Servo servo2; // Objeto de la clase Servo para controlar el servo2

// Posiciones iniciales de los servomotores
int eje1 = 90;
int eje2 = 90;

/*
  setup(): Configuración inicial del programa.
*/
void setup() {
  // Inicialización de los servomotores y LEDs
  servo1.attach(7); // El pin 7 controlará el servomotor conectado a la placa Arduino
  servo2.attach(6); // El pin 6 controlará el servomotor conectado a la placa Arduino
  servo1.write(90);  // Establece la posición inicial del servo1 a 90 grados
  servo2.write(90);  // Establece la posición inicial del servo2 a 90 grados
  pinMode(ledRojoPin, OUTPUT); // Configura el pin del LED Rojo como salida
  pinMode(ledVerdePin, OUTPUT); // Configura el pin del LED Verde como salida
}

/*
  loop(): Función principal del programa que se ejecuta en bucle.
*/
void loop() {
  // Control del LED Rojo
  /*
  Mediante un if procederemos a analizar la posicion del joystick tanto en el eje X, como en el eje Y,
  y determinar si el joystick se esta moviendo para encender el LED rojo, caso contario el led permanecera
  apagado
  */ 
  if (analogRead(0) < 200 || analogRead(1) < 200 || analogRead(0) > 700 || analogRead(1) > 700) {
    digitalWrite(ledRojoPin, HIGH); // Enciende el LED Rojo si se mueve el joystick
  } else {
    digitalWrite(ledRojoPin, LOW); // Apaga el LED Rojo si no se mueve el joystick
  }

  // Control del LED Verde
  /*
    Para llevar el control del LED verde vamos hacer algo similiar a la parte anterior, mediante un if procederemos a analizar 
    la posicion del joystick tanto en el eje X, como en el eje Y, y determinar si el joystick se esta moviendo para 
    encender el LED rojo, caso contario el LED rojo permanecera apagado y el LED verde encendido
  */ 
  if (analogRead(0) >= 200 && analogRead(0) <= 700 && analogRead(1) >= 200 && analogRead(1) <= 700) {
    digitalWrite(ledVerdePin, HIGH); // Enciende el LED Verde si no se mueve el joystick
  } else {
    digitalWrite(ledVerdePin, LOW); // Apaga el LED Verde si se mueve el joystick
  }

  // Control del SERVO 1
  /*
    La funcion analogRead() nos permite acceder a la posicion que se encuentra el eje X en nuestro caso en el pin A0
    tenemos definido la conexion desde el joystick para dicho eje, y lo que esto nos permitira es moverlo o para la derecha
    o izquierda dependiendo de que manera lo este manipulando el usuario.
  */
  if (analogRead(0) < 200 && eje1 < 180) {
    eje1++;  // Incrementa la posición del servo1 si el joystick se mueve hacia la izquierda
    servo1.write(eje1);
  } else if (analogRead(0) > 700 && eje1 > 0) {
    eje1--;  // Decrementa la posición del servo1 si el joystick se mueve hacia la derecha
    servo1.write(eje1);
  }

  // Control del SERVO 2
  /*
    La funcion analogRead() nos permite acceder a la posicion que se encuentra el eje Y en nuestro caso en el pin A1,
    tenemos definido la conexion desde el joystick para dicho eje, y lo que esto nos permitira es moverlo
    para arriba o abajo dependiendo de que manera lo este manipulando el usuario.
  */
  if (analogRead(1) < 200 && eje2 < 180) {
    eje2++;  // Incrementa la posición del servo2 si el joystick se mueve hacia arriba
    servo2.write(eje2);
  } else if (analogRead(1) > 700 && eje2 > 0) {
    eje2--;  // Decrementa la posición del servo2 si el joystick se mueve hacia abajo
    servo2.write(eje2);
  }

  delay(5); // Breve retardo para estabilizar las lecturas del joystick y que no se un movimiento muy rapido
}
