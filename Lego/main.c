/*
  Style rules:
    Use an underscore to separate words in a name.
    Meaningful names for functions.  Use verb phrases.
    Meaningful named constants for all magic numbers.  Use ALL_CAPS noun phrases.
    Meaningful variable names (but  k  for loop variables).  Use noun phrases.
    A single blank lines to separate sections of code (including function definitions).
      No blank lines within a function.
    A single space after every comma.
    A single space after IF, WHILE, FOR.
    Prototypes for every function (except main).
    Functions are ordinarily less than 15 lines of code.
    {
      Use this curly brace style.
    }
    Indent per the INDENT button in the KIPR IDE.
    Prototypes and #defines ordered in a sensible way, e.g.:
      main,
      sub-functions of main
      movement functions
      claw functions
      other functions.
    Use the same ordering for function definitions as you used for prototypes.
*/

/*
  main function for the Lego robot, Botball 2013.
  Authors include: PUT_YOUR_NAMES_HERE.
*/

/*
  TODO:
  1. Fix all to obey style rules.  Compile frequently as you do so.
  2. Divide  main  into sub-functions that themselves are < 15 lines of code.
  3. Add speed parameter to turn functions.
  4. Test, test test (on the actual board).
  5. Probably need to have a claw position and code for going over the bump.
*/

#include <kipr/wombat.h>
#define OPEN 2000
#define DOWN 2000
#define CLOSE 1350
#define UP 1000
#define SERVO_TIME 500
#define ARM 1
#define CLAW 0
#define SLOW 10
#define MEDIUM 20
#define FAST 40
#define UP_WITH_ITEM 1800
#define INFARED_SENSOR 0
#define BLACK 3500
#define WHITE 3000

void turn_left_degrees(int degrees);
void turn_right_degrees(int degrees);
void go_forward_till_black(int speed);
void open_claw();
void down_claw();
void close_claw();
void up_claw();
void close_claw(int div);
void up_claw_with_item();
void go_forward_till_white(int speed);
void motor_off();
void move_forward_inches(int inches, int speed);
void clear_motor_position();
int main()
{
    printf("Hello World\n");

    enable_servos();
    close_claw(FAST);
    up_claw();
    go_forward_till_black(100);
    go_forward_till_whiee(100);
    motor_off();
    motor(2,50);
    motor(3,50);
    msleep(500);
    motor_off();
    turn_right_degrees(90);
    motor_off();
    while (1)
    {

        if (analog(0) > 3000)
        {  
            motor(2,100);
            motor(3,60);  
        }

        else if (analog(0) < 3000)
        {  
            motor(2,60);
            motor(3,100);  
        }

        if (digital(0))
        {
            break;
        }
    }
    off(2);
    off(3);
    motor(2,-50);
    motor(3,-50);
    msleep(3000);
    off(2);
    off(3);
    open_claw();
    down_claw();
    motor(3,30);
    motor(2,-30);
    msleep(1000);
    off(2);
    off(3);
    motor(2,50);
    motor(3,50);
    msleep(1500);
    off(2);
    off(3);
    close_claw(FAST);
    motor(2,-50);
    motor(3,-50);
    msleep(1000);
    off(2);
    off(3);
    motor(3,-40);
    motor(2,100);
    msleep(3000);
    off(2);
    off(3);
    msleep(5000);
    while (1)
    {

        if (analog(0) > 3000)
        {  
            motor(2,100);
            motor(3,60);  
        }

        else if (analog(0) < 3000)
        {  
            motor(2,60);
            motor(3,100);  
        }
        if (digital(0))
        {
            break;
        }
    }
    return 0;
}
void close_claw(int div)
{
    int pos;
    pos=get_servo_position(CLAW);
    while(1)
    {

        if (pos <= CLOSE) break; 
        pos= pos-div;
        set_servo_position(CLAW,pos);
        msleep(100);
    }
}

void open_claw()
{
    set_servo_position(CLAW,OPEN);
    msleep(SERVO_TIME);

}

void down_claw()
{
    set_servo_position(ARM,DOWN);
    msleep(SERVO_TIME);
}

void up_claw()
{
    set_servo_position(ARM,UP);
    msleep(SERVO_TIME);
}

void up_claw_with_item()
{
    set_servo_position(ARM,UP_WITH_ITEM);
    msleep(SERVO_TIME);
}

void go_forward_till_black(int speed)
{
    motor(2, speed);
    motor(3, speed);
    while (1)
    {
        if (analog(INFARED_SENSOR) > BLACK)
        {  
            break;   
        }
    }    
}
void go_forward_till_white(int speed)
{
    motor(2, speed);
    motor(3, speed);
    while (1)
    {
        if (analog(INFARED_SENSOR) < WHITE)
        {  
            break;   
        }
    }    
}
void motor_off()
{
    off(2);
    off(3);
}
void move_forward_inches(int inches, int speed)
{
    clear_motor_position();
    motor(2,speed);
    motor(3,speed);
    while(1)
    {
        if (inches * 225 <= get_motor_position_counter(2))
        {
            break;
        }
    }
    motor_off();
    clear_motor_position();
}
void clear_motor_position()
{
    clear_motor_position_counter(2);
    clear_motor_position_counter(3);
}
void turn_right_degrees(int degrees)
{
    motor(3,50);
    motor(2,-50);
    msleep(16.5*degrees);

}
void turn_left_degrees(int degrees)
{
    motor(3,-50);
    motor(2,50);
    msleep(16.5*degrees);

}

void follow_left_line()
{
    while (1)
    {

        if (analog(0) > 3000)
        {  
            motor(2,100);
            motor(3,60);  
        }

        else if (analog(0) < 3000)
        {  
            motor(2,60);
            motor(3,100);  
        }

        if (digital(0))
        {
            break;
        }
    }
}
void follow_right_line()
{
    while (1)
    {

        if (analog(0) > 3000)
        {  
            motor(2,60);
            motor(3,100);  
        }

        else if (analog(0) < 3000)
        {  
            motor(2,100);
            motor(3,60);  
        }

        if (digital(0))
        {
            break;
        }
    }
}
