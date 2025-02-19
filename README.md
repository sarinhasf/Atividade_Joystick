<img width=100% src="https://capsule-render.vercel.app/api?type=waving&color=0000FF&height=120&section=header"/>


<h1 align="center">EmbarcaTech | Atividade Joystick</h1>

Com o objetivo de consolidar os conceitos sobre o uso de conversores analógico-digitais (ADC) no RP2040 e explorar as funcionalidades da placa de desenvolvimento BitDogLab, propõe-se a realização daseguinte atividade prática individual.

## Objetivos:

- Compreender o funcionamento do conversor analógico-digital (ADC) no RP2040.
- Utilizar o PWM para controlar a intensidade de dois LEDs RGB com base nos valores do joystick.
- Representar a posição do joystick no display SSD1306 por meio de um quadrado móvel.
- Aplicar o protocolo de comunicação I2C na integração com o display.


## Sobre o projeto:

- O LED Azul terá seu brilho ajustado conforme o valor do eixo Y. Quando o joystick estiver solto (posição central - valor 2048), o LED permanecerá apagado. À medida que o joystick for movido para cima (valores menores) ou para baixo (valores maiores), o LED aumentará seu brilho gradualmente, atingindo a intensidade máxima nos extremos (0 e 4095).
- O LED Vermelho seguirá o mesmo princípio, mas de acordo com o eixo X. Quando o joystick estiver solto (posição central - valor 2048), o LED estará apagado. Movendo o joystick para a esquerda (valores menores) ou para a direita (valores maiores), o LED aumentará de brilho sendo mais intenso nos extremos (0 e 4095).
- Os LEDs serão controlados via PWM para permitir variação suave da intensidade luminosa. Exibir no display SSD1306 um quadrado de 8x8 pixels, inicialmente centralizado, que se moverá proporcionalmente aos valores capturados pelo joystick.
- Alternar o estado do LED Verde a cada acionamento.
- Modificar a borda do display para indicar quando foi pressionado, alternando entre diferentes estilos de borda a cada novo acionamento.
- Finalmente, o botão A terá a seguinte funcionalidade: Ativar ou desativar os LED PWM a cada acionamento

## Lista de requisitos:

1. Uso de interrupções: Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando rotinas de interrupção (IRQ).
2. Debouncing: É obrigatório implementar o tratamento do bouncing dos botões via software.
3. Utilização do Display 128 x 64: A utilização de ferramentas gráficas demonstrará o entendimento do princípio de funcionamento do display, bem como, a utilização do protocolo I2C.
4. Organização do código: O código deve estar bem estruturado e comentado para facilitar o entendimento.
 
## Tecnologias:

1. Git e Github;
2. VScode;
3. Linguagem C;
4. Simulador Wokwi;
5. Placa de desenvolvimento BitDogLab

## 💻 Instruções para Importar, Compilar e Rodar o Código Localmente:

Siga os passos abaixo para clonar o repositório, importar no VS Code usando a extensão do **Raspberry Pi Pico Project**, compilar e executar o código.

1. **Clone o repositório para sua máquina local**  
   Abra o terminal e execute os comandos abaixo:
   ```bash
   git clone https://github.com/sarinhasf/Atividade-ServoMotor.git
   cd projeto

2. **Abra o VS Code e instale a extensão "Raspberry Pi Pico Project" (caso não já a tenha instalada)**
 - No VS Code, vá até "Extensões" (Ctrl+Shift+X)
 - Pesquise por "Raspberry Pi Pico Project"
 - Instale a extensão oficial

3. **Importe o projeto no VS Code**
 - No VS Code, abra o projeto que foi clonado

## Desenvolvedora:
 
<table>
  <tr>
    <td align="center"><img style="" src="https://avatars.githubusercontent.com/u/143294885?v=4" width="100px;" alt=""/><br /><sub><b> Sara Souza </b></sub></a><br />👨‍💻</a></td>
</table>

## Link do video de apresentação: 

<table>
  <tr>
    <td align="center"> <sub><b> https://youtube.com/shorts/cNSTPe96JVw?si=U7tArYTkF_9oLuaY </b></td>
    </tr>
</table>
