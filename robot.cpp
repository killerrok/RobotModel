#include <iostream>

const float GRAVITY_CONST = 9.81;
const float TIME_CONST = 0.1;
const float ITERATIONS = 20;

class Robot
{
    float depth;
    float waterResistanceK;
    float speed;
    float mass;
    float archimedForce;
    float enginePower;

public:

    Robot(float mass, float archimedForce, float waterResistanceK)
        : speed(0),
        depth(0),
        enginePower(0)
    {
        this->mass = mass;
        this->archimedForce = archimedForce;
        this->waterResistanceK = waterResistanceK;
    }

    void Initialize(float speed, float depth, float power)
    {
        setSpeed(speed);
        setDepth(depth);
        setEnginePower(power);
    }

    void setSpeed(float speed)
    {
        this->speed = speed;
    }

    float getSpeed()
    {
        return speed;
    }

    void setDepth(float depth)
    {
        if (depth < 0)
            this->depth = depth;
        else
            this->depth = 0;
    }

    float getDepth() 
    { 
        return depth; 
    }

    void setEnginePower(float power)
    {
        this->enginePower = power;
    }

    float getMass()
    {
        return mass;
    }

    float getWaterResistanceK()
    {
        return waterResistanceK;
    }

    float getArchimedForce()
    {
        return archimedForce;
    }

    float getEnginePower()
    {
        return enginePower;
    }
};

float CalculateForces(Robot & r)
{
    float weight = -r.getMass()*GRAVITY_CONST;
    float waterResistance = -r.getSpeed()*r.getWaterResistanceK();
    return weight + r.getArchimedForce() + waterResistance + r.getEnginePower();
}

int main()
{
    Robot r(1, 50, 0.1);
    r.Initialize(0, -5, 0);
    //r.setEnginePower(-40);

    for (int i =0; i < ITERATIONS; i++)
    {
        float forceSum = CalculateForces(r);
        float acceleration = forceSum/r.getMass();
        r.setSpeed(acceleration*TIME_CONST);
        r.setDepth(r.getDepth() + r.getSpeed()*TIME_CONST);
        std::cout << r.getDepth() << std::endl;
    }
    system("pause");
    return 0;
}