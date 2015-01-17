#include <iostream>
#include <iomanip>

const float GRAVITY_CONST = 9.81;
const float TIME_CONST = 0.1;
const float ITERATIONS = 200;

class FloatingObject
{
    float mass;
    float waterResistanceK;
    float archimedForce;
    float speed;
    float depth;

public:
    FloatingObject(float mass, float archimedForce, float waterResistanceK) :
        mass(mass),
        archimedForce(archimedForce),
        waterResistanceK(waterResistanceK)
    {/*
        this->mass = mass;
        this->archimedForce = archimedForce;
        this->waterResistanceK = waterResistanceK;*/
    }

    void Initialize(float speed, float depth)
    {
        setSpeed(speed);
        setDepth(depth);
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

    float getArchimedForce()
    {
        return archimedForce;
    }

    float getMass()
    {
        return mass;
    }

    float getWaterResistanceK()
    {
        return waterResistanceK;
    }

};

class Robot : public FloatingObject
{
    float enginePower;

public:
    Robot(float mass, float archimedForce, float waterResistanceK, float enginePower)
       : FloatingObject(mass, archimedForce, waterResistanceK),
         enginePower(enginePower)
    {
    }

    void setEnginePower(float power)
    {
        this->enginePower = power;
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

float CalculateForces(FloatingObject & w)
{
    float weight = -w.getMass()*GRAVITY_CONST;
    float waterResistance = -w.getSpeed()*w.getWaterResistanceK();
    return weight + w.getArchimedForce() + waterResistance;
}

int main()
{
    Robot r(1, 50, 0.1, -35);
    FloatingObject w(1, 30, 0.1);
    r.Initialize(0, -5);
    w.Initialize(0, -5);

    for (int i =0; i < ITERATIONS; i++)
    {
        float forceSum = CalculateForces(r);
        float acceleration = forceSum/r.getMass();

        r.setSpeed(acceleration*TIME_CONST);
        r.setDepth(r.getDepth() + r.getSpeed()*TIME_CONST);

        forceSum = CalculateForces(w);
        acceleration = forceSum/w.getMass();

        w.setSpeed(acceleration*TIME_CONST);
        w.setDepth(w.getDepth() + w.getSpeed()*TIME_CONST);

        std::cout << std::setw(15) << r.getDepth() << std::setw(15) << w.getDepth() << std::endl;
    }
    system("pause");
    return 0;
}

