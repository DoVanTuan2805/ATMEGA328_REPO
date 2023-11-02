#include <init.h>
#define DIR A1
#define PUL A2

static uint16_t setupSpeed = 0;
volatile uint16_t value_timer = 65000; // max 65525
static int pulse = 1600;
volatile float target_pulse = 0; // 360 angle = 1600 xung
volatile uint16_t current_pulse = 0;
volatile bool state = false;
volatile bool step_on = true;

void initInteruptTimer1()
{
    cli(); // tắt ngắt toàn cục

    /* Reset Timer/Counter1 */
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;

    /* Setup Timer/Counter1 */
    TCCR1B |= (1 << CS11) | (1 << CS10); // prescale = 64

    /*
    1 xung = 64/16Mhz = 4us
    */
    TCNT1 = value_timer + setupSpeed; // DEFAUL = 65500 go to 65536 = 37 -> 4us * 37 = 148 tràn
    TIMSK1 = (1 << TOIE1);            // Overflow interrupt enable
    sei();                            // cho phép ngắt toàn cục
}
ISR(TIMER1_OVF_vect)
{
    state = !state;
    digitalWrite(PUL, state);
    TCNT1 = value_timer + setupSpeed;
    current_pulse++;
    if (current_pulse / 2 > target_pulse)
    { // 3200 xung -> 1600 xung +    -------   1600 xung -
        current_pulse = 0;
        TCCR1A = 0;
        TCCR1B = 0;
        TIMSK1 = 0;
    }
}
void angleStep(float angleNew, float angleOld)
{
    float angle = angleNew - angleOld;
    bool dir = angle < 0 ? 1 : 0;
    digitalWrite(DIR, dir);
    angle = abs(angle);
    // 360 = 1600
    // angle = ?
    target_pulse = pulse * angle / 360.0;
    initInteruptTimer1();
}