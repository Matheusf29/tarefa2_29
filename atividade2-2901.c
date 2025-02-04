// Incluindo as bibliotecas.
#include <stdio.h> 
#include "pico/stdlib.h" 
#include "hardware/timer.h" 
#include "hardware/pio.h"

const uint LED_BLUE = 11;    
const uint LED_RED = 12;    
const uint LED_GREEN = 13;   

#define BUTTON_A 5  // Definindo o pino do botão

bool led_active = false;    // Variável de apoio para armazenar o estado dos leds.

// Função de callback para desligar o LED.
int64_t turn_off_callback_desligar_led_vermelho(alarm_id_t id, void *user_data) {
   
   gpio_put(LED_RED, false);       // desliga o led vermelho, atribuido falso em sua saida

   return 0;          // retorna 0 para que o alarme não se repita
}

// Função de callback para desligar o LED.
int64_t turn_off_callback_desligar_led_azul(alarm_id_t id, void *user_data) {
    
    gpio_put(LED_BLUE, false);       // desliga o led azul, atribuido falso em sua saida

    return 0; // retorna 0 para que o alarme não se repita
}

// Função de callback para desligar o LED.
int64_t turn_off_callback_desligar_led_verde(alarm_id_t id, void *user_data) {
    
    gpio_put(LED_GREEN, false); // desligando o led verde
    led_active = false;         // Altera a variável para indicar que os leds estão desligados
    return 0;                       
}

/*Inicializando as portas que serão utilizadas, ativando pull up na gpio-5*/
void iniciar(){
    gpio_init(LED_RED);               
    gpio_set_dir(LED_RED, GPIO_OUT);  
    gpio_init(LED_BLUE);                  
    gpio_set_dir(LED_BLUE, GPIO_OUT);    
    gpio_init(LED_GREEN);                 
    gpio_set_dir(LED_GREEN, GPIO_OUT);    
    gpio_init(BUTTON_A);                    
    gpio_set_dir(BUTTON_A, GPIO_IN);          
    gpio_pull_up(BUTTON_A);
}

void liga_leds(){
    gpio_put(LED_RED, true);        
    gpio_put(LED_BLUE, true);       
    gpio_put(LED_GREEN, true);
    /*Funções para desligar os leds a cada 3s*/
    add_alarm_in_ms(3000, turn_off_callback_desligar_led_azul, NULL, false);
    add_alarm_in_ms(6000, turn_off_callback_desligar_led_vermelho, NULL, false);
    add_alarm_in_ms(9000, turn_off_callback_desligar_led_verde, NULL, false); 
}


int main() {
    //Função para inicializar as portas
    iniciar();

    while (true) {
        // Verifica se o botão foi pressionado e se o LED não está ativo.
        if ((!gpio_get(BUTTON_A)) && (!led_active)) {
            
            sleep_ms(50); //Atraso para evitar multiplas leituras depois nova verificação.

            if (!gpio_get(BUTTON_A)) {

                liga_leds();         // ligar os 3 leds e setar os callbacks.
                led_active = true;  // Altera a variável para indicar que os leds estão ligados
            }}
        sleep_ms(10);
    }
    return 0;
}