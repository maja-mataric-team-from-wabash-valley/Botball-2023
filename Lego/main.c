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
#define OPEN 1600
#define DOWN 1150
#define CLOSE 970
#define UP 50
#define SERVO_TIME 500
#define ARM 3
#define CLAW 0
#define SLOW 10
#define MEDIUM 20
#define FAST 40
#define UP_WITH_ITEM 1050
#define INFARED_SENSOR 0
#define BLACK 3500
#define WHITE 3000
double START_TIME = 0.0;
#define PRESS_ON 0  //0 = off and 1 = on
#define WAIT_FOR_CREATE 0
#define LIGHT_RANGE 2000

void turn_right_till_white(int left_speed, int right_speed);
void turn_right_till_black(int left_speed, int right_speed);
void line_follow_backwards();
void turn_left_degrees(int degrees);
void turn_right_degrees(int degrees);
void go_forward_till_black(int speed);
void open_claw();
void down_claw();
void close_claw(int div);
void up_claw();
void close_claw(int div);
void up_claw_with_item();
void go_forward_till_white(int speed);
void turn_right_till_grey(int left_speed, int right_speed);
void motor_off();
void move_forward_inches(int inches, int speed);
void clear_motor_position();
void follow_right_line();
void follow_left_line();
void set_up_robot();
void go_to_line_at_start();
void move_backwards_inches(int inches, int speed);
void grab_item();
void go_back_to_line();
void press();
void start_timer();
double get_timer();
void wait_for_create();
void wait_until_packets();
int LIGHT_ON_VALUE;
int LIGHT_OFF_VALUE;
int LIGHT_THRESHOLD;
void calibrate_light(int port);
void wait_for_lights(int port);

int main()
{
    printf("Hello World\n");
    set_up_robot();
    calibrate_light(2);
    wait_for_lights(2);
    press();
    start_timer();
    press();
    go_to_line_at_start();
    press();
    follow_left_line();
    press();
    grab_item();
    press();
    // go_back_to_line();
    //press();
    line_follow_backwards();
    press();
    move_forward_inches(6,100);
    press();
    set_servo_position(ARM,1020);
    turn_right_degrees(100);
    press();
    turn_right_till_black(40,-40);
    set_servo_position(ARM,1020);
    press();
    turn_right_till_white(20,-20);  
    press();
    turn_right_till_black(-20,20);
    press();
    turn_right_till_white(20,-20);
    press();
    turn_right_till_black(-20,20);
    turn_right_till_white(20,-20);
    down_claw();
    wait_until_packets();
    move_backwards_inches(12, 100);
    turn_left_degrees(70);
    open_claw();
    up_claw();
    turn_right_degrees(70);
    line_follow_backwards();
    move_forward_inches(1,100);
    set_servo_position(ARM,1050);
    open_claw();
    turn_left_degrees(100);
    move_forward_inches(7,100);  
    close_claw(100);
    move_backwards_inches(4,50);
    line_follow_backwards();
    move_forward_inches(1,50);
    turn_right_degrees(100);
    open_claw();
    disable_servos();



    return 1;
}

void close_claw(int div)
{
    int current_pos;
    int next_pos;
    while (1)
    {
        current_pos = get_servo_position(CLAW);
        next_pos = current_pos - div;
        if(current_pos <= CLOSE)
        {
            break;   
        }
        set_servo_position(CLAW, next_pos);
        while (1)
        {
            if (get_servo_position(CLAW) <= next_pos)
            {
                break;
            }
        }
        msleep(200);
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
            motor_off();
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
            motor_off();
            break;   
        }
    }    
}
void motor_off()
{
    off(2);
    off(3);
}
void move_forward_inches( int inches, int speed)
{
    clear_motor_position();
    motor(2,speed);
    motor(3,speed);
    while(1)
    {
        if (inches * 225 <= get_motor_position_counter(2))
        {
            motor_off();
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
    motor_off();
}
void turn_left_degrees(int degrees)
{
    motor(3,-50);
    motor(2,50);
    msleep(16.5*degrees);
    motor_off();
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
            motor_off();
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
            motor_off();
            break;
        }
    }
}

void set_up_robot()
{
    enable_servos();
    close_claw(100);
    up_claw();
}
void go_to_line_at_start()
{
    go_forward_till_black(100);
    go_forward_till_white(100);
    motor_off();
    move_forward_inches(2,100);
    turn_right_degrees(90);
    motor_off();
}
void move_backwards_inches(int inches, int speed)
{
    clear_motor_position();
    motor(2,-speed);
    motor(3,-speed);
    while(1)
    {
        if (inches * 225 <= fabs(get_motor_position_counter(2)))
        {
            break;
        }
    }
    motor_off();
    clear_motor_position();
}
void grab_item()
{
    move_backwards_inches(5,75);
    press();
    open_claw();
    press();
    turn_right_degrees(20);
    press();
    down_claw();
    press();
    //turn_right_degrees(20);
    press();
    turn_left_degrees(20);
    //move_forward_inches(2,75);  // was 4
    press();
    close_claw(100);
}
void go_back_to_line()
{
    motor(2,-50);
    motor(3,-50);
    turn_left_degrees(10);
    msleep(500);
    motor_off();

}
void line_follow_backwards()
{

    while (1)
    {

        if (analog(1) < 2000)
        {  

            motor(3,-100);  
            motor(2,-50); 
        }

        else 
        {  
            motor(2,-100);
            motor(3,-50);

        }

        if (digital(1))
        {
            motor_off();
            break;
        }
    }

}
void press()
{ 
    if (PRESS_ON)
    {

        printf("Press A\n");
        while (1)
        {
            if (a_button())
            {
                break;
            }
            msleep(50);
        }
    }
    else
    {
        msleep(200);
    }
}
void turn_right_till_white(int left_speed, int right_speed)
{
    motor(2, right_speed);
    motor(3, left_speed);
    while (1)
    {
        if (analog(0) < 2500)
        {  
            motor_off();
            break;   
        }
    }    
}
void turn_right_till_black(int left_speed, int right_speed)
{
    motor(2, right_speed);
    motor(3, left_speed);
    while (1)
    {
        if (analog(0) > 2500)
        {  
            motor_off();
            break;   
        }
    }    
}
void start_timer()
{
    START_TIME = seconds();
}
double get_timer()
{
    return seconds() - START_TIME;
}
void wait_until_packets()
{
    while(1)
    {
        if(get_timer() > 67.0)
        {
            break;
        }
    }
}
void turn_right_till_grey(int left_speed, int right_speed)
{
    motor(2, right_speed);
    motor(3, left_speed);
    while (1)
    {
        if (analog(0) > 2500 && analog(0) < 2700)
        {  
            motor_off();
            break;   
        }
    }    
}
void wait_for_create()
{
    while (WAIT_FOR_CREATE)
    {
        msleep(22000);
    }	
}
void calibrate_light(int port)
{
    while (1)
    {
        printf(" Turn on light. Press 'A' to continue\n");
        while (1)
        {
            if (a_button())
            {
                LIGHT_ON_VALUE = analog(port);
                msleep(1000);
                break;
            }
        }
        printf(" Turn off light. Press 'A' to continue\n");
        while (1)
        {
            if (a_button())
            {
                LIGHT_OFF_VALUE = analog(port);
                msleep(1000);
                break;
            }
        }
        if (LIGHT_OFF_VALUE - LIGHT_ON_VALUE > LIGHT_RANGE)
        {
            printf("Light calibration complete\n");
            break; 
        }
        else 
        {
            printf("Light calibration failed/ Press 'A' to try again\n");
            if (a_button())
            {

                msleep(100);
            }
        }
    }
}
void wait_for_lights(int port)
{
    printf("Ready for light");
    while (1)
    {
        if (analog(port) <= 1000)
        {
            break ; 
        }
        else 
        {
          msleep(100);
        }
    }
}
