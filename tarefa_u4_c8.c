/* Atividade Joystick | Embarcatech */
/* Aluna: Sara Souza Ferreira       */
/* Data de entrega: 18/02/2025      */


#include <stdio.h>        
#include "hardware/i2c.h"
#include "inc/ssd1306.h"
#include "inc/font.h"
#include "pico/stdlib.h"  
#include "pico/bootrom.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h" 
#include "hardware/adc.h"


#define DEBOUNCE_TIME 200000 // definindo tempo de esperar do debaunce
#define endereco 0x3C //endereço do nosso display
#define I2C_PORT i2c1
#define valor_max 121
#define valor_min 56


//Definindo variaveis globais
uint32_t last_time = 0;      // captura o tempo do ultimo acionamento do botão para o debounce
uint16_t eixo_x, eixo_y; //valores dos eixos 
bool estado_led_pwm = true; //variavel para alterar o estado dos leds 
uint sliceBlue, slideRed;           // Variáveis para armazenar os slices 
uint16_t nivelBlue = 50, nivelRed = 50; // Inicialização dos níveis de PWM para os LEDs, começando com o red em 50
ssd1306_t ssd;
bool cor = true; //para aparecer as coisas no display ou não
bool state;



//função callback das interruções
void btns_callback(uint gpio, uint32_t events)
{   
    //aplicando metodo deboucing
    uint32_t current_time = to_us_since_boot(get_absolute_time()); 
    if (current_time - last_time > DEBOUNCE_TIME)          // se tiver passado o tempo definido        
    {
        if (gpio == 5) //BOTÃO
        {estado_led_pwm = !estado_led_pwm;}

        else if (gpio == 22) //JOYSTICK 
        {
            state = !gpio_get(11);
            gpio_put(11, state);
            cor = !cor;
            ssd1306_fill(&ssd, !cor); // Limpa o display
        }

        last_time = current_time; // Atualiza o tempo para o debounce
    }
}

// Serve para configurar o PWM - Leds
void configuraPWM(uint led, uint *slice, uint16_t level)
{
    gpio_set_function(led, GPIO_FUNC_PWM); // Configura o pino do LED como saída PWM
    *slice = pwm_gpio_to_slice_num(led);   // Obtém o slice do PWM associado ao pino do LED
    pwm_set_clkdiv(*slice, 16.0);   // Define o divisor de clock do PWM
    pwm_set_wrap(*slice, 4096);          // Configura o valor máximo do contador (período do PWM)
    pwm_set_enabled(*slice, true);         // Habilita o PWM no slice correspondente ao LED
}

void inicializacao()
{
    stdio_init_all();

    //inicialização do I2C
    i2c_init(I2C_PORT, 400 * 1000); //usando 400Khz
    gpio_set_function(14, GPIO_FUNC_I2C);                    
    gpio_set_function(15, GPIO_FUNC_I2C);                   
    gpio_pull_up(14);                                        
    gpio_pull_up(15);                                        
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); 
    ssd1306_config(&ssd);                                         
    ssd1306_send_data(&ssd);                                      

    //inicalização dos pinos
    adc_init();  // Inicializa o módulo ADC
    adc_gpio_init(27); // Configura o pino 27 (eixo X) para entrada ADC
    adc_gpio_init(26); // Configura o pino 26 (eixo Y) para entrada ADC
    gpio_init(22);             
    gpio_set_dir(22, GPIO_IN); 
    gpio_pull_up(22);          
    gpio_init(5);
    gpio_set_dir(5, GPIO_IN);
    gpio_pull_up(5);
    gpio_init(11);
    gpio_set_dir(11, GPIO_OUT);
    
    //inicialização dos leds azul e vermelho como pwm
    configuraPWM(12, &sliceBlue, nivelBlue); 
    configuraPWM(13, &slideRed, nivelRed);    
}

// Função que serve para ler os valores dos eixos do joystick 
void lendoJoystick(uint16_t *valor_X, uint16_t *valor_Y)
{
    // Leitura do valor do eixo X 

    adc_select_input(0); //canal adc 0
    sleep_us(1); //espera um tempo para ler                    
    *valor_X = adc_read();           

    // Leitura do valor do eixo Y 

    adc_select_input(1); //canal adc 1
    sleep_us(1); //espera um tempo para ler             
    *valor_Y = adc_read();           
}

//serve para exibição no display ssd1306
void viewDisplay(uint16_t X, uint16_t Y) 
{
    ssd1306_fill(&ssd, cor);
    ssd1306_rect(&ssd, 3, 3, 122, 58, !cor, cor);

    //definindo os limites da tela
    if (X > valor_max) {X = valor_max;}

    if (Y > valor_min) {Y = valor_min;}

    ssd1306_draw_string(&ssd, "*", X, Y); // Desenha o quadrado que se mexe junto ao joystick
    ssd1306_send_data(&ssd); //setando as infos
}

//função principal
int main()
{
    inicializacao();
    printf("Inicializações feitas com sucesso!\n");

    //criando as interrupções dos botoes A e Joystick
    gpio_set_irq_enabled_with_callback(5, GPIO_IRQ_EDGE_FALL, true, btns_callback);
    gpio_set_irq_enabled_with_callback(22, GPIO_IRQ_EDGE_FALL, true, btns_callback);

    while (1)
    {
        lendoJoystick(&eixo_x, &eixo_y); //chamando a função que faz a leitura do joystick
        viewDisplay(eixo_x/28, eixo_y/69); //chamando a função que foca na visualização no display 
        
        if (estado_led_pwm == true)
        {
            //modificando a intensidade dos leds atráves do ciclo de trabalho
            pwm_set_gpio_level(12, eixo_x); //LED BLUE
            pwm_set_gpio_level(13, eixo_y);  //LED RED
        }
        else{
            //apaga os leds 
            pwm_set_gpio_level(12, 0); //LED BLUE
            pwm_set_gpio_level(13, 0); //LED RED
        }
        sleep_ms(100);
    }
}
