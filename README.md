# Zadanie 2 - Sterowanie PWM diodami LED RGB

## Opis

Program steruje jasnoscia zielonej diody LED (LED4) za pomoca PWM na STM32L476RG.
Jasnosc zmienia sie przyciskami S1 (jasniej) i S2 (ciemniej) z wykorzystaniem przerwan EXTI.

## Mikrokontroler

STM32L476RG (Nucleo-64), zegar 80 MHz (HSI + PLL).

## Uzycie pinow

| Pin | Funkcja | Opis |
|-----|---------|------|
| PB6 (RGB_LED_1) | TIM4_CH1 (AF2) | Anoda LED4 - sygnal PWM sterujacy jasnoscia |
| PB7 (RGB_LED_2) | GPIO Input (no pull) | Wysoka impedancja - nieaktywny (charlieplexing) |
| PB8 (RGB_LED_3) | GPIO Output LOW | Katoda zielona LED4 - LOW = zielony wlaczony |
| PB9 (RGB_LED_4) | GPIO Input (no pull) | Wysoka impedancja - nieaktywny (charlieplexing) |
| PB0 (S1) | EXTI Falling + Pull-up | Przycisk zwiekszania jasnosci (podlaczony do GND) |
| PB5 (S2) | EXTI Falling + Pull-up | Przycisk zmniejszania jasnosci (podlaczony do GND) |

## Konfiguracja PWM (TIM4)

- Zegar timera: 80 MHz
- Prescaler: 79 (80 MHz / 80 = 1 MHz)
- Period (ARR): 999
- Czestotliwosc PWM: 1 MHz / 1000 = **1 kHz**
- Tryb: PWM1, polaryzacja HIGH
- Kanal: CH1 (PB6)

## Topologia LED - Charlieplexing

Diody RGB (LD1-LD4) sa polaczone w ukladzie charlieplexing na 4 pinach (PB6-PB9).
Aby zapalic konkretny kolor jednej diody:
- jeden pin ustawia sie jako wyjscie HIGH (anoda),
- drugi pin jako wyjscie LOW (katoda wybranego koloru),
- pozostale piny jako wejscia (wysoka impedancja) - zapobiega to zapaleniu niepozadanych diod.

Dla LED4 zielony: PB6=HIGH (anoda), PB8=LOW (katoda zielona), PB7/PB9=input.

## Sterowanie jasnoscia

- Zmienna `brightness` (uint16_t) przechowuje wartosc CCR (0-1000)
- Wartosc poczatkowa: 200 (20% wypelnienia)
- S1: zwieksza brightness o 100 (max 900)
- S2: zmniejsza brightness o 100 (min 100)
- Zmiana CCR przez `__HAL_TIM_SET_COMPARE()` w przerwaniu EXTI

## Uzyte metody HAL

| Funkcja | Zastosowanie |
|---------|-------------|
| `HAL_TIM_PWM_Start()` | Uruchomienie PWM na TIM4 CH1 |
| `__HAL_TIM_SET_COMPARE()` | Ustawienie wartosci CCR (wypelnienie PWM) |
| `HAL_GPIO_EXTI_Callback()` | Obsluga przerwan od przyciskow S1/S2 |
| `HAL_TIM_PWM_Init()` | Inicjalizacja TIM4 w trybie PWM (CubeMX) |
| `HAL_TIM_PWM_ConfigChannel()` | Konfiguracja kanalu PWM (CubeMX) |
| `HAL_GPIO_Init()` | Konfiguracja GPIO (CubeMX) |
| `HAL_NVIC_EnableIRQ()` | Wlaczenie przerwan EXTI0 i EXTI9_5 (CubeMX) |

## Struktura plikow

- `Core/Src/main.c` - logika programu (callback EXTI, start PWM, zmienna brightness)
- `Core/Src/stm32l4xx_it.c` - handlery przerwan (TIM4, EXTI0, EXTI9_5) - wygenerowane przez CubeMX
- Konfiguracja GPIO, TIM4, NVIC - wygenerowana przez CubeMX w main.c
