class motionProfile{
public:
    void profileTask();

    void updateProfile(double i_maxSpeed, double i_accelTime, double i_finishTime);

    void disable();


private:
    double calculateOutput();

    double trapezoidalProfile();
    double SProfile();
 

public:
    enum profileTypes {E_TRAPEZOIDAL, E_SPROFILE};

    profileTypes activeProfileType;
    bool profileActive = false;
    double elapsedTime;
    double finishTime;


private:

    double m_accelTime; //Time it takes to reach max speed
    double m_maxSpeed;

};

extern motionProfile masterProfile;