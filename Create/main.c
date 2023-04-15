#include <kipr/wombat.h>
#include <math.h>
void move(float inches_wanted, int left_speed, int right_speed, float multiplier);
void forward(float inches_wanted, int speed);
void backward(float inches_wanted, int speed);
void right (float inches_wanted, int speed);
void left(float inches_wanted, int speed);
void button();
void test();
void line_follow();

int main()
{
    create_connect();
    line_follow();
    //forward(9.5, 75);
    //right(90, 75);
    //foward(69, 75);
    //left(45, 75);
    //forward(3, 75);
    //backward(3, 75);
    //left(45, 75);
    //forward(3, 75);
    create_disconnect();
    return 0;
}
void move(float inches_wanted, int left_speed, int right_speed, float multiplier)
{
    float inches_gone;
    set_create_distance(0);
    set_create_total_angle(0);
    create_drive_direct(left_speed, right_speed);
    while (1)
    {
        if (multiplier < 5)
        {
            inches_gone = fabs(get_create_total_angle());
        }
        else 
        { 
            inches_gone = fabs(get_create_distance());
        }

        if (inches_gone >= inches_wanted * multiplier)
        {
            create_stop();
            break;
        }
    }

}
void spin_right(int degrees_wanted, int speed)
{
    int degrees_gone;
    set_create_total_angle(0);
    create_drive_direct(speed, -speed);
    while (1)
    {
        degrees_gone = fabs (get_create_total_angle());
        if (degrees_gone >= degrees_wanted * 1.05)
        {
            create_stop();
            break;
        }
    }

}
void forward (float inches_wanted, int speed)
{
    move(inches_wanted, speed, speed, 26.65);
}
void backward(float inches_wanted, int speed)
{
    move(inches_wanted, -speed, -speed, 26.65);
}      
void right (float degrees_wanted, int speed)
{
    move(degrees_wanted, speed, -speed, 1.05);
}
void left(float degrees_wanted, int speed)
{
    move(degrees_wanted, -speed, speed, 1.05);
}      
void button()
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
void test()
{
    button();
    printf("Succesful\n");
    create_connect();
    forward(12, 100);
    button();
    backward(12, 100);
    button();
    left(90, 100);
    button();
    right(90, 100);
    button();

    //move(90, -90, 90, 1.05);
    // move(12, 90, 90, 26.65);
    // move(90, 90, -90, 1.05);
    //move(12, -90, -90, 26.65);
}
void line_follow()
{
    int s;
    while (1)
    {
        s = get_create_lfcliff();
        printf("%d\n", s);
        if (s > 800)
        {
            create_drive_direct(190, 170);
        }
        else if(s < 200)
        {
            create_drive_direct(170, 190);
        }
        else
        {
            create_drive_direct(190, 190);
        }
        msleep(1000);
    }
}
